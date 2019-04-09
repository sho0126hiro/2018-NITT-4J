#include "kernel.h"
#include "kernel_id.h"
#include "MinSys3069.h"
#include "sample.h"

/* �X�^�[�g�A�b�v���[�`������ŏ��ɌĂяo����鏉�����֐� */
/* OS�N���O�ɂ��邱�ƁiSCI�̏������Ȃǁj���s���Ă���      */
/* ���̊֐�����X�^�[�g�A�b�v���[�`���ɖ߂�����ɁC       */
/* �X�^�[�g�A�b�v���[�`����HOS���Ăяo��                  */
void preStartHos()
{
	initSCI1();              /* SCI�̏����� */
	SCI1_printf("\npreStartHos: start!\n");  /* �J�n���b�Z�[�W */
}

const static T_CTSK pk_ctsk = {TA_HLNG,  1, primeNumber, 3, 256, NULL};
const static T_CTSK pk_ctsk2 = {TA_HLNG, 1,   printLine, 2, 128, NULL};
ID tskID1, tskID2;
const static T_CFLG pk_cflg={(TA_TPRI | TA_WSGL),0};
ID flgID;

/* HOS���ōŏ��ɋN������n���h��*/
/* system.cfg���ŐÓI�ɋN������� */
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
	/* flug_id */
	flgid=acre_flg(&pk_cflg);
	if (E_OK<flgid) {
		flgID=flgid;
		SCI1_printf("OnHosStart: flgid=%d\n",flgID);
	} else {
		SCI1_printf("OnHosStart: acre_flg err %d\n",flgid);
	}
	act_tsk(tskID1);
	act_tsk(tskID2);
}

/* 1sec���ƂɃ^�C�}�̎��Ԃ�\������^�X�N */
/* system.cfg���ŐÓI�ɐ�������COnHosStart()���ŋN������Ă��� */
void printTime(VP_INT exinf)
{
	SYSTIM time;
	PRI tskpri = 1;
	ER checker;
	T_RFLG pk_rflg;
	FLGPTN flgptn;
	while (1) { /*�i�v���[�v*/
		/* �^�C�}�l�擾 */
		get_tim(&time);
		if((unsigned long int)time.ltime > 3000){
			/* 3�b�o�ߎ� */
			checker = chg_pri(tskID2,tskpri);
			if(checker != E_OK){
				SCI1_printf("ercd_tsk err %d\n",checker);
			}
		}
		
		/* �^�C�}�l�o�� */
		SCI1_printf("printTime:%8ld\n",(unsigned long int)time.ltime);
		/* 1000msec�҂�(OS��CPU���p�����ꎞ�I�ɕԂ��C���ԂɂȂ�����߂��Ă��炤) */
		dly_tsk(1000);
	}
}

/* 1���ȏ�̑f����\����������^�X�N*/
void primeNumber(VP_INT exinf){
	int num=10000;
	int i;
	int check  = 1;
	int count  = 0;
	int count2 = 0;
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
			count2++;
			set_flg(flgID,count2);
		}
	}
}

/* ���r�������� */
void printLine(VP_INT exinf){
	T_RFLG pk_rflg;
	FLGPTN flgptn;
	while(1){
		wai_flg(flgID,65535,TWF_ORW,&flgptn);
		SCI1_printf("--------------- [%d��ڂ̕\��] ---------------\n",flgptn);
		clr_flg(flgID,~flgptn);
	}
}
