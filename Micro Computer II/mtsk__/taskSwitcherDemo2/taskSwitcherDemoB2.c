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

context_t context0,context1; /*�R���e�L�X�g�o�b�t�@�̎���*/
int tasksw=0; /* 0 �܂��� 1 �ғ����̃^�X�N�ԍ�*/
unsigned long int systemstackPtr;  /*�X�C�b�`���p�X�^�b�N�|�C���^�ޔ��ꏊ*/

/*�R���e�L�X�g�o�b�t�@�̒��̃��W�X�^�̕\���@�m�F�p*/
void printContext1(context_t *con)
{
	unsigned long int *currentPtr=(unsigned long int *)(con->Ber7);
	SCI1_printf("ER0 %08lx    ",currentPtr[0]);
	SCI1_printf("ER4 %08lx\n",  currentPtr[4]);
	SCI1_printf("ER1 %08lx    ",currentPtr[1]);
	SCI1_printf("ER5 %08lx\n",  currentPtr[5]);
	SCI1_printf("ER2 %08lx    ",currentPtr[2]);
	SCI1_printf("ER6 %08lx\n",  currentPtr[6]);
	SCI1_printf("ER3 %08lx    ",currentPtr[3]);
	SCI1_printf("ER7 %08lx\n",con->Ber7);
}

/*�X�^�b�N�̂������ӂ̕\��*/
void printStackArea(context_t *con)
{
	unsigned long int address=(unsigned long int)(&(con->stack0))+4;
	int i;
	SCI1_printf("tail of stack + 1 =%05lx\n",address);
	address-=0x30;
	address&=0xfffffff0;
	SCI1_printf("address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F\n");
	for (i=0; i<0x40; i++,address++) {
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
	context0.Ber7=(unsigned long int)&context0.Ber0;
	SCI1_printf("task0,stack,er7=%p %08lx %08lx\n", task0, context0.stack0.returnAddress, context0.Ber7);

	context1.stack0.returnAddress=(unsigned long int)task1;
	context1.Ber7=(unsigned long int)&context1.Ber0;
	SCI1_printf("task1,stack,er7=%p %08lx %08lx\n", task1, context1.stack0.returnAddress, context1.Ber7);
	
	printContext();

	startTimer01();  /*���Ԋ��荞�݃^�C�}�X�^�[�gch0,ch1*/

	/*�����܂ł�2�̃^�X�N�̋N�����������B�ŏ���task0���N������*/
	tasksw=0;
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
�i�P�j���݂̃^�X�N��task0,task1�̂ǂ���ł����������o
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
    mov.w  @_tasksw, r0  ;���O�̃^�X�N�ԍ��̎擾
    cmp.w  #1, r0
    beq RETURNEDFROMTASK1

RETURNEDFROMTASK0:
    ;���O���^�X�N0�̂Ƃ��̃^�X�N�X�C�b�`���
    mov.w #1, r0         ;���̃^�X�N�ԍ���1
    mov.w r0, @_tasksw   ;���̃^�X�N�ԍ���ϐ�tasksw�ɕۑ�
    ;�X�^�b�N�|�C���^���R���e�L�X�g0��Ber7�ɕۑ�
    mov.l  er7,  @_context0; (context0��context0.Ber7�͓����A�h���X)

    ;�����Ԃ̕\��
    mov.l  @_systemstackPtr,  er7 ;�X�C�b�`���̃X�^�b�N�|�C���^�̕��A
    jsr @_printContext            ;context�̃X�i�b�v�V���b�g�i�m�F�p�j
    jsr @_blinkLED                ;LED�_�Ł@�i����_���p�j�����ł͉������Ă��悢���Ƃ̌���
    mov.l  er7,  @_systemstackPtr ;�����p�̃X�^�b�N�̕ۑ�

    ;�R���e�L�X�g1��Ber7���X�^�b�N�|�C���^�ɃZ�b�g
    mov.l  @_context1, er7 ; (context1��context1.Ber7�͓����A�h���X)
    bra GONEXTTASK

RETURNEDFROMTASK1:
    ;���O���^�X�N1�̂Ƃ��̃^�X�N�X�C�b�`���
    mov.w #0, r0         ;���̃^�X�N�ԍ���0
    mov.w r0, @_tasksw   ;���̃^�X�N�ԍ���ϐ�tasksw�ɕۑ�
    ;�X�^�b�N�|�C���^���R���e�L�X�g�P��Ber7�ɕۑ�
    mov.l  er7,  @_context1; (context1��context1.Ber7�͓����A�h���X)

    ;�����Ԃ̕\��
    mov.l  @_systemstackPtr,  er7 ;�X�C�b�`���̃X�^�b�N�|�C���^�̕��A
    jsr @_printContext            ;context�̃X�i�b�v�V���b�g�i�m�F�p�j
    jsr @_blinkLED                ;LED�_�Ł@�i����_���p�j�����ł͉������Ă��悢���Ƃ̌���
    mov.l  er7,  @_systemstackPtr ;�����p�̃X�^�b�N�̕ۑ�

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


/*
  *** task switcher demo ***

task0,stack,er7=00000E4E 00000e4e 000fefa8
task1,stack,er7=00000E7E 00000e7e 000ff04c
  context for task0
ER0 00000000    ER4 00000000
ER1 00000000    ER5 00000000
ER2 00000000    ER6 00000000
ER3 00000000    ER7 000fefa8
tail of stack + 1 =fefc8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef90 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fefa0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fefb0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fefc0 : 00 00 00 00 00 00 0e 4e 00 0f f0 4c 00 00 00 00
  context for task1
ER0 00000000    ER4 00000000
ER1 00000000    ER5 00000000
ER2 00000000    ER6 00000000
ER3 00000000    ER7 000ff04c
tail of stack + 1 =ff06c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff030 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff040 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff050 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff060 : 00 00 00 00 00 00 00 00 00 00 0e 7e 00 00 00 00
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
ER2 00000000    ER6 00000030
ER3 00000000    ER7 000fefa4
tail of stack + 1 =fefc8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef90 : 03 5a 00 2b 00 00 03 3c 00 0a 00 00 06 be 00 00
fefa0 : 00 00 00 00 03 be 00 14 00 00 00 11 00 00 00 00
fefb0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 30
fefc0 : 21 00 0e 42 00 00 0e 72 00 0f f0 4c 00 00 00 00
  context for task1
ER0 00000000    ER4 00000000
ER1 00000000    ER5 00000000
ER2 00000000    ER6 00000000
ER3 00000000    ER7 000ff04c
tail of stack + 1 =ff06c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff030 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff040 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff050 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff060 : 00 00 00 00 00 00 00 00 00 00 0e 7e 00 0f ff 08
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
  context for task0
ER0 03be0014    ER4 00000000
ER1 00000011    ER5 00000000
ER2 00000000    ER6 00000030
ER3 00000000    ER7 000fefa4
tail of stack + 1 =fefc8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef90 : 03 5a 00 2b 00 00 03 3c 00 0a 00 00 06 be 00 00
fefa0 : 00 00 00 00 03 be 00 14 00 00 00 11 00 00 00 00
fefb0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 30
fefc0 : 21 00 0e 42 00 00 0e 72 00 0f f0 4c 00 00 00 00
  context for task1
ER0 0000135f    ER4 00000000
ER1 00000300    ER5 00000000
ER2 00000000    ER6 00000402
ER3 00000000    ER7 000ff04c
tail of stack + 1 =ff06c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff030 : 20 00 00 00 03 5a 00 2b 00 00 03 3c 00 0a 00 00
ff040 : 06 be 00 00 00 00 00 00 00 00 00 00 00 00 13 5f
ff050 : 00 00 03 00 00 00 00 00 00 00 00 00 00 00 00 00
ff060 : 00 00 00 00 00 00 04 02 00 00 0e 9e 00 0f ff 08
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
  context for task0
ER0 03310014    ER4 00000000
ER1 0000000f    ER5 00000000
ER2 00000000    ER6 0000004a
ER3 00000000    ER7 000fefa4
tail of stack + 1 =fefc8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef90 : 03 5a 00 2b 00 00 03 3c 00 0a 00 00 06 be 00 00
fefa0 : 00 00 00 00 03 31 00 14 00 00 00 0f 00 00 00 00
fefb0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 4a
fefc0 : 21 00 0e 42 00 00 0e 72 00 0f f0 4c 00 00 00 00
  context for task1
ER0 0000135f    ER4 00000000
ER1 00000300    ER5 00000000
ER2 00000000    ER6 00000402
ER3 00000000    ER7 000ff04c
tail of stack + 1 =ff06c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff030 : 20 00 00 00 03 5a 00 2b 00 00 03 3c 00 0a 00 00
ff040 : 06 be 00 00 00 00 00 00 00 00 00 00 00 00 13 5f
ff050 : 00 00 03 00 00 00 00 00 00 00 00 00 00 00 00 00
ff060 : 00 00 00 00 00 00 04 02 00 00 0e 9e 00 0f ff 08
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
task1 1045
task1 1046
task1 1047
task1 1048
task1 1049
task1 1050
task1 1051
task1 1052
  context for task0
ER0 03310014    ER4 00000000
ER1 0000000f    ER5 00000000
ER2 00000000    ER6 0000004a
ER3 00000000    ER7 000fefa4
tail of stack + 1 =fefc8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef90 : 03 5a 00 2b 00 00 03 3c 00 0a 00 00 06 be 00 00
fefa0 : 00 00 00 00 03 31 00 14 00 00 00 0f 00 00 00 00
fefb0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 4a
fefc0 : 21 00 0e 42 00 00 0e 72 00 0f f0 48 00 00 00 00
  context for task1
ER0 01e40014    ER4 00000000
ER1 00000003    ER5 00000000
ER2 00000000    ER6 0000041c
ER3 00000000    ER7 000ff048
tail of stack + 1 =ff06c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff030 : 20 00 00 00 03 5a 00 2b 00 00 03 3c 00 0a 00 00
ff040 : 06 be 00 00 00 00 00 00 01 e4 00 14 00 00 00 03
ff050 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff060 : 00 00 04 1c 21 00 0e 42 00 00 0e a4 00 0f ff 08
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
  context for task0
ER0 04ea0014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 00000000
ER3 00000000    ER7 000fefa4
tail of stack + 1 =fefc8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef90 : 03 5a 00 2b 00 00 03 3c 00 0a 00 00 06 be 00 00
fefa0 : 00 00 00 00 04 ea 00 14 00 00 00 13 00 00 00 00
fefb0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fefc0 : 21 00 0e 42 00 00 0e 72 00 0f f0 48 00 00 00 00
  context for task1
ER0 01e40014    ER4 00000000
ER1 00000003    ER5 00000000
ER2 00000000    ER6 0000041c
ER3 00000000    ER7 000ff048
tail of stack + 1 =ff06c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff030 : 20 00 00 00 03 5a 00 2b 00 00 03 3c 00 0a 00 00
ff040 : 06 be 00 00 00 00 00 00 01 e4 00 14 00 00 00 03
ff050 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff060 : 00 00 04 1c 21 00 0e 42 00 00 0e a4 00 0f ff 08
task1 1053
task1 1054
task1 1055
task1 1056
task1 1057
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
  context for task0
ER0 04ea0014    ER4 00000000
ER1 00000013    ER5 00000000
ER2 00000000    ER6 00000000
ER3 00000000    ER7 000fefa4
tail of stack + 1 =fefc8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef90 : 03 5a 00 2b 00 00 03 3c 00 0a 00 00 06 be 00 00
fefa0 : 00 00 00 00 04 ea 00 14 00 00 00 13 00 00 00 00
fefb0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fefc0 : 21 00 0e 42 00 00 0e 72 00 0f f0 48 00 00 00 00
  context for task1
ER0 04070014    ER4 00000000
ER1 00000007    ER5 00000000
ER2 00000000    ER6 00000436
ER3 00000000    ER7 000ff048
tail of stack + 1 =ff06c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff030 : 20 00 00 00 03 5a 00 2b 00 00 03 3c 00 0a 00 00
ff040 : 06 be 00 00 00 00 00 00 04 07 00 14 00 00 00 07
ff050 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff060 : 00 00 04 36 21 00 0e 42 00 00 0e a4 00 0f ff 08
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
  context for task0
ER0 00001354    ER4 00000000
ER1 00000300    ER5 00000000
ER2 00000000    ER6 0000001b
ER3 00000000    ER7 000fefa8
tail of stack + 1 =fefc8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef90 : 03 5a 00 2b 00 00 03 3c 00 0a 00 00 06 be 00 00
fefa0 : 00 00 00 00 00 00 00 00 00 00 13 54 00 00 03 00
fefb0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fefc0 : 00 00 00 1b 00 00 0e 6c 00 0f f0 48 00 00 00 00
  context for task1
ER0 04070014    ER4 00000000
ER1 00000007    ER5 00000000
ER2 00000000    ER6 00000436
ER3 00000000    ER7 000ff048
tail of stack + 1 =ff06c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff030 : 20 00 00 00 03 5a 00 2b 00 00 03 3c 00 0a 00 00
ff040 : 06 be 00 00 00 00 00 00 04 07 00 14 00 00 00 07
ff050 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff060 : 00 00 04 36 21 00 0e 42 00 00 0e a4 00 0f ff 08
task1 1079
task1 1080
task1 1081
task1 1082
task1 1083
task1 1084
task1 1085
task1 1086
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
  context for task0
ER0 00001354    ER4 00000000
ER1 00000300    ER5 00000000
ER2 00000000    ER6 0000001b
ER3 00000000    ER7 000fefa8
tail of stack + 1 =fefc8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef90 : 03 5a 00 2b 00 00 03 3c 00 0a 00 00 06 be 00 00
fefa0 : 00 00 00 00 00 00 00 00 00 00 13 54 00 00 03 00
fefb0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fefc0 : 00 00 00 1b 00 00 0e 6c 00 0f f0 48 00 00 00 00
  context for task1
ER0 03110014    ER4 00000000
ER1 00000005    ER5 00000000
ER2 00000000    ER6 000003ec
ER3 00000000    ER7 000ff048
tail of stack + 1 =ff06c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff030 : 20 00 00 00 03 5a 00 2b 00 00 03 3c 00 0a 00 00
ff040 : 06 be 00 00 00 00 00 00 03 11 00 14 00 00 00 05
ff050 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff060 : 00 00 03 ec 21 00 0e 42 00 00 0e a4 00 0f ff 08
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
task0   49
task0   50
task0   51
task0   52
task0   53
  context for task0
ER0 01c90014    ER4 00000000
ER1 00000003    ER5 00000000
ER2 00000000    ER6 00000035
ER3 00000000    ER7 000fefa4
tail of stack + 1 =fefc8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef90 : 03 5a 00 2b 00 00 03 3c 00 0a 00 00 06 be 00 00
fefa0 : 00 00 00 00 01 c9 00 14 00 00 00 03 00 00 00 00
fefb0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 35
fefc0 : 21 00 0e 42 00 00 0e 72 00 0f f0 48 00 00 00 00
  context for task1
ER0 03110014    ER4 00000000
ER1 00000005    ER5 00000000
ER2 00000000    ER6 000003ec
ER3 00000000    ER7 000ff048
tail of stack + 1 =ff06c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff030 : 20 00 00 00 03 5a 00 2b 00 00 03 3c 00 0a 00 00
ff040 : 06 be 00 00 00 00 00 00 03 11 00 14 00 00 00 05
ff050 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff060 : 00 00 03 ec 21 00 0e 42 00 00 0e a4 00 0f ff 08
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
task1 1029
task1 1030
  context for task0
ER0 01c90014    ER4 00000000
ER1 00000003    ER5 00000000
ER2 00000000    ER6 00000035
ER3 00000000    ER7 000fefa4
tail of stack + 1 =fefc8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef90 : 03 5a 00 2b 00 00 03 3c 00 0a 00 00 06 be 00 00
fefa0 : 00 00 00 00 01 c9 00 14 00 00 00 03 00 00 00 00
fefb0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 35
fefc0 : 21 00 0e 42 00 00 0e 72 00 0f f0 48 00 00 00 00
  context for task1
ER0 05330014    ER4 00000000
ER1 00000009    ER5 00000000
ER2 00000000    ER6 00000406
ER3 00000000    ER7 000ff048
tail of stack + 1 =ff06c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff030 : 20 00 00 00 03 5a 00 2b 00 00 03 3c 00 0a 00 00
ff040 : 06 be 00 00 00 00 00 00 05 33 00 14 00 00 00 09
ff050 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff060 : 00 00 04 06 21 00 0e 42 00 00 0e a4 00 0f ff 08
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
task0   78
task0   79
  context for task0
ER0 03ed0014    ER4 00000000
ER1 00000007    ER5 00000000
ER2 00000000    ER6 0000004f
ER3 00000000    ER7 000fefa4
tail of stack + 1 =fefc8
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
fef90 : 03 5a 00 2b 00 00 03 3c 00 0a 00 00 06 be 00 00
fefa0 : 00 00 00 00 03 ed 00 14 00 00 00 07 00 00 00 00
fefb0 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 4f
fefc0 : 21 00 0e 42 00 00 0e 72 00 0f f0 48 00 00 00 00
  context for task1
ER0 05330014    ER4 00000000
ER1 00000009    ER5 00000000
ER2 00000000    ER6 00000406
ER3 00000000    ER7 000ff048
tail of stack + 1 =ff06c
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ff030 : 20 00 00 00 03 5a 00 2b 00 00 03 3c 00 0a 00 00
ff040 : 06 be 00 00 00 00 00 00 05 33 00 14 00 00 00 09
ff050 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ff060 : 00 00 04 06 21 00 0e 42 00 00 0e a4 00 0f ff 08
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
*/