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

void setOperation(int B_duty,int C_duty){
    if(B_duty==-1 || C_duty==-1){
        //Brake
        IO.PDR1.BYTE|=0x06; // 0000 0110
        GRset(100,100);
    }else {
        IO.PDR1.BYTE&=0xf9; // 1111 1001
        GRset(B_duty,C_duty);
    }
}

int main(void)
{
    //P86,P87���o�̓|�[�g�ɐݒ�i����m�F�pLED�j
    IO.PCR8|=0xc0;
    //P11,P12���o�̓|�[�g�ɐݒ�i���[�^�j
    IO.PCR1|=0x06;
    initSCI3();
    TW.TMRW.BYTE=0x03; //(0000 0011) : FTIOB FTIOC >> pwm mode
    TW.TCRW.BYTE=0xB6; //(1011 0110) : �R���y�A�}�b�`A��TNCT���N���A
                                     //�N���b�N��/8
                                     //FTIOB FTIOC �o�͒[�q�̏o�͒l�̐ݒ�(1)
    TW.TCNT=0x0000;    // TCNT�̏����� 
    TW.GRA=625;       // 0.25ms (4kHz)
    TW.TMRW.BIT.CTS=1; // TCNT�J�E���^�X�^�[�g
    //���]�F�f���[�e�B���ݒ�@��~�F�f���[�e�B��0���@�u���[�L�F-1
    //                    1     2     3     4     5     6     7     8     9    10    11
    int B_duty[11] = {    0,  100,  100,    0,   50,    0,   -1,    0,  100,    0,   -1};//left
    int C_duty[11] = {    0,  100,    0,  100,   50,    0,   -1,    0,  100,    0,   -1};//right
    int time[11]   = {    1, 2000, 2000, 2000, 2000,    1, 2000,    1, 2000,    1, 2000};//time(ms)
    int i;
    while(1){
        for(i=0;i<10;i++){
            setOperation(B_duty[i],C_duty[i]);
            msecWait(time[i]);
        }
    }
}