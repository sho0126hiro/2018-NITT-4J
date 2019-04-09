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

ID	tskIDA, tskIDB ;
ID	flgID;
/* HOS下で最初に起動するハンドラ*/
/* system.cfg中で静的に起動される */
void OnHosStart(VP_INT exinf)
{
	const static T_CTSK pk_ctskA = { TA_HLNG, 1, primeNumber, 5, 256, NULL};
	const static T_CTSK pk_ctskB = { TA_HLNG, 1,   ButtonLED, 6, 256, NULL};
	ER_ID	tskid ;
	/* flugを追加 */
	ER_ID	flgid ;
	T_CFLG pk_cflg = { (TA_TPRI | TA_WMUL), 0 };
	
	putStringSCI1("OnHosStart: starting!\n");
	flgid = acre_flg( &pk_cflg ); /*イベントフラグを生成*/
	
	if( E_OK < flgid ) {
		flgID = flgid;
	} else {
		SCI1_printf("acre_flg error %d\n", flgid);
	}
	
	
	if( ( tskid = acre_tsk( &pk_ctskA ) ) <= E_OK ) {
		SCI1_printf( "acre_tsk error %d\n", tskid ) ;
	} else {
		tskIDA= tskid ;
	}

	if( ( tskid = acre_tsk( &pk_ctskB ) ) <= E_OK ) {
		SCI1_printf( "acre_tsk error %d\n", tskid ) ;
	} else {
		tskIDB= tskid ;
	}
	act_tsk( tskIDA );
}

/* 1万以上の素数を表示し続けるタスク*/
void primeNumber(VP_INT exinf){
	static int num=10000;
	int i;
	int check = 1;
	FLGPTN flgptn;
	T_RFLG pk_rflg;
	act_tsk( tskIDB );
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
			wai_sem(SEMID_SCI); /* semapho資源の獲得 */
			ref_flg(flgID,&pk_rflg);
			/* フラグが0のときのみ表示する */
			/*SCI1_printf("flg :  %d\n",pk_rflg.flgptn);*/
			if(!pk_rflg.flgptn){
				SCI1_printf("primeNumber :%8d\n",num);
			}
			sig_sem(SEMID_SCI); /* semapho資源の返却 */
			dly_tsk(2);
		}
		if(num == 32767) num =10000;
		num++;
	}
}

/* ボタン1を押すとLED1を点灯，タスクAの表示を停止 */
/* もう一度ボタン1を押すとLED1を消灯，タスクAの表示を再開 */
void ButtonLED(VP_INT exinf)
{
	static int oldbutton = 0;
	static int stat=0;
	int button=0;
	int count;
	int i,j;
	while(1){
		wai_sem(SEMID_SCI);
		button = getPushSW();
		/*SCI1_printf("stat = %d\n",stat);*/
		if(oldbutton<button && button == 1){
			/*push button1*/
			/*チャタリング防止*/
			for(i=0;i<20000;i++)for(j=0;j<20;j++);
			if(stat==1){
				stat = 0;
				turnOffLed(0);
				SCI1_printf("restart!\n");
			}else{
				stat = 1;
				turnOnLed(0);
				SCI1_printf("stop!\n");
			}
		}
		if(stat != 1){
			clr_flg(flgID, ~1);
			sig_sem(SEMID_SCI);
		}else{
			set_flg(flgID, 1);
			sig_sem(SEMID_SCI);
			/*SCI1_printf("hahaha world\n",stat);*/
		}
	}
}

