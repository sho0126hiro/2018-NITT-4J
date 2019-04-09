/**********************************************************
�^�C�}���荞�ݏ����ɓ������u�Ԃ̏o����
�^�C�}���荞�݂������1�񂾂����荞�݂��N����
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

unsigned long int stackpointer; /*�X�^�b�N�|�C���^�̒l��ۑ�����ꏊ*/
unsigned char stack[0x30];      /*�X�^�b�N�̈��ۑ�����ꏊ*/

volatile int done=0; /*�ŏ���0,���荞�ݏ������I�������1�ɂȂ�*/

void dumpStackBuffer(void)
{
	unsigned long int address=0xFFEF0;
	int i;
	SCI1_printf("address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F\n");
	for (i=0; i<0x30; i++,address++) {
		if (i%0x10==0) SCI1_printf ("%05lx : ",address);
		SCI1_printf("%02x ",stack[i]);
		if (i%0x10==0xf) SCI1_printf("\n");
	}
}


main()
{
	initLed();   /*LED���j�b�g�̏������@�_�ł����邪�C����m�F�p*/
	initSCI1();  /*�V���A���ʐM�̏�����*/
	SCI1_printf("\n\n\n  *** interrupt function starting demo ***\n\n");
	SCI1_printf("Check LEDs. If you see LEDs are off, push [ENTER] key.\n");
	getCharSCI1();

	/*�X�^�b�N�|�C���^�̒l�ƃX�^�b�N�̈��C�̕ϐ��ɕۑ�����@�A�Z���u������łȂ��Ə����Ȃ�*/
#pragma asm
    mov.l er7, @_stackpointer       ;er7(SP)�̒l��C�̕ϐ�stackpointer�Ɋi�[
                                    ;stackpointer��C�̕ϐ�stackpointer�̃A�h���X���Ӗ�����̂�
                                    ;�u@�v�����āC���̃A�h���X�̎w���ꏊ�̈Ӗ��ɂ��Ă���
    mov.l #H'FFEF0, er0             ;er0��0xffef0���i�[
    mov.l #_stack,  er1             ;er1��C�̕ϐ�stack�̃A�h���X���i�[
                                    ;���Ȃ킿C�̔z��ϐ�stack�̐擪�A�h���X
    mov.b #H'30:8,  r2h             ;r2h��0x30�i8bit�l�j���i�[
    bra   la02
la01:
    mov.b @er0+,     r2l            ;er0�̎w���Ă���o�C�g�l��r2l�Ɋi�[���C���̌�er0�̒l���P���₷
    mov.b r2l,      @er1            ;r2l�̒l���Cer1�̎w���Ă���A�h���X�ɕۑ�
    inc.l #1,       er1             ;er1�̒l���P���₷
    dec.b           r2h             ;r2h�̒l���P���炷
la02:
    bne   la01                      ;���O�̉��Z���ʂ�0�łȂ�������la01�փW�����v
#pragma endasm

	SCI1_printf("Stack Area (main satrting)\n");
	dumpStackBuffer();
	SCI1_printf("StackPointer= %05lx\n\n", stackpointer);

	initTimer01Int(500); /*���Ԋ��荞��500msec ITUch0,1�g�p*/
	E_INT();        /*CPU���荞�݋���*/
	startTimer01();  /*���Ԋ��荞�݃^�C�}�X�^�[�gch0,ch1*/

	while(!done); /*���荞�ݏ������I���܂Ń��[�v*/

	/*�X�^�b�N�|�C���^�̒l�ƃX�^�b�N�̈��C�̕ϐ��ɕۑ�����@�A�Z���u������łȂ��Ə����Ȃ�*/
	/*��ɂ������A�Z���u���v���O�����̕����Ɠ���*/
#pragma asm
    mov.l er7, @_stackpointer
    mov.l #H'FFEF0, er0
    mov.l #_stack,  er1
    mov.b #H'30:8,  r2h
    bra   lb02
lb01:
    mov.b @er0+,     r2l
    mov.b r2l,      @er1
    inc.l #1,       er1
    dec.b           r2h
lb02:
    bne   lb01
#pragma endasm

	stopTimer01();   /*���Ԋ��荞�݃^�C�}�[�X�g�b�vch0,ch1*/
	D_INT();         /*CPU���荞�݋֎~*/

	SCI1_printf("Stack Area (main terminating)\n");
	dumpStackBuffer();
	SCI1_printf("StackPointer= %05lx\n\n", stackpointer);

	SCI1_printf("Done!   Check LEDs. If LEDs are lightend, OK!!\n");
	while(1);     /*�������[�v*/
}  /*end of main*/


/*���̍�Ƃɂ����LED���_�������荞�ݏ����ɓ��������Ƃ��m�F�����*/
void lightenLED()
{
	SCI1_printf("Turning on LEDs.\n");
	turnOnLed(0);
	turnOnLed(1);
}


void printSituation(void)
{
	SCI1_printf("Stack Area in interrupt routine\n");
	dumpStackBuffer();
	SCI1_printf("StackPointer= %05lx\n\n", stackpointer);
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

    ;���̕����͏�ɂ������A�Z���u���v���O�����̕����Ɠ���

    mov.l er7, @_stackpointer;
    mov.l #H'FFEF0, er0
    mov.l #_stack,  er1
    mov.b #H'30:8,  r2h
    bra   lx02
lx01:
    mov.b @er0+,     r2l
    mov.b r2l,      @er1
    inc.l #1,       er1
    dec.b           r2h
lx02:
    bne   lx01

    ;  �ۑ������X�^�b�N�|�C���^�̒l�ƃX�^�b�N�̈��\������  
    jsr @_printSituation

    ;  �����ɗ����؋���LED��_��  
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

Stack Area (main satrting)
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ffef0 : 00 00 00 00 00 00 00 04 00 00 0c b4 00 0f ff 0c
fff00 : 00 00 00 00 00 00 0e ea 00 00 0e f0 00 00 01 56
fff10 : ff ff ff ff ff ff ff ff ff ff ff ff 7f 00 00 00
StackPointer= fff0c

Stack Area in interrupt routine
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ffef0 : 00 00 00 04 00 00 0c b4 00 0f ff 08 00 00 00 00
fff00 : 00 00 0f 42 00 00 11 f4 44 00 0f 5e 00 00 01 56
fff10 : ff ff ff ff ff ff ff ff ff ff ff ff 7f 00 00 00
StackPointer= fff08

Turning on LEDs.
Stack Area (main terminating)
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ffef0 : 00 00 0c b4 00 0f ff 04 00 00 00 00 00 00 00 00
fff00 : 00 00 00 00 00 00 10 50 44 00 0f 5e 00 00 01 56
fff10 : ff ff ff ff ff ff ff ff ff ff ff ff 7f 00 00 00
StackPointer= fff0c

Done!   Check LEDs. If LEDs are lightend, OK!!
*/

/* map
      _main                                H'00000EC4           DAT
      _printSituation                      H'00000FF0           DAT
*/
