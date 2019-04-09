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

#pragma interrupt (TimerIntFunction)
void TimerIntFunction()
{
	lightenLED();
	done=1;
	ITU1.TSR.BIT.IMFA=0; /*�^�C�}���j�b�g�Ɋ�������t�������Ƃ�m�点��*/
}


/*
���s����
�N����LED�������Ă���̂��m�F���CEnterKey�������ƁC����ɐi��ňȉ���
�悤�ɂȂ��Ď~�܂����悤�Ɍ�����B

  *** interrupt function starting demo ***

Check LEDs. If you see LEDs are off, push [ENTER] key.

Turning on LEDs.
Done!   Check LEDs. If LEDs are lightend, OK!!
*/
