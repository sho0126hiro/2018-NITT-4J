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

/* HOS���ōŏ��ɋN������n���h��*/
/* system.cfg���ŐÓI�ɋN������� */
void OnHosStart(VP_INT exinf)
{
	putStringSCI1("OnHosStart: starting!\n");
	act_tsk(TSKID_0);	/* TASKID_0�͐ÓI���� */
	act_tsk(TSKID_1);	/* TASKID_1�͐ÓI���� */
}


void taskA(VP_INT exinf)
{
	char *msg,*msg2;
	int i;
	while(1){
		if(tget_mpf(MPFID_0, (VP)&msg,1000)!=E_TMOUT){ /* ���L�������̊l�� */
			SCI1_printf("first\n",msg);
		}
		dly_tsk(1000);
		if(tget_mpf(MPFID_0, (VP)&msg2,1000)!=E_TMOUT){ /* ���L�������̊l�� */
			SCI1_printf("second\n",msg);
		}else{
			SCI1_printf("Complete!\n");
		}
		rel_mpf(MPFID_0, (VP)msg ) ; /* ���L�������̕ԋp */
		rel_mpf(MPFID_0, (VP)msg2 ) ; /* ���L�������̕ԋp */
		dly_tsk(1000);
	}
}

void taskB(VP_INT exinf)
{
	char *msg,*msg2;
	int i;
	while(1){
		if(tget_mpf(MPFID_0, (VP)&msg,1000)!=E_TMOUT){ /* ���L�������̊l�� */
			SCI1_printf("first\n",msg);
		}
		dly_tsk(1000);
		if(tget_mpf(MPFID_0, (VP)&msg2,1000)!=E_TMOUT){ /* ���L�������̊l�� */
			SCI1_printf("second\n",msg);
		}else{
			SCI1_printf("Complete!\n");
		}
		rel_mpf(MPFID_0, (VP)msg ) ; /* ���L�������̕ԋp */
		rel_mpf(MPFID_0, (VP)msg2 ) ; /* ���L�������̕ԋp */
		dly_tsk(1000);
	}
}


void mymemcpy(char *d, char *s, int size)
{
    while(size-- > 0) *d++ = *s++;
}


