#include<3694.h>
#include "ltrc_lib.h"

void msecWait(unsigned long int length)
{
    //時間待ちをする処理
    volatile unsigned long int i;
    for(i=0;i<length*568;i++){ 
  }
}

int main(void)
{
    //P86,P87を出力ポートに設定
    IO.PCR8|=0xc0;
    initSCI3();
    AD.ADCSR.BYTE = 0x39; //AD変換初期設定
                          //0011 1001
                          //AD変換開始
                          //Scan mode
                          //(70ステート)
                          //AN0-AN1
    //出力レジスタの初期化
    AD.ADDRA.BYTE=0x0000;
    AD.ADDRB.BYTE=0x0000;
    unsigned int left,right;
    while(1){
        while(AD.ADCSR.BIT.ADF!=1);  /* 変換結果がでるまで待つ  */
	    //A-D変換終了
        left  = AD.ADDRA; //left  : AN0 : P80
        right = AD.ADDRB; //right : AN1 : P81

        IO.PDR8.BYTE &=0x3f;  //LED1とLED2を消灯
        if(left>right){
            IO.PDR8.BYTE |= 0x40;   //LED1を点灯
        }else if (left<right){
            IO.PDR8.BYTE |= 0x80;  //LED2を点灯
        }else{
            IO.PDR8.BYTE |= 0xc0;  //LED1とLED2を点灯
        }   
        msecWait(1000); //1秒待機
        AD.ADCSR.BIT.ADF=0;           /* 終了ﾌﾗｸﾞを０に戻す  */
    }
}