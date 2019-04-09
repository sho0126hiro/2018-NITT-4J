#include "kernel.h"
#include "kernel_id.h"
#include "MinSys3069.h"
#include "sample.h"

ID tskID1;
ID tskID2;

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
	const static T_CTSK pk_ctsk = {TA_HLNG,  1, primeNumber, 3, 256, NULL};
	const static T_CTSK pk_ctsk2 = {TA_HLNG, 1,   printLine, 2, 128, NULL};
	
	ER_ID tskid;
	ER_ID tskid2;
	putStringSCI1("OnHosStart: starting!\n");
	tskid=acre_tsk(&pk_ctsk);
	tskid2=acre_tsk(&pk_ctsk2);
	if (E_OK<tskid) {
		tskID1=tskid;
		act_tsk(tskID1);
	} else {
		SCI1_printf("acre_tsk err %d\n",tskid);
	}
	if (E_OK<tskid2) {
		tskID2=tskid2;
		act_tsk(tskID2);
	} else {
		SCI1_printf("acre_tsk err %d\n",tskid2);
	}
}

/* 1secごとにタイマの時間を表示するタスク */
/* system.cfg中で静的に生成され，OnHosStart()中で起動されている */
void printTime(VP_INT exinf)
{
	SYSTIM time;
	PRI tskpri = 1;
	ER checker;
	while (1) { /*永久ループ*/
		/* タイマ値取得 */
		get_tim(&time);
		
		if((unsigned long int)time.ltime > 3000){
			/* 3秒経過時 */
			checker = chg_pri(tskID2,tskpri);
			if(checker != E_OK){
				SCI1_printf("ercd_tsk err %d\n",checker);
			}
		}
		
		/* タイマ値出力 */
		SCI1_printf("printTime:%8ld\n",(unsigned long int)time.ltime);
		
		/* 1000msec待つ(OSにCPU利用権を一時的に返し，時間になったら戻してもらう) */
		dly_tsk(1000);
	}
}

/* 1万以上の素数を表示し続けるタスク*/
void primeNumber(VP_INT exinf){
	int num=10000;
	int i;
	int check = 1;
	int count = 0;
	while(1){
		check = 1;
		if(num%2==0){
			num++;
			continue;
		}
		if(num%3==0){
			num++;
			continue;
		}
		for(i=4;i<=num/2;i++){
			if((num%i)==0){
				check=0;
				break;
			}
		}
		if(check){
			SCI1_printf("primeNumber :%8d\n",num);
			count++;
		}
		if(num == 32767) num =10000;
		num++;
		if(count == 10){
			count=0;
			wup_tsk(tskID2);
		}
	}
}

/* 横罫線を引く */
void printLine(VP_INT exinf){
	while(1){
		SCI1_printf("------------------------------\n");
		slp_tsk();
	}
}
