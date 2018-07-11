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
    TW.GRB=0.01*dutyL*625; //GRA=625に対するdutyLの割合を出す
    TW.GRC=0.01*dutyR*625; //GRA=625に対するdutyRの割合を出す
}

int main(void)
{
    //P86,P87を出力ポートに設定
    IO.PCR8|=0xc0;
    initSCI3();
    TW.TMRW.BYTE=0x4B; //(0100 1011) : FTIOB FTIOC >> pwm mode
    TW.TCRW.BYTE=0xB6; //(1011 0110) : コンペアマッチAでTCNTがクリア
                                  // : クロックφ/8 
                                  // : FTIOB FTIOC 出力端子の出力値の設定(1)
    TW.TCNT=0x0000;    // TCNの初期化 
    TW.GRA=625;        // 0.25ms (4kHz)
    TW.TMRW.BIT.CTS=1; // TCNTカウンタスタート 
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