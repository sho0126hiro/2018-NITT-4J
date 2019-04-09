#include "kernel.h"
#include "kernel_id.h"
#include "MinSys3069.h"
#include "sample.h"


/* スタートアップルーチンから最初に呼び出される初期化関数 */
/* OS起動前にすること（SCIの初期化など）を行っておく      */
/* この関数からスタートアップルーチンに戻った後に，       */
/* スタートアップルーチンはHOSを呼び出す                  */
void preStartHos()
{
	initSCI1();              /* SCIの初期化 */
	SCI1_printf("\npreStartHos: start!\n");  /* 開始メッセージ */
}

/* HOS下で最初に起動するハンドラ*/
/* system.cfg中で静的に起動される */
void OnHosStart(VP_INT exinf)
{
	putStringSCI1("OnHosStart: starting!\n");
	act_tsk(TSKID_0);	/* TASKID_0は静的生成 */
	act_tsk(TSKID_1);	/* TASKID_1は静的生成 */
	act_tsk(TSKID_2);	/* TASKID_2は静的生成 */
}


void taskA(VP_INT exinf)
{
	char *msg;
	int i;
	while(1){
		get_mpf(MPFID_0, (VP)&msg); /* 共有メモリの獲得 */
		mymemcpy(msg, "National Institute of Technology, Tokyo College\0", 48);
		for(i=0;i<48;i++)SCI1_printf("%c",msg[47-i]);
		SCI1_printf("\n");
		rel_mpf(MPFID_0, (VP)msg); /* 共有メモリの解放 */
		dly_tsk(1000);
	}
}

void taskB(VP_INT exinf)
{
	char *msg;
	int i;
	while(1){
		get_mpf(MPFID_0, (VP)&msg); /* 共有メモリの獲得 */
		mymemcpy(msg, "National Institute of Technology, Tokyo College\0", 48);
		for(i=0;i<48;i++)if(i%2!=0)SCI1_printf("%c",msg[i]);
		SCI1_printf("\n");
		rel_mpf(MPFID_0, (VP)msg); /* 共有メモリの解放 */
		dly_tsk(1000);
	}
}

void taskC(VP_INT exinf)
{
	char *msg;
	int i;
	while(1){
		get_mpf(MPFID_0, (VP)&msg); /* 共有メモリの獲得 */
		mymemcpy(msg, "National Institute of Technology, Tokyo College\0", 48);
		for(i=0;i<48;i++)if(i%2==0)SCI1_printf("%c",msg[i]);
		SCI1_printf("\n");
		rel_mpf(MPFID_0, (VP)msg); /* 共有メモリの解放 */
		dly_tsk(1000);
	}
}

void mymemcpy(char *d, char *s, int size)
{
    while(size-- > 0) *d++ = *s++;
}


