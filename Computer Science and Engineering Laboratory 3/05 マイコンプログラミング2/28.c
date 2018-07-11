#include <3694.h>
#include "ltrc_lib.h"

void msecWait(unsigned long int length)
{
    //���ԑ҂������鏈��
    volatile unsigned long int i;
    for(i=0;i<length*568;i++){ 
  }
}

void GRset(int dutyL,int dutyR){
    unsigned int b=0.01*dutyL*625; //GRA=625�ɑ΂���dutyL�̊������o��
    unsigned int c=0.01*dutyR*625; //GRA=625�ɑ΂���dutyR�̊������o��
    if(b==625)b--; //duty=100
    else if(b==0)b++; //duty=0
    if(c==625)c--;
    else if(c==0)c++;
    TW.GRB=b;
    TW.GRC=c;
}

int main(void)
{
    //P86,P87���o�̓|�[�g�ɐݒ�
    IO.PCR8|=0xc0;
    initSCI3();
    TW.TMRW.BYTE=0x4B; //(0100 1011) : FTIOB FTIOC >> pwm mode
    TW.TCRW.BYTE=0xB6; //(1011 0110) : �R���y�A�}�b�`A��TCNT���N���A
                                  // : �N���b�N��/8 
                                  // : FTIOB FTIOC �o�͒[�q�̏o�͒l�̐ݒ�(1)
    TW.TCNT=0x0000;    // TCNT�̏����� 
    TW.GRA=625;        // 0.25ms (4kHz)
    TW.TMRW.BIT.CTS=1; // TCNT�J�E���^�X�^�[�g 
    int B_duty[10]={100,80,50,20,0};
    int C_duty[10]={0,20,50,80,100};
    int i;
    while(1){
        for(i=0;i<5;i++){
            GRset(B_duty[i],C_duty[i]);
            SCI3printf("FTIOB duty : %d [%%] FTIOC duty : %d [%%]\n",B_duty[i],C_duty[i]);
            msecWait(3000);//3s
        }
    }
}