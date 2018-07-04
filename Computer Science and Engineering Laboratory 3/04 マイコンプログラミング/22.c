#include <3694.h>
#include "ltrc_lib.h"

/*
�V�X�e���N���b�N�̎��g��20MHz
�T�u�N���b�N�̎��g���F32.768kHz
*/

volatile int duty1=0;
volatile int duty2=0;
volatile int count=0;

//���荞�݃}�X�N�̃Z�b�g�F���荞��
#define setCCR_I() asm volatile("orc.b #0x80,CCR")
//���荞�݃}�X�N�̃N���A�F���荞�݋���
#define clearCCR_I() asm volatile("andc.b #0x7f,CCR")

#pragma interrupt
void int_timera(void){
    /*���荞�ݎ��Ɏ��s���鏈��*/
    /*LED�̓_������*/
    IRR1.BIT.IRRTA=0;
    if(count==100)count=0;
    if(count<=duty1)      IO.PDR8.BYTE |=0x40;  //LED1�̂ݓ_��
    else if(count>duty1)  IO.PDR8.BYTE &= 0xbf; //LED1����
    if(count<=duty2)      IO.PDR8.BYTE |= 0x80;  //LED2�_��
    if(count>duty2)       IO.PDR8.BYTE &= 0x7f; //LED2����   
    count++;
    
}

void msecWait(unsigned long int length)
{
//���ԑ҂������鏈��
    volatile unsigned  long int i;
    for(i=0;i<length*568;i++){
    }
}

int main(void){
    initSCI3();
    clearCCR_I(); /*���荞�݋���*/
    IO.PCR8|=0xC0; //�o�͐ݒ�
    IRR1.BIT.IRRTA=0;
    IENR1.BIT.IENTA=1;
    TA.TMA.BYTE |= 0x07; // �^�C�}�N���b�N ��/8
    while(1){
        duty1=20;
        duty2=90;
        SCI3printf("duty1: 20[%%] duty2 : 60[%%]");
        msecWait(3000);
        duty1=50;
        duty2=50;
        SCI3printf("duty1: 50[%%] duty2 : 50[%%]");
        msecWait(3000);
        duty1=80;
        duty2=10;
        SCI3printf("duty1: 80[%%] duty2 : 10[%%]");
        msecWait(3000);
    }
}