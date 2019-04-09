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
			set_flg(flgID,1);
		}
	}
}

/* ���r�������� */
void printLine(VP_INT exinf){
	T_RFLG pk_rflg;
	FLGPTN flgptn;
	while(1){
		wai_flg(flgID,1,TWF_ANDW,&flgptn);
		SCI1_printf("------------------------------\n");
		clr_flg(flgID,~1);
	}
}
/*
���s����

preStartHos: start!
OnHosStart: starting!
OnHosStart: primeNumber Pri,id= 3,8
OnHosStart: printLine Pri,id= 2,7
OnHosStart: flgid=4
primeNumber :   10007
primeNumber :   10009
primeNumber :   10037
primeNumber :   10039
primeNumber :   10061
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
primeNumber :   10427
primeNumber :   10429
primeNumber :   10433
primeNumber :   10453
primeNumber :   10457
------------------------------
primeNumber :   10459
primeNumber :   10463
primeNumber :   10477
primeNumber :   10487
primeNumber :   10499
primeNumber :   10501
primeNumber :   10513
*/