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
ID tskID1, tskID2, tskID3;

void OnHosStart(VP_INT exinf)
{
	ER_ID tskid;
	T_CTSK pk_ctsk1 = {TA_HLNG,  1, checkButton, 5, 256, NULL};
	T_CTSK pk_ctsk2 = {TA_HLNG, 1,  buttonHandler, 5, 256, NULL};
	T_CCYC pk_ccyc = {TA_HLNG,1,CYC_wupCButton,128};
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
	
	cycid = acre_cyc(&pk_ccyc);
	if(E_OK < cycid){
		cycID = cycid;
	}else{
		SCI1_printf("acre_cyc error %d\n",cycid);
	}
	putStringSCI1("OnHosStart: starting!\n");
	act_tsk(tskID1);
}

void CYC_wupCButton(VP_INT exinf)
{
	wup_tsk(tskID1);
}

void checkButton(VP_INT exinf)
{
	static int oldbutton=0;
	int button;
	int stat;
	int count;
	/*putStringSCI1("checkButton: starting!\n");*/
	sta_cyc(cycID);
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
#define	BTN2_PUSH 0x3f
#define	BTN3_PUSH 0x4f

#define BTN0_RELEASE 0x10
#define	BTN1_RELEASE 0x20
#define	BTN2_RELEASE 0x30
#define	BTN3_RELEASE 0x40


void buttonHandler(VP_INT exinf)
{
	switch (exinf) {
	case BTN0_PUSH:
		SCI1_printf("B0 PUSHED  \n");
		break;
	case BTN1_PUSH:
		SCI1_printf("B1 PUSHED  \n");
		break;
	case BTN2_PUSH:
		SCI1_printf("B2 PUSHED  \n");
		break;
	case BTN3_PUSH:
		SCI1_printf("B3 PUSHED  \n");
		break;
	case BTN0_RELEASE:
		SCI1_printf("B0 RELEASED  \n");
		break;
	case BTN1_RELEASE:
		SCI1_printf("B1 RELEASED  \n");
		break;
	case BTN2_RELEASE:
		SCI1_printf("B2 RELEASED  \n");
		break;
	case BTN3_RELEASE:
		SCI1_printf("B3 RELEASED  \n");
		break;
	default:
		break;
	}
	ext_tsk();
}

