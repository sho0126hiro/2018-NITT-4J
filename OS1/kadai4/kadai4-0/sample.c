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

ER_ID cycid;
ID    cycID;

void OnHosStart(VP_INT exinf)
{
	T_CCYC pk_ccyc = {TA_HLNG,1,CYC_wupCButton,128};
	cycid = acre_cyc(&pk_ccyc);
	
	if(E_OK < cycid){
		cycID = cycid;
	}else{
		SCI1_printf("acre_cyc error %d\n",cycid);
	}
	putStringSCI1("OnHosStart: starting!\n");
	act_tsk(tskID_CHK_BTN);
}

void CYC_wupCButton(VP_INT exinf)
{
	wup_tsk(tskID_CHK_BTN);
}

void checkButton(VP_INT exinf)
{
	static int oldbutton=0;
	int button;
	int stat;
	putStringSCI1("checkButton: starting!\n");
	sta_cyc(cycID);
	while(1) {
		slp_tsk();
		/*SCI1_printf("[checkButton] getPushSW : %d \n",button);*/
		button=getPushSW();
		/*SCI1_printf("[--checkButton--] getPushSW : %d \n",button);*/
		if ((stat=(oldbutton^button))) {
			if (oldbutton<button) { /*押された*/
				/*SCI1_printf("[checkButton] oldB : %d  b : %d \n",oldbutton,button);*/
				sta_tsk(tskID_BTN_HDL,stat);
			}
			oldbutton=button;
			/*SCI1_printf("[***checkButton***] oldB : %d  b : %d \n",oldbutton,button);*/
		}
	}
	ext_tsk();
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
		break;
	case BTN1:
		SCI1_printf("B1 PUSHED  \n");
		break;
	case BTN2:
		SCI1_printf("B2 PUSHED  \n");
		break;
	case BTN3:
		SCI1_printf("B3 PUSHED  \n");
		break;
	default:
		break;
	}
	ext_tsk();
}

