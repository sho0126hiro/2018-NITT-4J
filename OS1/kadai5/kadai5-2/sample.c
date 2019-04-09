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

ID	tskIDA, tskIDB ;

/* HOS���ōŏ��ɋN������n���h��*/
/* system.cfg���ŐÓI�ɋN������� */
void OnHosStart(VP_INT exinf)
{
	const static T_CTSK pk_ctskA = { TA_HLNG, 1, primeNumber, 5, 256, NULL};
	const static T_CTSK pk_ctskB = { TA_HLNG, 1,   ButtonLED, 6, 256, NULL};
	ER_ID	tskid ;

	putStringSCI1("OnHosStart: starting!\n");

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

/* 1���ȏ�̑f����\����������^�X�N*/
void primeNumber(VP_INT exinf){
	static int num=10000;
	int i;
	int check = 1;
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
			wai_sem(SEMID_SCI); /* semapho�����̊l�� */
			SCI1_printf("primeNumber :%8d\n",num);
			sig_sem(SEMID_SCI); /* semapho�����̕ԋp */
			dly_tsk(2);
		}
		if(num == 32767) num =10000;
		num++;
	}
}

/* �{�^��1��������LED1��_���C�^�X�NA�̕\�����~ */
/* ������x�{�^��1��������LED1�������C�^�X�NA�̕\�����ĊJ */
void ButtonLED(VP_INT exinf)
{
	static int oldbutton = 0;
	static int stat=0;
	int button=0;
	int count;
	long int i,j;
	while(1){
		if(stat != 1){
			wai_sem(SEMID_SCI);
		}
		button = getPushSW();
		/*SCI1_printf("stat = %d\n",stat);*/
		if(oldbutton<button && button == 1){
			/*push button1*/
			/*�`���^�����O�h�~*/
			for(i=0;i<50000;i++)for(j=0;j<10;j++);
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
			sig_sem(SEMID_SCI);
		}else{
			/*SCI1_printf("hahaha world\n",stat);*/
		}
	}
}
