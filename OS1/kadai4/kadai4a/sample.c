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

ID    cycID1,cycID2;
ID tskID1, tskID2, tskID3;
ID flgID;

void OnHosStart(VP_INT exinf)
{
	ER_ID tskid;
	ER_ID cycid;
	ER_ID flgid;
	T_CTSK pk_ctsk1 = {TA_HLNG,  1, checkButton, 5, 256, NULL};
	T_CTSK pk_ctsk2 = {TA_HLNG, 1,  buttonHandler, 5, 256, NULL};
	T_CTSK pk_ctsk3 = {TA_HLNG, 1,  checkButtonKeep, 5, 256, NULL};
	
	T_CFLG pk_cflg = { (TA_TPRI | TA_WMUL), 0 };
	
	T_CCYC pk_ccyc = {TA_HLNG,1,CYC_wupCButton,128};
	T_CCYC pk_ccyc2 = {TA_HLNG,1,CYC_wupCBK,10};
	
	flgid = acre_flg( &pk_cflg ); /*イベントフラグを生成*/
	if( E_OK < flgid ) {
		flgID = flgid;
	} else {
		SCI1_printf("acre_flg error %d\n", flgid);
	}

	tskid=acre_tsk(&pk_ctsk1);
	if (E_OK<tskid) {
		tskID1=tskid;
	} else {
		SCI1_printf("OnHosStart: acre_tsk checkButton err %d\n",tskid);
	}
	
	tskid=acre_tsk(&pk_ctsk2);
	if (E_OK<tskid) {
		tskID2=tskid;
	} else {
		SCI1_printf("OnHosStart: acre_tsk buttonHandler err %d\n",tskid);
	}
	
	tskid=acre_tsk(&pk_ctsk3);
	if (E_OK<tskid) {
		tskID3=tskid;
	} else {
		SCI1_printf("OnHosStart: acre_tsk checkButtonKeep err %d\n",tskid);
	}
	
	cycid = acre_cyc(&pk_ccyc);
	if(E_OK < cycid){
		cycID1 = cycid;
	}else{
		SCI1_printf("acre_cyc error %d\n",cycid);
	}
	cycid = acre_cyc(&pk_ccyc2);
	if(E_OK < cycid){
		cycID2 = cycid;
	}else{
		SCI1_printf("acre_cyc error %d\n",cycid);
	}
	putStringSCI1("OnHosStart: starting!\n");
	
	act_tsk(tskID1);
	act_tsk(tskID3);
}

void CYC_wupCButton(VP_INT exinf)
{
	wup_tsk(tskID1);
}

void CYC_wupCBK(VP_INT exinf)
{
	wup_tsk(tskID3);
}

void checkButton(VP_INT exinf)
{
	static int oldbutton=0;
	int button;
	int stat;
	int count;
	/*putStringSCI1("checkButton: starting!\n");*/
	sta_cyc(cycID1);
	while(1) {
		slp_tsk();
		count=0;
		button=getPushSW();
		/*SCI1_printf("button [%d] old[%d]\n",button,oldbutton);*/
		if(oldbutton<button){/* push */
			oldbutton=button;
			while(button){
				button /= 2;
				count++;
			}
			button = count;
			/*SCI1_printf("push:%d\n",count);*/
			stat = (count << 4) | 0x0f;
			sta_tsk(tskID2,stat);
		}else if (oldbutton>button){/*release*/
			while(oldbutton){
				oldbutton /= 2;
				count++;
			}
			oldbutton=count;
			/*SCI1_printf("release:%d\n",oldbutton);*/
			stat = (count << 4) & 0xf0;
			/*SCI1_printf("stat[release]:%b\n",stat);*/
			sta_tsk(tskID2,stat);
			oldbutton = button;
		}
	}
	ext_tsk();
}

#define BTN0_PUSH 0x1f
#define	BTN1_PUSH 0x2f

#define BTN0_RELEASE 0x10
#define	BTN1_RELEASE 0x20


void buttonHandler(VP_INT exinf)
{
	switch (exinf) {
	case BTN0_PUSH:
		SCI1_printf("B0 PUSHED  \n");
		turnOnLed(0);
		set_flg(flgID,1);
		sta_cyc(cycID2);
		break;
	case BTN1_PUSH:
		SCI1_printf("B1 PUSHED  \n");
		turnOnLed(1);
		set_flg(flgID,2);
		sta_cyc(cycID2);
		break;
	case BTN0_RELEASE:
		SCI1_printf("B0 RELEASED  \n");
		stp_cyc(cycID2);
		clr_flg(flgID, ~3);
		break;
	case BTN1_RELEASE:
		SCI1_printf("B1 RELEASED  \n");
		stp_cyc(cycID2);
		clr_flg(flgID, ~3);
		break;
	default:
		break;
	}
	ext_tsk();
}

void checkButtonKeep(VP_INT exinf)
{
	FLGPTN flgptn;
	T_RFLG pk_rflg;
	static int counter = 0;
	while(1){
		slp_tsk();
		/*SCI1_printf("counter :  %d\n",counter);*/
		counter++;
		if(counter==100){
			counter=0;
			ref_flg(flgID,&pk_rflg);
			SCI1_printf("flg :  %d\n",pk_rflg.flgptn);
			switch(pk_rflg.flgptn){
				case 1:
					/* B0 */
					turnOffLed(0);
					break;
				case 2:
					/* B0 */
					turnOffLed(1);
					break;
				default:
					break;
			}
		}
	}
	ext_tsk();
}
