/**********************************************************
�C���^�[�o���^�C�}���荞�݂ɂ���ĂQ�̃^�X�N�̐؂�ւ����s��
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

/***************�@�Q�̃^�X�N�̎��́@��������@********************/
void msecwait(int msec)
/*mesc�ԂȂɂ����Ȃ����ԉ҂��֐�*/
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<1588;j++);    /*1588�͎����ɂ���ċ��߂��l*/
	}
}

void task0(void)
{
	int cnt=0;
	while (1) {
		D_INT();  /*���̃f���ł͒ʐM���͊��荞�݋֎~�ɂ��ă��\�[�X�̋���������Ă���*/
		SCI1_printf("task0 %4d\n",cnt);
		E_INT();
		msecwait(20);
		cnt++;
		if (cnt==100) cnt=0;
	}
}

void task1(void)
{
	int cnt=1000;
	while (1) {
		D_INT();  /*���̃f���ł͒ʐM���͊��荞�݋֎~�ɂ��ă��\�[�X�̋���������Ă���*/
		SCI1_printf("task1 %4d\n",cnt);
		E_INT();
		msecwait(20);
		cnt++;
		if (cnt==1100) cnt=1000;
	}
}

void task2(void)
{
	int cnt=10000;
	while (1) {
		D_INT();  /*���̃f���ł͒ʐM���͊��荞�݋֎~�ɂ��ă��\�[�X�̋���������Ă���*/
		SCI1_printf("task2 %5d\n",cnt);
		E_INT();
		msecwait(20);
		cnt++;
		if (cnt==11000) cnt=10000;
	}
}

/***************�@�Q�̃^�X�N�̎��́@�����܂Ł@********************/

typedef union {
	unsigned char Bccr;
	unsigned long int returnAddress;
} stack_t;

typedef struct {
	unsigned long int Ber7;   /*������Ԃł�Ber0�������Ă���*/
	unsigned char stack[128]; /*stack�`stack0�̍��킳�������̂����ۂ̃X�^�b�N*/
	unsigned long int Ber0;   /*������Ԃ���ER0������ƍl����C��̓X�^�b�N�̈ꕔ*/
	unsigned long int Ber1;   /*������Ԃ���ER1������ƍl����C��̓X�^�b�N�̈ꕔ*/
	unsigned long int Ber2;   /*������Ԃ���ER2������ƍl����C��̓X�^�b�N�̈ꕔ*/
	unsigned long int Ber3;   /*������Ԃ���ER3������ƍl����C��̓X�^�b�N�̈ꕔ*/
	unsigned long int Ber4;   /*������Ԃ���ER4������ƍl����C��̓X�^�b�N�̈ꕔ*/
	unsigned long int Ber5;   /*������Ԃ���ER5������ƍl����C��̓X�^�b�N�̈ꕔ*/
	unsigned long int Ber6;   /*������Ԃ���ER6������ƍl����C��̓X�^�b�N�̈ꕔ*/
	stack_t stack0;           /*������Ԃ͂����ɖ߂�A�h���X��CCR�������Ă���*/
} context_t;

context_t context0,context1,context2; /*�R���e�L�X�g�o�b�t�@�̎���*/
int tasksw=0; /* 0 �܂��� 1 �܂���2�@�ғ����̃^�X�N�ԍ�*/
unsigned long int systemstackPtr;  /*�X�C�b�`���p�X�^�b�N�|�C���^�ޔ��ꏊ*/

main()
{
	initLed();   /*LED���j�b�g�̏������@�_�ł����邪�C����m�F�p*/
	initSCI1();  /*�V���A���ʐM�̏�����*/
	SCI1_printf("\n\n\n  *** task switcher ***\n\n");
	initTimer01Int(500); /*���Ԋ��荞��500smsec ITUch0,1�g�p�@���̃^�C�~���O�Ń^�X�N�؂�ւ����N����*/
	E_INT();        /*CPU���荞�݋���*/

	/*�R���e�L�X�g�o�b�t�@�ɃR���e�L�X�g���Q�̍쐬*/
	context0.stack0.returnAddress=(unsigned long int)task0; /* task0�̖߂�l�̐ݒ� */
	context0.Ber7=(unsigned long int)&(context0.Ber0);/*������ */

	context1.stack0.returnAddress=(unsigned long int)task1;
	context1.Ber7=(unsigned long int)&(context1.Ber0);

    context2.stack0.returnAddress=(unsigned long int)task2;
	context2.Ber7=(unsigned long int)&(context2.Ber0);

	startTimer01();  /*���Ԋ��荞�݃^�C�}�X�^�[�gch0,ch1*/

	/*�����܂ł�2�̃^�X�N�̋N�����������B�ŏ���task0���N������*/
	tasksw=0;
    /* ���̃A�Z���u���R�[�h���N���v���O����*/
#pragma asm
    mov.l  er7,  @_systemstackPtr  ;�X�C�b�`���̃X�^�b�N�|�C���^��ޔ�
    mov.l  @_context0, er7 ;�^�X�N0�̃X�^�b�N�|�C���^�𕜋A
                           ; context0��context0.Ber7�͓����A�h���X
    pop.l  er0
    pop.l  er1
    pop.l  er2
    pop.l  er3
    pop.l  er4
    pop.l  er5
    pop.l  er6
    rte                            ;ReTurn from Exception �ɂ��^�X�N�N��
#pragma endasm

} /*end of main*/

/*�x�N�g���e�[�u���̐ݒ�*/
#pragma asm
    .SECTION    MYVEC, DATA, LOCATE=H'000070
    .ORG        H'000070  ;IMIA1
    .DATA.L     _TaskSwitcher
    .SECTION    P,CODE,ALIGN=2 ;�����Y��Ă͂����Ȃ�
#pragma endasm

/*
�C���^�[�o���^�C�}���荞�݂ŋN�����郋�[�`���C�^�X�N�؂�ւ��̍�Ƃ��s��
TaskSwitcher�ł͎��̂��Ƃ��s��
�i�P�j���݂̃^�X�N��task0,task1,task2�̂ǂ�ł����������o
�i�Q�j���݂̑S���W�X�^��context0�C�܂���context1�Ƃ��ĕۑ�
�i�R�j���̃^�X�N�ɂނ���context0�C�܂���context1��S���W�X�^�ɍڂ���
�i�S�jrte�ŐV�^�X�N���N���i���荞�݂���߂�ӂ������j
*/
#pragma asm
_TaskSwitcher:                   ; function: TaskSwitcher
    ;�^�C�}���j�b�g�Ɋ��荞�݂��󂯕t�������Ƃ�m�点��
    BCLR.B #0,@H'FFFF71:8         ;ITU1.TSR.BIT.IMFA=0;

    ; ** ���R���e�L�X�g�ۑ� **
    push.l er6
    push.l er5
    push.l er4
    push.l er3
    push.l er2
    push.l er1
    push.l er0
    mov.w  @_tasksw, r0   ;���O�̃^�X�N�ԍ��̎擾
    cmp.w  #2, r0         ; 2�Ɣ�ׂ�
    beq RETURNEDFROMTASK2 ; �����Ȃ����
    cmp.w  #1, r0         ; 1�Ɣ�ׂ�
    beq RETURNEDFROMTASK1 ; �����Ȃ����

RETURNEDFROMTASK0:
    ;���O���^�X�N0�̂Ƃ��̃^�X�N�X�C�b�`���
    mov.w #1, r0         ;���̃^�X�N�ԍ���1
    mov.w r0, @_tasksw   ;���̃^�X�N�ԍ���ϐ�tasksw�ɕۑ�
    ;�X�^�b�N�|�C���^���R���e�L�X�g0��Ber7�ɕۑ�
    mov.l  er7,  @_context0; (context0��context0.Ber7�͓����A�h���X)
    ;�R���e�L�X�g1��Ber7���X�^�b�N�|�C���^�ɃZ�b�g
    mov.l  @_context1, er7 ; (context1��context1.Ber7�͓����A�h���X)
    bra GONEXTTASK ; jump goNextTask

RETURNEDFROMTASK1:
    ;���O���^�X�N1�̂Ƃ��̃^�X�N�X�C�b�`���
    mov.w #2, r0         ;���̃^�X�N�ԍ���2
    mov.w r0, @_tasksw   ;���̃^�X�N�ԍ���ϐ�tasksw�ɕۑ�
    ;�X�^�b�N�|�C���^���R���e�L�X�g�P��Ber7�ɕۑ�
    mov.l  er7,  @_context1; (context1��context1.Ber7�͓����A�h���X)
    ;�R���e�L�X�g2��Ber7���X�^�b�N�|�C���^�ɃZ�b�g
    mov.l  @_context2, er7 ; (context2��context2.Ber7�͓����A�h���X)
    bra GONEXTTASK ; jump goNextTask

RETURNEDFROMTASK2:
    ;���O���^�X�N2�̂Ƃ��̃^�X�N�X�C�b�`���
    mov.w #0, r0         ;���̃^�X�N�ԍ���0
    mov.w r0, @_tasksw   ;���̃^�X�N�ԍ���ϐ�tasksw�ɕۑ�
    ;�X�^�b�N�|�C���^���R���e�L�X�g2��Ber7�ɕۑ�
    mov.l  er7,  @_context2; (context2��context2.Ber7�͓����A�h���X)
    ;�R���e�L�X�g0��Ber7���X�^�b�N�|�C���^�ɃZ�b�g
    mov.l  @_context0, er7 ; (context0��context0.Ber7�͓����A�h���X)

GONEXTTASK:
    pop.l  er0
    pop.l  er1
    pop.l  er2
    pop.l  er3
    pop.l  er4
    pop.l  er5
    pop.l  er6

    rte

#pragma endasm
