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

main()
{
	initLed();   /*LED���j�b�g�̏������@�_�ł����邪�C����m�F�p*/
	initSCI1();  /*�V���A���ʐM�̏�����*/
	SCI1_printf("\n\n\n  *** task switcher demo ***\n\n");
	initTimer01Int(500); /*���Ԋ��荞��500msec ITUch0,1�g�p�@���̃^�C�~���O�Ń^�X�N�؂�ւ����N����*/
	E_INT();        /*CPU���荞�݋���*/

	/*�R���e�L�X�g�o�b�t�@�ɃR���e�L�X�g���Q�̍쐬*/
	context0.stack0.returnAddress=(unsigned long int)task0;
	context0.Ber7=(unsigned long int)&(context0.Ber0);

	context1.stack0.returnAddress=(unsigned long int)task1;
	context1.Ber7=(unsigned long int)&(context1.Ber0);

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
    ;�R���e�L�X�g1��Ber7���X�^�b�N�|�C���^�ɃZ�b�g
    mov.l  @_context1, er7 ; (context1��context1.Ber7�͓����A�h���X)
    bra GONEXTTASK

RETURNEDFROMTASK1:
    ;���O���^�X�N1�̂Ƃ��̃^�X�N�X�C�b�`���
    mov.w #0, r0         ;���̃^�X�N�ԍ���0
    mov.w r0, @_tasksw   ;���̃^�X�N�ԍ���ϐ�tasksw�ɕۑ�
    ;�X�^�b�N�|�C���^���R���e�L�X�g�P��Ber7�ɕۑ�
    mov.l  er7,  @_context1; (context1��context1.Ber7�͓����A�h���X)
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

/*
  *** task switcher demo ***

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
task1 1049
task1 1050
task1 1051
task1 1052
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
task0   98
task0   99
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
task1 1098
task1 1099
task1 1000
task1 1001
task1 1002
task1 1003
task1 1004
task1 1005

*/