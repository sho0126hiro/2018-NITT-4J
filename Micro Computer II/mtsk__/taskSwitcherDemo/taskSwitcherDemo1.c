/**********************************************************
インターバルタイマ割り込みによって２つのタスクの切り替えを行う
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

/***************　２つのタスクの実体　ここから　********************/
void msecwait(int msec)
/*mesc間なにもしない時間稼ぎ関数*/
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<1588;j++);    /*1588は実測によって求めた値*/
	}
}

void task0(void)
{
	int cnt=0;
	while (1) {
		D_INT();  /*このデモでは通信中は割り込み禁止にしてリソースの競合を避けている*/
		SCI1_printf("task0 %4d\n",cnt);
		E_INT();
		msecwait(20);
		cnt++;
		if (cnt==100) cnt=0;
	}
}

void task1(void)
{
	int cnt=1000;
	while (1) {
		D_INT();  /*このデモでは通信中は割り込み禁止にしてリソースの競合を避けている*/
		SCI1_printf("task1 %4d\n",cnt);
		E_INT();
		msecwait(20);
		cnt++;
		if (cnt==1100) cnt=1000;
	}
}

/***************　２つのタスクの実体　ここまで　********************/

typedef union {
	unsigned char Bccr;
	unsigned long int returnAddress;
} stack_t;

typedef struct {
	unsigned char stack[128]; /*stackとstack0の合わさったものが実際のスタック*/
	stack_t stack0;           /*初期状態はここに戻りアドレスとCCRが入っている*/
	unsigned long int Ber0;   /*ここより下のBer0～Ber7は各レジスタの保存領域*/
	unsigned long int Ber1;
	unsigned long int Ber2;
	unsigned long int Ber3;
	unsigned long int Ber4;
	unsigned long int Ber5;
	unsigned long int Ber6;
	unsigned long int Ber7; /*初期状態ではstack0をさしている*/
} context_t;

context_t context0,context1; /*コンテキストバッファの実体*/

int tasksw=0; /* 0 または 1 ：どちらのタスクが実行されているかを示している*/
unsigned long int Ber0;  /*ER0の退避場所　タスクスイッチャ起動直後にちょっと使う*/
const unsigned long int buff0Address=(unsigned long int)&context0.Ber0;
const unsigned long int buff1Address=(unsigned long int)&context1.Ber0;
const unsigned long int stackPtr0Address=(unsigned long int)&context0.Ber7;
const unsigned long int stackPtr1Address=(unsigned long int)&context1.Ber7;
unsigned long int systemstackPtr;  /*スイッチャ用スタックポインタ退避場所*/


main()
{
	initLed();   /*LEDユニットの初期化　点滅させるが，動作確認用*/
	initSCI1();  /*シリアル通信の初期化*/
	SCI1_printf("\n\n\n  *** task switcher demo ***\n\n");
	initTimer01Int(500); /*時間割り込み500msec ITUch0,1使用　このタイミングでタスク切り替えが起こる*/
	E_INT();        /*CPU割り込み許可*/

	/*コンテキストバッファにコンテキストを２つの作成*/
	context0.stack0.returnAddress=(unsigned long int)task0;
	context0.Ber7=(unsigned long int)&(context0.stack0);

	context1.stack0.returnAddress=(unsigned long int)task1;
	context1.Ber7=(unsigned long int)&(context1.stack0);

	startTimer01();  /*時間割り込みタイマスタートch0,ch1*/

	/*ここまでで2つのタスクの起動準備完了。最初はtask0を起動する*/
	tasksw=0;
#pragma asm
	mov.l  er7,  @_systemstackPtr  ;タスクスイッチャのスタックポインタを退避
	mov.l  @_stackPtr0Address, er0 ;タスク0のスタックポインタを設定（復帰と同じ手順）
	mov.l  @er0, er7               ;     (er0経由でer7(=SP)に設定)
	rte                            ;ReTurn from Exception によりタスク0起動
#pragma endasm

} /*end of main*/


/*ベクトルテーブルの設定*/
#pragma asm
	.SECTION    MYVEC, DATA, LOCATE=H'000070
	.ORG        H'000070  ;IMIA1
	.DATA.L     _TaskSwitcher
	.SECTION    P,CODE,ALIGN=2 ;これを忘れてはいけない
#pragma endasm

/*
インターバルタイマ割り込みで起動するルーチン／タスクスイッチャ本体
タスク切り替えの作業を行う
TaskSwitcherでは次のことを行う
（１）現在のタスクがtask0,task1のどちらであったか検出
（２）現在の全レジスタをcontext0，またはcontext1として保存
（３）次のタスクにむけてcontext0，またはcontext1を全レジスタに載せる
（４）rteで新タスクを起動（割り込みから戻るふりをする）

ただし，タスクスイッチャが起動した時点では，すべてのレジスタは，
スイッチャ起動前に動作していたタスクが使用中である。
そのため，スイッチャが起動直後において，全レジスタを保存する前にいくつかの
レジスタを使用する場合は，そのレジスタを退避し，作業が終了した時点で復帰させ
全レジスタをコンテキスト保存場所に保存する手順となる。以下の★参照
*/
#pragma asm
_TaskSwitcher:                   ; function: TaskSwitcher
	;タイマユニットに割り込みを受け付けたことを知らせる
	BCLR.B #0,@H'FFFF71:8         ;ITU1.TSR.BIT.IMFA=0;

	; ** 旧コンテキスト保存 **
	mov.l  er0,  @_Ber0  ;直前タスク番号確認のためER0を使いたいのでER0を退避★↓
	mov.w  @_tasksw, r0
	cmp.w  #1, r0         ;r0が1であるかどうか調べる
	beq    RETUNEDFROMTASK1  ;直前がタスク１，次がタスク０ならジャンプ
RETUNEDFROMTASK0:
	mov.w #1, r0          ;次のタスクはタスク1
	mov.w  r0,  @_tasksw  ;この段階で変数taskswの中身は次のコンテキスト番号
	;直前はタスク０だったのでコンテキスト０に保存する準備
	mov.l  @_stackPtr0Address, er0
	bra SAVECONTEXT
RETUNEDFROMTASK1:
	mov.w #0, r0          ;次のタスクはタスク0
	mov.w  r0,  @_tasksw  ;この段階で変数taskswの中身は次のコンテキスト番号
	;直前はタスク１だったのでコンテキスト１に保存する準備
	mov.l  @_stackPtr1Address, er0
SAVECONTEXT:
	;コンテキストの保存
	mov.l  er7, @er0  ;er0の指しているアドレスにer7(=SP)を保存する
	mov.l  er0, er7   ;er0の値をer7(=SP)に設定する
	mov.l  @_Ber0,  er0                            ;ER0を使い終えたので復帰★↑
	push.l er6
	push.l er5
	push.l er4
	push.l er3
	push.l er2
	push.l er1
	push.l er0

	;この段階で，すべてのレジスタをスイッチャが自由に使えるようになった

	; ** 次に実行すべき新コンテキスト設定 **
	mov.w  @_tasksw, r0  ;変数taskswの中身は次のタスク番号である
	cmp.w  #1, r0
	beq    SETREADYTASK1  ;新タスクが１ならジャンプ
SETREADYTASK0:
	;コンテキスト０用のスタックを指すようにスタックポインタを設定
	mov.l  @_buff0Address, er7
	bra SETCONTEXTANDGO
SETREADYTASK1:
	;コンテキスト１用のスタックを指すようにスタックポインタを設定
	mov.l  @_buff1Address, er7
SETCONTEXTANDGO:
	;コンテキストを復旧させて，次のタスク起動
	pop.l  er0
	pop.l  er1
	pop.l  er2
	pop.l  er3
	pop.l  er4
	pop.l  er5
	pop.l  er6
	pop.l  er7

	rte                            ;ReTurn from Exception により新タスク起動

#pragma endasm

/*
実行結果

  *** task switcher demo ***

task0    0
task0    1
task0    2
task0    3
task0    4
task0    5
task0    6
task0    7
task0    8
task0    9
task0   10
task0   11
task0   12
task0   13
task0   14
task0   15
task0   16
task0   17
task0   18
task0   19
task0   20
task0   21
task0   22
task0   23
task0   24
task0   25
task0   26
task0   27
task0   28
task0   29
task0   30
task0   31
task0   32
task0   33
task0   34
task0   35
task0   36
task0   37
task0   38
task0   39
task0   40
task0   41
task0   42
task0   43
task0   44
task0   45
task0   46
task0   47
task0   48
task1 1000
task1 1001
task1 1002
task1 1003
task1 1004
task1 1005
task1 1006
task1 1007
task1 1008
task1 1009
task1 1010
task1 1011
task1 1012
task1 1013
task1 1014
task1 1015
task1 1016
task1 1017
task1 1018
task1 1019
task1 1020
task1 1021
task1 1022
task1 1023
task1 1024
task1 1025
task1 1026
task1 1027
task1 1028
task1 1029
task1 1030
task1 1031
task1 1032
task1 1033
task1 1034
task1 1035
task1 1036
task1 1037
task1 1038
task1 1039
task1 1040
task1 1041
task1 1042
task1 1043
task1 1044
task1 1045
task1 1046
task1 1047
task1 1048
task0   49
task0   50
task0   51
task0   52
task0   53
task0   54
task0   55
task0   56
task0   57
task0   58
task0   59
task0   60
task0   61
task0   62
task0   63
task0   64
task0   65
task0   66
task0   67
task0   68
task0   69
task0   70
task0   71
task0   72
task0   73
task0   74
task0   75
task0   76
task0   77
task0   78
task0   79
task0   80
task0   81
task0   82
task0   83
task0   84
task0   85
task0   86
task0   87
task0   88
task0   89
task0   90
task0   91
task0   92
task0   93
task0   94
task0   95
task0   96
task0   97
task1 1049
task1 1050
task1 1051
task1 1052
task1 1053
task1 1054
task1 1055
task1 1056
task1 1057
task1 1058
task1 1059
task1 1060
task1 1061
task1 1062
task1 1063
task1 1064
task1 1065
task1 1066
task1 1067
task1 1068
task1 1069
task1 1070
task1 1071
task1 1072
task1 1073
task1 1074
task1 1075
task1 1076
task1 1077
task1 1078
task1 1079
task1 1080
task1 1081
task1 1082
task1 1083
task1 1084
task1 1085
task1 1086
task1 1087
task1 1088
task1 1089
task1 1090
task1 1091
task1 1092
task1 1093
task1 1094
task1 1095
task1 1096
task1 1097
task0   98
task0   99
task0    0
task0    1
task0    2
task0    3
task0    4
task0    5
task0    6
task0    7
task0    8
task0    9
task0   10
task0   11
task0   12
task0   13
task0   14
task0   15
task0   16
task0   17
task0   18
task0   19
task0   20
task0   21
task0   22
task0   23
task0   24
task0   25
task0   26
task0   27
task0   28
task0   29
task0   30
task0   31
task0   32
task0   33
task0   34
task0   35
task0   36
task0   37
task0   38
task0   39
task0   40
task0   41
task0   42
task0   43
task0   44
task0   45
task0   46
task1 1098
task1 1099
task1 1000
task1 1001
task1 1002
task1 1003
task1 1004
task1 1005
task1 1006
task1 1007
task1 1008
task1 1009
task1 1010
task1 1011
task1 1012
task1 1013
task1 1014
task1 1015
task1 1016
task1 1017
task1 1018
task1 1019
task1 1020
task1 1021
task1 1022
task1 1023
task1 1024
task1 1025
task1 1026
task1 1027
task1 1028
task1 1029
task1 1030
task1 1031
task1 1032
task1 1033
task1 1034
task1 1035
task1 1036
task1 1037
task1 1038
task1 1039
task1 1040
task1 1041
task1 1042
task1 1043
task1 1044
task1 1045
task1 1046
task0   47
task0   48
task0   49
task0   50
task0   51
task0   52
task0   53
task0   54
task0   55
task0   56
task0   57
task0   58
task0   59
task0   60
task0   61
task0   62
task0   63
task0   64
task0   65
task0   66
task0   67
task0   68
task0   69
task0   70
task0   71
task0   72
task0   73
task0   74
task0   75
task0   76
task0   77
task0   78
task0   79
task0   80
task0   81

*/
