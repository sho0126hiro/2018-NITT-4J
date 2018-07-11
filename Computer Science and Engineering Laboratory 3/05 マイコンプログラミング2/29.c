#include <3694.h>
#include "ltrc_lib.h"

void msecWait(unsigned long int length)
{
    //時間待ちをする処理
    volatile unsigned long int i;
    for(i=0;i<length*568;i++){ 
  }
}

void GRset(int dutyL,int dutyR){
    unsigned int b=0.01*dutyL*625; //GRA=625に対するdutyLの割合を出す
    unsigned int c=0.01*dutyR*625; //GRA=625に対するdutyRの割合を出す
    if(b==625)b--; //duty=100
    else if(b==0)b++; //duty=0
    if(c==625)c--;
    else if(c==0)c++;
    TW.GRB=b;
    TW.GRC=c;
}

long int setOperation(int B_duty,int C_duty,int time){
    GRset(B_duty,C_duty);
    if(time==0){
        return 1;
    }else return 2000;
}

int main(void)
{
    //P86,P87を出力ポートに設定
    IO.PCR8|=0xc0;
    initSCI3();
    TW.TMRW.BYTE=0x03; //(0000 0011) : FTIOB FTIOC >> pwm mode
    TW.TCRW.BYTE=0xB6; //(1011 0110) : コンペアマッチAでTNCTがクリア
                                 // : クロックφ/8 
                                 // : FTIOB FTIOC 出力端子の出力値の設定(1)
    TW.TCNT=0x0000;    // TCNの初期化 
    TW.GRA=625;       // 0.25ms (4kHz)
    TW.TMRW.BIT.CTS=1; // TCNTカウンタスタート 
    //B:left C:rightとする
    unsigned int left,right;
    int B_duty[11] = {  0,100,100,  0, 50,  0,  0,  0,100,  0,  0};//left
    int C_duty[11] = {  0,100,  0,100, 50,  0,  0,  0,100,  0,  0};//right
    int time[11]   = {  0,  1,  1,  1,  1,  0,  1,  0,  1,  0,  1};//time(0:1ms,1:2s)
    int i;
    long int B_pwm,C_pwm;
    while(1){
        for(i=0;i<10;i++){
            //SCI3print("FTIOB duty : %d [%%] FTIOC duty : %d [%%]",B_duty[i],C_duty[i]);
            msecWait(setOperation(B_duty[i],C_duty[i],time[i]));
        }
    }
}