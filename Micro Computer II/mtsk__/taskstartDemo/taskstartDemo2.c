/**********************************************************
�^�C�}���荞�ݏ����ɓ������u�Ԃ̏o����
�^�C�}���荞�݂������1�񂾂����荞�݂��N����
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"


volatile int done=0; /*�ŏ���0,���荞�ݏ������I�������1�ɂȂ�*/

main()
{
	initLed();   /*LED���j�b�g�̏������@�_�ł����邪�C����m�F�p*/
	initSCI1();  /*�V���A���ʐM�̏�����*/
	SCI1_printf("\n\n\n  *** interrupt function starting demo ***\n\n");
	SCI1_printf("Check LEDs. If you see LEDs are off, push [ENTER] key.\n");
	getCharSCI1();

	initTimer01Int(500); /*���Ԋ��荞��500msec ITUch0,1�g�p*/
	E_INT();        /*CPU���荞�݋���*/
	startTimer01();  /*���Ԋ��荞�݃^�C�}�X�^�[�gch0,ch1*/

	while(!done); /*���荞�ݏ������I���܂Ń��[�v*/

	stopTimer01();   /*���Ԋ��荞�݃^�C�}�[�X�g�b�vch0,ch1*/
	D_INT();         /*CPU���荞�݋֎~*/

	SCI1_printf("Done!   Check LEDs. If LEDs are lightend, OK!!\n");
	while(1);     /*�������[�v*/
}

/*���̍�Ƃɂ����LED���_�������荞�ݏ����ɓ��������Ƃ��m�F�����*/
void lightenLED()
{
	SCI1_printf("Turning on LEDs.\n");
	turnOnLed(0);
	turnOnLed(1);
}

/*�x�N�g���e�[�u���̐ݒ�*/
#pragma asm
    .SECTION    MYVEC, DATA, LOCATE=H'000070
    .ORG        H'000070  ;IMIA1
    .DATA.L     _TimerIntFunction
    .SECTION    P,CODE,ALIGN=2 ;�����Y��Ă͂����Ȃ�
#pragma endasm

#pragma asm
_TimerIntFunction:                   ; function: _TimerIntFunction()
    ;�X�^�b�N�|�C���^�̒l�ƃX�^�b�N�̈����C�̕ϐ��ɕۑ�����
    ;�{���Ȃ�񊄂荞�݃��[�`���͂���d�������Ă���͂��Ȃ̂ŁCer0�Ȃǂ̃��W�X�^��
    ;�g�p���ł���C���荞�݃��[�`�����ł����̃��W�X�^�𗘗p����ꍇ�́C���W�X�^��
    ;���e���X�^�b�N�ɑޔ������C���荞�݃��[�`���I�����O�ɕ��A������̂����ʂ̎g�����ł���B
    ;�{�v���O�����ł́Cmain�֐��͉�����Ƃ��Ă��Ȃ��̂ŁC���W�X�^�ޔ����s���Ă��Ȃ��B

    ;  �����ɗ����؋���LED��_������֐���call
    jsr @_lightenLED

    ;  ���荞�ݏ��������������Ƃ�main�ɒm�点��
    mov.w  #1, r0
    mov.w  r0, @_done             ;C�̕ϐ�done��1����

    ;�^�C�}���j�b�g�Ɋ��荞�݂��󂯕t�������Ƃ�m�点��
    BCLR.B #0,@H'FFFF71:8         ;ITU1.TSR.BIT.IMFA=0;

    rte                    ; ReTurn from Exception
#pragma endasm


/*
���s����
�N����LED�������Ă���̂��m�F���CEnterKey�������ƁC����ɐi��ňȉ���
�悤�ɂȂ��Ď~�܂����悤�Ɍ�����B

  *** interrupt function starting demo ***

Check LEDs. If you see LEDs are off, push [ENTER] key.

Turning on LEDs.
Done!   Check LEDs. If LEDs are lightend, OK!!
*/
