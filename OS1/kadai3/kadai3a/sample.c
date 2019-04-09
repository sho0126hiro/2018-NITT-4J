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

const static T_CTSK pk_ctsk = {TA_HLNG,  1, primeNumber, 4, 256, NULL};
const static T_CTSK pk_ctsk2 = {TA_HLNG, 1,   printLine, 3, 128, NULL};
const static T_CTSK pk_ctsk3 = {TA_HLNG, 1,   printDoubleLine, 2, 128, NULL};
ID tskID1, tskID2, tskID3;
const static T_CFLG pk_cflg={(TA_TPRI | TA_WMUL),0};
ID flgID;

/* HOS下で最初に起動するハンドラ*/
/* system.cfg中で静的に起動される */
void OnHosStart(VP_INT exinf)
{
	ER_ID tskid;
	ER_ID flgid;
	putStringSCI1("OnHosStart: starting!\n");
	tskid=acre_tsk(&pk_ctsk);
	if (E_OK<tskid) {
		tskID1=tskid;
		SCI1_printf("OnHosStart: primeNumber Pri,id= %d,%d\n",pk_ctsk.itskpri,tskid);
	} else {
		SCI1_printf("OnHosStart: acre_tsk primeNumber err %d\n",tskid);
	}
	tskid=acre_tsk(&pk_ctsk2);
	if (E_OK<tskid) {
		tskID2=tskid;
		SCI1_printf("OnHosStart: printLine Pri,id= %d,%d\n",pk_ctsk2.itskpri,tskid);
	} else {
		SCI1_printf("OnHosStart: acre_tsk printLine err %d\n",tskid);
	}
	tskid=acre_tsk(&pk_ctsk3);
	if (E_OK<tskid) {
		tskID3=tskid;
		SCI1_printf("OnHosStart: printLine Pri,id= %d,%d\n",pk_ctsk2.itskpri,tskid);
	} else {
		SCI1_printf("OnHosStart: acre_tsk printLine err %d\n",tskid);
	}
	
	/* flg_id */
	flgid=acre_flg(&pk_cflg);
	if (E_OK<flgid) {
		flgID=flgid;
		SCI1_printf("OnHosStart: flgid=%d\n",flgID);
	} else {
		SCI1_printf("OnHosStart: acre_flg err %d\n",flgid);
	}
	
	act_tsk(tskID1);
	act_tsk(tskID2);
	act_tsk(tskID3);
}

/* 1secごとにタイマの時間を表示するタスク */
/* system.cfg中で静的に生成され，OnHosStart()中で起動されている */
void printTime(VP_INT exinf)
{
	SYSTIM time;
	PRI tskpri = 1;
	ER checker;
	T_RFLG pk_rflg;
	FLGPTN flgptn;
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
	int c     = 0;
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
			c++;
		}
		if(num == 32767) num =10000;
		num++;
		
		if(c >= 5 && count!=50){
			c=0;
			set_flg(flgID,1);
		}
		if(count == 50){
			count=0;
			c = 0;
			set_flg(flgID,2);
		}
	}
}

/* 横罫線を引く */
void printLine(VP_INT exinf){
	T_RFLG pk_rflg;
	FLGPTN flgptn;
	while(1){
		wai_flg(flgID,1,TWF_ANDW,&flgptn);
		SCI1_printf("------------------------------\n");
		clr_flg(flgID,~1);
	}
}

void printDoubleLine(VP_INT exinf){
	T_RFLG pk_rflg;
	FLGPTN flgptn;
	while(1){wai_flg(flgID,2,TWF_ANDW,&flgpt
		n);
		SCI1_printf("==============================\n");
		clr_flg(flgID,~2);
	}
}
/*
実行結果

preStartHos: start!
OnHosStart: starting!
OnHosStart: primeNumber Pri,id= 4,8
OnHosStart: printLine Pri,id= 3,7
OnHosStart: printLine Pri,id= 3,6
OnHosStart: flgid=4
primeNumber :   10007
primeNumber :   10009
primeNumber :   10037
primeNumber :   10039
primeNumber :   10061
------------------------------
primeNumber :   10067
primeNumber :   10069
primeNumber :   10079
primeNumber :   10091
primeNumber :   10093
------------------------------
primeNumber :   10099
primeNumber :   10103
primeNumber :   10111
primeNumber :   10133
primeNumber :   10139
------------------------------
primeNumber :   10141
primeNumber :   10151
primeNumber :   10159
primeNumber :   10163
primeNumber :   10169
------------------------------
primeNumber :   10177
primeNumber :   10181
primeNumber :   10193
primeNumber :   10211
primeNumber :   10223
------------------------------
primeNumber :   10243
primeNumber :   10247
primeNumber :   10253
primeNumber :   10259
primeNumber :   10267
------------------------------
primeNumber :   10271
primeNumber :   10273
primeNumber :   10289
primeNumber :   10301
primeNumber :   10303
------------------------------
primeNumber :   10313
primeNumber :   10321
primeNumber :   10331
primeNumber :   10333
primeNumber :   10337
------------------------------
primeNumber :   10343
primeNumber :   10357
primeNumber :   10369
primeNumber :   10391
primeNumber :   10399
------------------------------
primeNumber :   10427
primeNumber :   10429
primeNumber :   10433
primeNumber :   10453
primeNumber :   10457
==============================
primeNumber :   10459
primeNumber :   10463
primeNumber :   10477
primeNumber :   10487
primeNumber :   10499
------------------------------
primeNumber :   10501
primeNumber :   10513
primeNumber :   10529
primeNumber :   10531
primeNumber :   10559
------------------------------
primeNumber :   10567
primeNumber :   10589
primeNumber :   10597
primeNumber :   10601
primeNumber :   10607
------------------------------
primeNumber :   10613
primeNumber :   10627
primeNumber :   10631
primeNumber :   10639
primeNumber :   10651
------------------------------
primeNumber :   10657
primeNumber :   10663
primeNumber :   10667
primeNumber :   10687
primeNumber :   10691
------------------------------
primeNumber :   10709
primeNumber :   10711
primeNumber :   10723
primeNumber :   10729
primeNumber :   10733
------------------------------
primeNumber :   10739
primeNumber :   10753
primeNumber :   10771
primeNumber :   10781
primeNumber :   10789
------------------------------
primeNumber :   10799
primeNumber :   10831
primeNumber :   10837
primeNumber :   10847
primeNumber :   10853
------------------------------
primeNumber :   10859
primeNumber :   10861
primeNumber :   10867
primeNumber :   10883
primeNumber :   10889
------------------------------
primeNumber :   10891
primeNumber :   10903
primeNumber :   10909
primeNumber :   10937
primeNumber :   10939
==============================
primeNumber :   10949
primeNumber :   10957
primeNumber :   10973
primeNumber :   10979
primeNumber :   10987
------------------------------
primeNumber :   10993
primeNumber :   11003
primeNumber :   11027
primeNumber :   11047
primeNumber :   11057
------------------------------
primeNumber :   11059
primeNumber :   11069
primeNumber :   11071
primeNumber :   11083
primeNumber :   11087
------------------------------
primeNumber :   11093
primeNumber :   11113
primeNumber :   11117
primeNumber :   11119
primeNumber :   11131
------------------------------
primeNumber :   11149
primeNumber :   11159
primeNumber :   11161
primeNumber :   11171
primeNumber :   11173
------------------------------
primeNumber :   11177
primeNumber :   11197
primeNumber :   11213
primeNumber :   11239
primeNumber :   11243
------------------------------
primeNumber :   11251
primeNumber :   11257
primeNumber :   11261
primeNumber :   11273
primeNumber :   11279
------------------------------
primeNumber :   11287
primeNumber :   11299
primeNumber :   11311
primeNumber :   11317
primeNumber :   11321
------------------------------
primeNumber :   11329
primeNumber :   11351
primeNumber :   11353
*/