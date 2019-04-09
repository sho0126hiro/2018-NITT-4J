#include "kernel.h"
#include "kernel_id.h"
#include "MinSys3069.h"
#include "sample.h"

ID tsk_drumRoot;
ID cycID;
ID flg_button;
ID flg_drum2;
ID flg_drum3;
/* スタートアップルーチンから最初に呼び出される初期化関数 */
/* OS起動前にすること（SCIの初期化など）を行っておく      */
/* この関数からスタートアップルーチンに戻った後に，       */
/* スタートアップルーチンはHOSを呼び出す                  */
void preStartHos()
{
	int i,j;
	initSCI1();              /* SCIの初期化 */
	initLCD();               /* LCDの初期化 */
	SCI1_printf("\npreStartHos: start!\n");  /* 開始メッセージ */
}

/* HOS下で最初に起動するハンドラ*/
/* system.cfg中で静的に起動される */
void OnHosStart(VP_INT exinf)
{
	const static T_CTSK pk_ctsk4 = {TA_HLNG, 1,   drumRoot, 5, 256, NULL};
	const static T_CFLG pk_cflg={(TA_TPRI | TA_WMUL),0};
	T_CCYC pk_ccyc = {TA_HLNG,1,CYC_wupCButton,10};
	ER_ID tskid,cycid,flgid;
	
	putStringSCI1("OnHosStart: starting!\n");
	tskid=acre_tsk(&pk_ctsk4);
	
	/* cyc*/
	cycid = acre_cyc(&pk_ccyc);
	if(E_OK < cycid){
		cycID = cycid;
	}else{
		SCI1_printf("acre_cyc error %d\n",cycid);
	}
	
	/*flag*/
	flgid=acre_flg(&pk_cflg);
	if (E_OK<flgid) {
		flg_button=flgid;
		SCI1_printf("OnHosStart: flgid=%d\n",flg_button);
	} else {
		SCI1_printf("OnHosStart: acre_flg err %d\n",flgid);
	}
	
	/*タスクの起動*/
	if( ( tskid = acre_tsk( &pk_ctsk4 ) ) <= E_OK ) {
		SCI1_printf( "acre_tsk4 error %d\n", tskid ) ;
	} else {
		tsk_drumRoot = tskid ;
	}
	cycid = acre_cyc(&pk_ccyc);
	act_tsk(tskID_CHK_BTN);
	act_tsk( tsk_drumRoot );

}

/* 周期的に立ち上がらせる */
void CYC_wupCButton(VP_INT exinf)
{
	wup_tsk(tskID_CHK_BTN);
}

/* tskID_CHK_BTN */
void checkButton(VP_INT exinf)
{
	static int oldbutton=0;
	int button;
	int stat;
	putStringSCI1("checkButton: starting!\n");
	sta_cyc(cycID);
	while(1) {
		slp_tsk();
		button=getPushSW();
		if ((stat=(oldbutton^button))) {
			if (oldbutton<button) { /*押された*/
				sta_tsk(tskID_BTN_HDL,stat);
			}
			oldbutton=button;
		}
	}
	ext_tsk();
}



void drumRoot(VP_INT exinf){
	T_RFLG pk_rflg;
	int d1=1,d2=2,d3=3,stopcount=0;
	int check1=1,check2=1,check3=1;
	const stop=5; /* ドラム回転のスピード調整（0の場合速すぎて文字が薄くなる）*/
	putStringSCI1("drumRoot: starting!\n");
	while(1){
		if(stop == stopcount){
			stopcount==0;
			LCDclrscr();
			SCI1_printf("%d  \n",d1);
			ref_flg(flg_button,&pk_rflg);
			switch(pk_rflg.flgptn){
				case 1:
					check1=1;
					clr_flg(flg_button,~1);
					break;
				case 2:
					check2=1;
					clr_flg(flg_button,~2);
					break;
				case 3:
					check3=1;
					clr_flg(flg_button,~3);
					break;
				case 4:
					check1=0;
					check2=0;
					check3=0;
					turnOffLed(0);
					clr_flg(flg_button,~4);
					break;
			}
			if(!check1)d1++;
			if(!check2)d2++;
			if(!check3)d3++;
			if(d1==10)d1=0;
			if(d2==10)d2=0;
			if(d3==10)d3=0;
			if(d1==d2 && d2==d3){
				if(check1 && check2 && check3)turnOnLed(0);
			}
			LCD_printf("%d %d %d",d1,d2,d3);
		}
		stopcount++;
		/* if(check1 && check2 && check3)turnOnLed(0); */
	}
}

#define	BTN0	0x01
#define	BTN1	0x02
#define	BTN2	0x04
#define	BTN3	0x08

void buttonHandler(VP_INT exinf)
{
	switch (exinf) {
	case BTN0:
		SCI1_printf("B0 PUSHED  \n");
		set_flg(flg_button,1);
		break;
	case BTN1:
		SCI1_printf("B1 PUSHED  \n");
		set_flg(flg_button,2);
		break;
	case BTN2:
		SCI1_printf("B2 PUSHED  \n");
		set_flg(flg_button,3);
		break;
	case BTN3:
		SCI1_printf("B3 PUSHED  \n");
		set_flg(flg_button,4);
		break;
	default:
		break;
	}
	ext_tsk();
}
