/*  msecwait�֐���1�b���Ƃ�LED��ON-OFF���s��  */
#include <3048fone.h>

void msecwait(int msec)
/*msec�ԂȂɂ����Ȃ����ԉ҂��֐�*/
{
    int i,j;
    for (i=0;i<msec;i++) {
        for (j=0;j<2646;j++);    /*2646�͎����ɂ���ċ��߂��l*/
    }
}

main()
{
    /*P5�̉���2�r�b�g���o�͂ɐݒ�*/
    /* P5��DDR�̉���2�r�b�g��1��^����Ƃ��̐ݒ�ɂȂ�*/
    /*DDR�Ƃ�DataDirectionRegister(�f�[�^�����ݒ背�W�X�^)*/
    P5.DDR =  0x3;  /*0x3 = 00000011(��i��)*/
    while(1) {/*����͖������[�v*/
        /*LED0��ON�ɂ���  P5��DR�̑�0�r�b�g��1�ɂ���*/
        /*DR�Ƃ�DataRegister(�f�[�^���W�X�^)*/
        P5.DR.BIT.B0=1;
        /*LED1��OFF�ɂ���  P5��DR�̑�1�r�b�g��0�ɂ���*/
        P5.DR.BIT.B1=0;
        msecwait(1000);/*1000msec�̊ԂȂɂ����Ȃ�*/
        /*LED0��OFF�ɂ���  P5��DR�̑�0�r�b�g��0�ɂ���*/
        P5.DR.BIT.B0=0;
        /*LED1��ON�ɂ���  P5��DR�̑�1�r�b�g��1�ɂ���*/
        P5.DR.BIT.B1=1;
        msecwait(1000);
    }
}
 
