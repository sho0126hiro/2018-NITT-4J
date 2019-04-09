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

/***************�@�Q�̃^�X�N�̎��́@�����܂Ł@********************/

typedef union {
	unsigned char Bccr;
	unsigned long int returnAddress;
} stack_t;

typedef struct {
	unsigned char stack[128]; /*stack��stack0�̍��킳�������̂����ۂ̃X�^�b�N*/
	stack_t stack0;           /*������Ԃ͂����ɖ߂�A�h���X��CCR�������Ă���*/
	unsigned long int Ber0;   /*������艺��Ber0�`Ber7�͊e���W�X�^�̕ۑ��̈�*/
	unsigned long int Ber1;
	unsigned long int Ber2;
	unsigned long int Ber3;
	unsigned long int Ber4;
	unsigned long int Ber5;
	unsigned long int Ber6;
	unsigned long int Ber7; /*������Ԃł�stack0�������Ă���*/
} context_t;

context_t context0,context1; /*�R���e�L�X�g�o�b�t�@�̎���*/

int tasksw=0; /* 0 �܂��� 1 �F�ǂ���̃^�X�N�����s����Ă��邩�������Ă���*/
unsigned long int Ber0;  /*ER0�̑ޔ��ꏊ�@�^�X�N�X�C�b�`���N������ɂ�����Ǝg��*/
const unsigned long int buff0Address=(unsigned long int)&context0.Ber0;
const unsigned long int buff1Address=(unsigned long int)&context1.Ber0;
const unsigned long int stackPtr0Address=(unsigned long int)&context0.Ber7;
const unsigned long int stackPtr1Address=(unsigned long int)&context1.Ber7;
unsigned long int systemstackPtr;  /*�X�C�b�`���p�X�^�b�N�|�C���^�ޔ��ꏊ*/

/*�R���e�L�X�g�o�b�t�@�̒��̃��W�X�^�̕\���@�m�F�p*/
void printContext1(context_t *con)
{
	SCI1_printf("ER0 %08lx    ",con->Ber0);
	SCI1_printf("ER4 %08lx\n",con->Ber4);
	SCI1_printf("ER1 %08lx    ",con->Ber1);
	SCI1_printf("ER5 %08lx\n",con->Ber5);
	SCI1_printf("ER2 %08lx    ",con->Ber2);
	SCI1_printf("ER6 %08lx\n",con->Ber6);
	SCI1_printf("ER3 %08lx    ",con->Ber3);
	SCI1_printf("ER7 %08lx\n",con->Ber7);
}

/*�X�^�b�N�̂������ӂ̕\��*/
void printStackArea(context_t *con)
{
	unsigned long int address=(unsigned long int)(&(con->Ber0));
	int i;
	address-=0x20;
	address&=0xfffffff0;
	SCI1_printf("tail of stack + 1 =%05lx\n",&(con->Ber0));
	SCI1_printf("address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F\n");
	for (i=0; i<0x30; i++,address++) {
		if (i%0x10==0) SCI1_printf ("%05lx : ",address);
		SCI1_printf("%02x ",*(unsigned char*)address);
		if (i%0x10==0xf) SCI1_printf("\n");
	}
}

/*�R���e�L�X�g�o�b�t�@�̃��W�X�^�\���֐��@�m�F�p*/
void printContext(void)
{
	SCI1_printf("  context for task0\n");
	printContext1(&context0);
	printStackArea(&context0);
	SCI1_printf("  context for task1\n");
	printContext1(&context1);
	printStackArea(&context1);
}

main()
{
	initLed();   /*LED���j�b�g�̏������@�_�ł����邪�C����m�F�p*/
	initSCI1();  /*�V���A���ʐM�̏�����*/
	SCI1_printf("\n\n\n  *** task switcher demo ***\n\n");
	initTimer01Int(500); /*���Ԋ��荞��500msec ITUch0,1�g�p�@���̃^�C�~���O�Ń^�X�N�؂�ւ����N����*/
	E_INT();        /*CPU���荞�݋���*/

	/*�R���e�L�X�g�o�b�t�@�ɃR���e�L�X�g���Q�̍쐬*/
	context0.stack0.returnAddress=(unsigned long int)task0;
	context0.Ber7=(unsigned long int)&(context0.stack0);
	SCI1_printf("task0,stack,er7=%p %08lx %08lx\n", task0, context0.stack0.returnAddress, context0.Ber7);

	context1.stack0.returnAddress=(unsigned long int)task1;
	context1.Ber7=(unsigned long int)&(context1.stack0);
	SCI1_printf("task1,stack,er7=%p %08lx %08lx\n", task1, context1.stack0.returnAddress, context1.Ber7);
	
	printContext();

	startTimer01();  /*���Ԋ��荞�݃^�C�}�X�^�[�gch0,ch1*/

	/*�����܂ł�2�̃^�X�N�̋N�����������B�ŏ���task0���N������*/
	tasksw=0;
#pragma asm
	mov.l  er7,  @_systemstackPtr  ;�����̃X�^�b�N�|�C���^��ޔ�
	mov.l  @_stackPtr0Address, er0 ;�^�X�N0�̃X�^�b�N�|�C���^��ݒ�i���A�Ɠ����菇�j
	mov.l  @er0, er7               ;     (er0�o�R��er7(=SP)�ɐݒ�)
	rte                            ;ReTurn from Exception �ɂ��^�X�N0�N��
#pragma endasm

} /*end of main*/


/*���̍�Ƃ͂��܂��C�C���^�[�o���^�C�}�̓��삪�Ď��ł���*/
void blinkLED()
{
	static int tick=0;
	if (tick==1) {
		turnOnLed(0);
		turnOffLed(1);
	} else {
		turnOffLed(0);
		turnOnLed(1);
	}
	tick=1-tick;
}


/*�x�N�g���e�[�u���̐ݒ�*/
#pragma asm
	.SECTION    MYVEC, DATA, LOCATE=H'000070
	.ORG        H'000070  ;IMIA1
	.DATA.L     _TaskSwitcher
	.SECTION    P,CODE,ALIGN=2 ;�����Y��Ă͂����Ȃ�
#pragma endasm


/*
�C���^�[�o���^�C�}���荞�݂ŋN�����郋�[�`���^�^�X�N�X�C�b�`���{��
�^�X�N�؂�ւ��̍�Ƃ��s��
TaskSwitcher�ł͎��̂��Ƃ��s��
�i�P�j���݂̃^�X�N��task0,task1�̂ǂ���ł����������o
�i�Q�j���݂̑S���W�X�^��context0�C�܂���context1�Ƃ��ĕۑ�
�i�R�j���̃^�X�N�ɂނ���context0�C�܂���context1��S���W�X�^�ɍڂ���
�i�S�jrte�ŐV�^�X�N���N���i���荞�݂���߂�ӂ������j

�������C�^�X�N�X�C�b�`�����N���������_�ł́C���ׂẴ��W�X�^�́C
�X�C�b�`���N���O�ɓ��삵�Ă����^�X�N���g�p���ł���B
���̂��߁C�X�C�b�`�����N������ɂ����āC�S���W�X�^��ۑ�����O�ɂ�������
���W�X�^���g�p����ꍇ�́C���̃��W�X�^��ޔ����C��Ƃ��I���������_�ŕ��A����
�S���W�X�^���R���e�L�X�g�ۑ��ꏊ�ɕۑ�����菇�ƂȂ�B�ȉ��́��Q��
*/
#pragma asm
_TaskSwitcher:                   ; function: TaskSwitcher
	;�^�C�}���j�b�g�Ɋ��荞�݂��󂯕t�������Ƃ�m�点��
	BCLR.B #0,@H'FFFF71:8         ;ITU1.TSR.BIT.IMFA=0;

	; ** ���R���e�L�X�g�ۑ� **
	mov.l  er0,  @_Ber0  ;���O�^�X�N�ԍ��m�F�̂���ER0���g�������̂�ER0��ޔ�����
	mov.w  @_tasksw, r0
	cmp.w  #1, r0         ;r0��1�ł��邩�ǂ������ׂ�
	beq    RETUNEDFROMTASK1  ;���O���^�X�N�P�C�����^�X�N�O�Ȃ�W�����v
RETUNEDFROMTASK0:
	mov.w #1, r0          ;���̃^�X�N�̓^�X�N1
	mov.w  r0,  @_tasksw  ;���̒i�K�ŕϐ�tasksw�̒��g�͎��̃R���e�L�X�g�ԍ�
	;���O�̓^�X�N�O�������̂ŃR���e�L�X�g�O�ɕۑ����鏀��
	mov.l  @_stackPtr0Address, er0
	bra SAVECONTEXT
RETUNEDFROMTASK1:
	mov.w #0, r0          ;���̃^�X�N�̓^�X�N0
	mov.w  r0,  @_tasksw  ;���̒i�K�ŕϐ�tasksw�̒��g�͎��̃R���e�L�X�g�ԍ�
	;���O�̓^�X�N�P�������̂ŃR���e�L�X�g�P�ɕۑ����鏀��
	mov.l  @_stackPtr1Address, er0
SAVECONTEXT:
	;�R���e�L�X�g�̕ۑ�
	mov.l  er7, @er0  ;er0�̎w���Ă���A�h���X��er7(=SP)��ۑ�����
	mov.l  er0, er7   ;er0�̒l��er7(=SP)�ɐݒ肷��
	mov.l  @_Ber0,  er0                            ;ER0���g���I�����̂ŕ��A����
	push.l er6
	push.l er5
	push.l er4
	push.l er3
	push.l er2
	push.l er1
	push.l er0

	;���̒i�K�ŁC���ׂẴ��W�X�^���X�C�b�`�������R�Ɏg����悤�ɂȂ���
	mov.l  @_systemstackPtr,  er7 ;����(�X�C�b�`��)�p�̃X�^�b�N�̕��A

	;���̒i�K�ŁC�X�C�b�`���p�̃X�^�b�N���g����悤�ɂȂ���
	jsr @_printContext            ;context�̃X�i�b�v�V���b�g�i�m�F�p�j
	jsr @_blinkLED                ;LED�_�Ł@�i����_���p�j
	mov.l  er7,  @_systemstackPtr ;����(�X�C�b�`��)�p�̃X�^�b�N�̕ۑ�

	; ** ���Ɏ��s���ׂ��V�R���e�L�X�g�ݒ� **
	mov.w  @_tasksw, r0  ;�ϐ�tasksw�̒��g�͎��̃^�X�N�ԍ��ł���
	cmp.w  #1, r0
	beq    SETREADYTASK1  ;�V�^�X�N���P�Ȃ�W�����v
SETREADYTASK0:
	;�R���e�L�X�g�O�p�̃X�^�b�N���w���悤�ɃX�^�b�N�|�C���^��ݒ�
	mov.l  @_buff0Address, er7
	bra SETCONTEXTANDGO
SETREADYTASK1:
	;�R���e�L�X�g�P�p�̃X�^�b�N���w���悤�ɃX�^�b�N�|�C���^��ݒ�
	mov.l  @_buff1Address, er7
SETCONTEXTANDGO:
	;�R���e�L�X�g�𕜋������āC���̃^�X�N�N��
	pop.l  er0
	pop.l  er1
	pop.l  er2
	pop.l  er3
	pop.l  er4
	pop.l  er5
	pop.l  er6
	pop.l  er7

	rte                            ;ReTurn from Exception �ɂ��V�^�X�N�N��

#pragma endasm

/*
���s����

  *** task switcher demo ***

task0,stack,er7=00000E4E 00000e4e 000fefa4
task1,stack,er7=00000E7E 00000e7e 000ff048
  context for task0
ER0 00000000    ER4 00000000
ER1 00000000    ER5 00000000
ER2 00000000    ER6 00000000
ER3 00000000    ER7 000fefa4
tail of stack + 1 =fefa8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fef90 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fefa0 : 00 00 00 00 00 00 0e 4e 00 00 00 00 00 00 00 00
  context for task1
ER0 00000000    ER4 00000000
ER1 00000000    ER5 00000000
ER2 00000000    ER6 00000000
ER3 00000000    ER7 000ff048
tail of stack + 1 =ff04c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff020 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff030 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff040 : 00 00 00 00 00 00 00 00 00 00 0e 7e 00 00 00 00
task0    0
task0    1
task0    2
task0    3
task0    4
task0    5
task0    6
task0    7
task0    8
task0    9
task0   10
task0   11
task0   12
task0   13
task0   14
task0   15
task0   16
task0   17
task0   18
task0   19
task0   20
task0   21
task0   22
task0   23
task0   24
task0   25
task0   26
task0   27
task0   28
task0   29
task0   30
task0   31
task0   32
task0   33
task0   34
task0   35
task0   36
task0   37
task0   38
task0   39
task0   40
task0   41
task0   42
task0   43
task0   44
task0   45
task0   46
task0   47
task0   48
  context for task0
ER0 03be0014    ER4 00000000
ER1 00000011    ER5 00000000
ER2 00000000    ER6 000f0030
ER3 00000000    ER7 000fefa0
tail of stack + 1 =fefa8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fef90 : 00 04 00 00 0c b4 00 0f ef a6 00 0f 00 30 00 00
fefa0 : 21 00 0e 42 00 00 0e 72 03 be 00 14 00 00 00 11
  context for task1
ER0 00000000    ER4 00000000
ER1 00000000    ER5 00000000
ER2 00000000    ER6 00000000
ER3 00000000    ER7 000ff048
tail of stack + 1 =ff04c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff020 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff030 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff040 : 00 00 00 00 00 00 00 00 00 00 0e 7e 00 00 00 00
task1 1000
task1 1001
task1 1002
task1 1003
task1 1004
task1 1005
task1 1006
task1 1007
task1 1008
task1 1009
task1 1010
task1 1011
task1 1012
task1 1013
task1 1014
task1 1015
task1 1016
task1 1017
task1 1018
task1 1019
task1 1020
task1 1021
task1 1022
task1 1023
task1 1024
task1 1025
task1 1026
task1 1027
task1 1028
  context for task0
ER0 03be0014    ER4 00000000
ER1 00000011    ER5 00000000
ER2 00000000    ER6 000f0030
ER3 00000000    ER7 000fefa0
tail of stack + 1 =fefa8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fef90 : 00 04 00 00 0c b4 00 0f ef a6 00 0f 00 30 00 00
fefa0 : 21 00 0e 42 00 00 0e 72 03 be 00 14 00 00 00 11
  context for task1
ER0 003a0014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 00000404
ER3 00000000    ER7 000ff044
tail of stack + 1 =ff04c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff020 : 06 be 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff030 : 00 00 00 00 00 04 00 00 0c b4 00 0f f0 4a 00 00
ff040 : 04 04 00 00 21 00 0e 42 00 00 0e a4 00 3a 00 14
task0   49
task0   50
task0   51
task0   52
task0   53
task0   54
task0   55
task0   56
task0   57
task0   58
task0   59
task0   60
task0   61
task0   62
task0   63
task0   64
task0   65
task0   66
task0   67
task0   68
task0   69
task0   70
task0   71
task0   72
task0   73
task0   74
task0   75
task0   76
task0   77
  context for task0
ER0 02a80014    ER4 00000000
ER1 00000012    ER5 00000000
ER2 00000000    ER6 000f004d
ER3 00000000    ER7 000fefa0
tail of stack + 1 =fefa8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fef90 : 00 04 00 00 0c b4 00 0f ef a6 00 0f 00 4d 00 00
fefa0 : 21 00 0e 42 00 00 0e 72 02 a8 00 14 00 00 00 12
  context for task1
ER0 003a0014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 00000404
ER3 00000000    ER7 000ff044
tail of stack + 1 =ff04c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff020 : 06 be 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff030 : 00 00 00 00 00 04 00 00 0c b4 00 0f f0 4a 00 00
ff040 : 04 04 00 00 21 00 0e 42 00 00 0e a4 00 3a 00 14
task1 1029
task1 1030
task1 1031
task1 1032
task1 1033
task1 1034
task1 1035
task1 1036
task1 1037
task1 1038
task1 1039
task1 1040
task1 1041
task1 1042
task1 1043
task1 1044
task1 1045
task1 1046
task1 1047
task1 1048
task1 1049
task1 1050
task1 1051
task1 1052
task1 1053
task1 1054
task1 1055
task1 1056
task1 1057
  context for task0
ER0 02a80014    ER4 00000000
ER1 00000012    ER5 00000000
ER2 00000000    ER6 000f004d
ER3 00000000    ER7 000fefa0
tail of stack + 1 =fefa8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fef90 : 00 04 00 00 0c b4 00 0f ef a6 00 0f 00 4d 00 00
fefa0 : 21 00 0e 42 00 00 0e 72 02 a8 00 14 00 00 00 12
  context for task1
ER0 00040014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 00000421
ER3 00000000    ER7 000ff044
tail of stack + 1 =ff04c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff020 : 06 be 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff030 : 00 00 00 00 00 04 00 00 0c b4 00 0f f0 4a 00 00
ff040 : 04 21 00 00 21 00 0e 44 00 00 0e a4 00 04 00 14
task0   78
task0   79
task0   80
task0   81
task0   82
task0   83
task0   84
task0   85
task0   86
task0   87
task0   88
task0   89
task0   90
task0   91
task0   92
task0   93
task0   94
task0   95
task0   96
task0   97
task0   98
task0   99
task0    0
task0    1
task0    2
task0    3
task0    4
task0    5
task0    6
  context for task0
ER0 01950014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 000f0006
ER3 00000000    ER7 000fefa0
tail of stack + 1 =fefa8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fef90 : 00 04 00 00 0c b4 00 0f ef a6 00 0f 00 06 00 00
fefa0 : 21 00 0e 42 00 00 0e 72 01 95 00 14 00 00 00 13
  context for task1
ER0 00040014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 00000421
ER3 00000000    ER7 000ff044
tail of stack + 1 =ff04c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff020 : 06 be 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff030 : 00 00 00 00 00 04 00 00 0c b4 00 0f f0 4a 00 00
ff040 : 04 21 00 00 21 00 0e 44 00 00 0e a4 00 04 00 14
task1 1058
task1 1059
task1 1060
task1 1061
task1 1062
task1 1063
task1 1064
task1 1065
task1 1066
task1 1067
task1 1068
task1 1069
task1 1070
task1 1071
task1 1072
task1 1073
task1 1074
task1 1075
task1 1076
task1 1077
task1 1078
task1 1079
task1 1080
task1 1081
task1 1082
task1 1083
task1 1084
task1 1085
task1 1086
  context for task0
ER0 01950014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 000f0006
ER3 00000000    ER7 000fefa0
tail of stack + 1 =fefa8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fef90 : 00 04 00 00 0c b4 00 0f ef a6 00 0f 00 06 00 00
fefa0 : 21 00 0e 42 00 00 0e 72 01 95 00 14 00 00 00 13
  context for task1
ER0 003a0014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 0000043e
ER3 00000000    ER7 000ff044
tail of stack + 1 =ff04c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff020 : 06 be 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff030 : 00 00 00 00 00 04 00 00 0c b4 00 0f f0 4a 00 00
ff040 : 04 3e 00 00 21 00 0e 44 00 00 0e a4 00 3a 00 14
task0    7
task0    8
task0    9
task0   10
task0   11
task0   12
task0   13
task0   14
task0   15
task0   16
task0   17
task0   18
task0   19
task0   20
task0   21
task0   22
task0   23
task0   24
task0   25
task0   26
task0   27
task0   28
task0   29
task0   30
task0   31
task0   32
task0   33
task0   34
task0   35
  context for task0
ER0 001e0014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 000f0023
ER3 00000000    ER7 000fefa0
tail of stack + 1 =fefa8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fef90 : 00 04 00 00 0c b4 00 0f ef a6 00 0f 00 23 00 00
fefa0 : 21 00 0e 44 00 00 0e 72 00 1e 00 14 00 00 00 13
  context for task1
ER0 003a0014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 0000043e
ER3 00000000    ER7 000ff044
tail of stack + 1 =ff04c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff020 : 06 be 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff030 : 00 00 00 00 00 04 00 00 0c b4 00 0f f0 4a 00 00
ff040 : 04 3e 00 00 21 00 0e 44 00 00 0e a4 00 3a 00 14
task1 1087
task1 1088
task1 1089
task1 1090
task1 1091
task1 1092
task1 1093
task1 1094
task1 1095
task1 1096
task1 1097
task1 1098
task1 1099
task1 1000
task1 1001
task1 1002
task1 1003
task1 1004
task1 1005
task1 1006
task1 1007
task1 1008
task1 1009
task1 1010
task1 1011
task1 1012
task1 1013
task1 1014
task1 1015
  context for task0
ER0 001e0014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 000f0023
ER3 00000000    ER7 000fefa0
tail of stack + 1 =fefa8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fef90 : 00 04 00 00 0c b4 00 0f ef a6 00 0f 00 23 00 00
fefa0 : 21 00 0e 44 00 00 0e 72 00 1e 00 14 00 00 00 13
  context for task1
ER0 00050014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 000003f7
ER3 00000000    ER7 000ff044
tail of stack + 1 =ff04c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff020 : 06 be 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff030 : 00 00 00 00 00 04 00 00 0c b4 00 0f f0 4a 00 00
ff040 : 03 f7 00 00 21 00 0e 42 00 00 0e a4 00 05 00 14
task0   36
task0   37
task0   38
task0   39
task0   40
task0   41
task0   42
task0   43
task0   44
task0   45
task0   46
task0   47
task0   48
task0   49
task0   50
task0   51
task0   52
task0   53
task0   54
task0   55
task0   56
task0   57
task0   58
task0   59
task0   60
task0   61
task0   62
task0   63
task0   64
  context for task0
ER0 00540014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 000f0040
ER3 00000000    ER7 000fefa0
tail of stack + 1 =fefa8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fef90 : 00 04 00 00 0c b4 00 0f ef a6 00 0f 00 40 00 00
fefa0 : 21 00 0e 42 00 00 0e 72 00 54 00 14 00 00 00 13
  context for task1
ER0 00050014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 000003f7
ER3 00000000    ER7 000ff044
tail of stack + 1 =ff04c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff020 : 06 be 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff030 : 00 00 00 00 00 04 00 00 0c b4 00 0f f0 4a 00 00
ff040 : 03 f7 00 00 21 00 0e 42 00 00 0e a4 00 05 00 14
task1 1016
task1 1017
task1 1018
task1 1019
task1 1020
task1 1021
task1 1022
task1 1023
task1 1024
task1 1025
task1 1026
task1 1027
task1 1028
task1 1029
task1 1030
task1 1031
task1 1032
task1 1033
task1 1034
task1 1035
task1 1036
task1 1037
task1 1038
task1 1039
task1 1040
task1 1041
task1 1042
task1 1043
task1 1044
  context for task0
ER0 00540014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 000f0040
ER3 00000000    ER7 000fefa0
tail of stack + 1 =fefa8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef80 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fef90 : 00 04 00 00 0c b4 00 0f ef a6 00 0f 00 40 00 00
fefa0 : 21 00 0e 42 00 00 0e 72 00 54 00 14 00 00 00 13
  context for task1
ER0 00390014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 00000414
ER3 00000000    ER7 000ff044
tail of stack + 1 =ff04c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff020 : 06 be 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff030 : 00 00 00 00 00 04 00 00 0c b4 00 0f f0 4a 00 00
ff040 : 04 14 00 00 21 00 0e 44 00 00 0e a4 00 39 00 14
task0   65
task0   66
task0   67
task0   68
task0   69
task0   70
task0   71
task0   72
task0   73
task0   74
task0   75
task0   76
task0   77
task0   78
task0   79
task0   80
task0   81
task0   82
task0   83
task0   84
task0   85
task0   86
task0   87

*/
