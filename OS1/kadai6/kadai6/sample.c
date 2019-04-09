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
	act_tsk(TSKID_2);	/* TASKID_2�͐ÓI���� */
}


void taskA(VP_INT exinf)
{
	char *msg;
	int i;
	while(1){
		get_mpf(MPFID_0, (VP)&msg); /* ���L�������̊l�� */
		mymemcpy(msg, "National Institute of Technology, Tokyo College\0", 48);
		for(i=0;i<48;i++)SCI1_printf("%c",msg[47-i]);
		SCI1_printf("\n");
		rel_mpf(MPFID_0, (VP)msg); /* ���L�������̉�� */
		dly_tsk(1000);
	}
}

void taskB(VP_INT exinf)
{
	char *msg;
	int i;
	while(1){
		get_mpf(MPFID_0, (VP)&msg); /* ���L�������̊l�� */
		mymemcpy(msg, "National Institute of Technology, Tokyo College\0", 48);
		for(i=0;i<48;i++)if(i%2!=0)SCI1_printf("%c",msg[i]);
		SCI1_printf("\n");
		rel_mpf(MPFID_0, (VP)msg); /* ���L�������̉�� */
		dly_tsk(1000);
	}
}

void taskC(VP_INT exinf)
{
	char *msg;
	int i;
	while(1){
		get_mpf(MPFID_0, (VP)&msg); /* ���L�������̊l�� */
		mymemcpy(msg, "National Institute of Technology, Tokyo College\0", 48);
		for(i=0;i<48;i++)if(i%2==0)SCI1_printf("%c",msg[i]);
		SCI1_printf("\n");
		rel_mpf(MPFID_0, (VP)msg); /* ���L�������̉�� */
		dly_tsk(1000);
	}
}

void mymemcpy(char *d, char *s, int size)
{
    while(size-- > 0) *d++ = *s++;
}


