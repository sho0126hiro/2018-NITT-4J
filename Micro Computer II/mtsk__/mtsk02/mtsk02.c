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

void task2(void)
{
	int cnt=10000;
	while (1) {
		D_INT();  /*このデモでは通信中は割り込み禁止にしてリソースの競合を避けている*/
		SCI1_printf("task2 %5d\n",cnt);
		E_INT();
		msecwait(20);
		cnt++;
		if (cnt==11000) cnt=10000;
	}
}

/***************　２つのタスクの実体　ここまで　********************/

typedef union {
	unsigned char Bccr;
	unsigned long int returnAddress;
} stack_t;

typedef struct {
	unsigned long int Ber7;   /*初期状態ではBer0をさしている*/
	unsigned char stack[128]; /*stack～stack0の合わさったものが実際のスタック*/
	unsigned long int Ber0;   /*初期状態だけER0があると考える，後はスタックの一部*/
	unsigned long int Ber1;   /*初期状態だけER1があると考える，後はスタックの一部*/
	unsigned long int Ber2;   /*初期状態だけER2があると考える，後はスタックの一部*/
	unsigned long int Ber3;   /*初期状態だけER3があると考える，後はスタックの一部*/
	unsigned long int Ber4;   /*初期状態だけER4があると考える，後はスタックの一部*/
	unsigned long int Ber5;   /*初期状態だけER5があると考える，後はスタックの一部*/
	unsigned long int Ber6;   /*初期状態だけER6があると考える，後はスタックの一部*/
	stack_t stack0;           /*初期状態はここに戻りアドレスとCCRが入っている*/
} context_t;

context_t context0,context1,context2; /*コンテキストバッファの実体*/
int tasksw=0; /* 0 または 1 または2　稼働中のタスク番号*/
unsigned long int systemstackPtr;  /*スイッチャ用スタックポインタ退避場所*/

main()
{
	initLed();   /*LEDユニットの初期化　点滅させるが，動作確認用*/
	initSCI1();  /*シリアル通信の初期化*/
	SCI1_printf("\n\n\n  *** task switcher ***\n\n");
	initTimer01Int(500); /*時間割り込み500smsec ITUch0,1使用　このタイミングでタスク切り替えが起こる*/
	E_INT();        /*CPU割り込み許可*/

	/*コンテキストバッファにコンテキストを２つの作成*/
	context0.stack0.returnAddress=(unsigned long int)task0; /* task0の戻り値の設定 */
	context0.Ber7=(unsigned long int)&(context0.Ber0);/*初期化 */

	context1.stack0.returnAddress=(unsigned long int)task1;
	context1.Ber7=(unsigned long int)&(context1.Ber0);

    context2.stack0.returnAddress=(unsigned long int)task2;
	context2.Ber7=(unsigned long int)&(context2.Ber0);

	startTimer01();  /*時間割り込みタイマスタートch0,ch1*/

	/*ここまでで2つのタスクの起動準備完了。最初はtask0を起動する*/
	tasksw=0;
    /* 下のアセンブリコードが起動プログラム*/
#pragma asm
    mov.l  er7,  @_systemstackPtr  ;スイッチャのスタックポインタを退避
    mov.l  @_context0, er7 ;タスク0のスタックポインタを復帰
                           ; context0とcontext0.Ber7は同じアドレス
    pop.l  er0
    pop.l  er1
    pop.l  er2
    pop.l  er3
    pop.l  er4
    pop.l  er5
    pop.l  er6
    rte                            ;ReTurn from Exception によりタスク起動
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
インターバルタイマ割り込みで起動するルーチン，タスク切り替えの作業を行う
TaskSwitcherでは次のことを行う
（１）現在のタスクがtask0,task1,task2のどれであったか検出
（２）現在の全レジスタをcontext0，またはcontext1として保存
（３）次のタスクにむけてcontext0，またはcontext1を全レジスタに載せる
（４）rteで新タスクを起動（割り込みから戻るふりをする）
*/
#pragma asm
_TaskSwitcher:                   ; function: TaskSwitcher
    ;タイマユニットに割り込みを受け付けたことを知らせる
    BCLR.B #0,@H'FFFF71:8         ;ITU1.TSR.BIT.IMFA=0;

    ; ** 旧コンテキスト保存 **
    push.l er6
    push.l er5
    push.l er4
    push.l er3
    push.l er2
    push.l er1
    push.l er0
    mov.w  @_tasksw, r0   ;直前のタスク番号の取得
    cmp.w  #2, r0         ; 2と比べて
    beq RETURNEDFROMTASK2 ; 同じなら入る
    cmp.w  #1, r0         ; 1と比べて
    beq RETURNEDFROMTASK1 ; 同じなら入る

RETURNEDFROMTASK0:
    ;直前がタスク0のときのタスクスイッチ作業
    mov.w #1, r0         ;次のタスク番号は1
    mov.w r0, @_tasksw   ;次のタスク番号を変数taskswに保存
    ;スタックポインタをコンテキスト0のBer7に保存
    mov.l  er7,  @_context0; (context0とcontext0.Ber7は同じアドレス)
    ;コンテキスト1のBer7をスタックポインタにセット
    mov.l  @_context1, er7 ; (context1とcontext1.Ber7は同じアドレス)
    bra GONEXTTASK ; jump goNextTask

RETURNEDFROMTASK1:
    ;直前がタスク1のときのタスクスイッチ作業
    mov.w #2, r0         ;次のタスク番号は2
    mov.w r0, @_tasksw   ;次のタスク番号を変数taskswに保存
    ;スタックポインタをコンテキスト１のBer7に保存
    mov.l  er7,  @_context1; (context1とcontext1.Ber7は同じアドレス)
    ;コンテキスト2のBer7をスタックポインタにセット
    mov.l  @_context2, er7 ; (context2とcontext2.Ber7は同じアドレス)
    bra GONEXTTASK ; jump goNextTask

RETURNEDFROMTASK2:
    ;直前がタスク2のときのタスクスイッチ作業
    mov.w #0, r0         ;次のタスク番号は0
    mov.w r0, @_tasksw   ;次のタスク番号を変数taskswに保存
    ;スタックポインタをコンテキスト2のBer7に保存
    mov.l  er7,  @_context2; (context2とcontext2.Ber7は同じアドレス)
    ;コンテキスト0のBer7をスタックポインタにセット
    mov.l  @_context0, er7 ; (context0とcontext0.Ber7は同じアドレス)

GONEXTTASK:
    pop.l  er0
    pop.l  er1
    pop.l  er2
    pop.l  er3
    pop.l  er4
    pop.l  er5
    pop.l  er6

    rte

#pragma endasm
