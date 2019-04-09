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
    AD.CSR.BYTE = 0x39; //AD変換初期設定
                          //0011 1001
                          //AD変換開始
                          //Scan mode
                          //(70ステート)
                          //AN0-AN1
    //出力レジスタの初期化
    AD.DRA=0x0000;
    AD.DRB=0x0000;
    unsigned int left,right;
    while(1){
        while(AD.CSR.BIT.ADF!=1);  /* 変換結果がでるまで待つ  */
	    //A-D変換終了
        left  = AD.DRA; //left  : AN0 : PB0 :10
        right = AD.DRB; //right : AN1 : PB1 : 9
        SCI3printf("left= %b (%d)  right = %b (%d)\n",left>>6,left>>6,right>>6,right>>6);
        IO.PDR8.BYTE &=0x3f;  //LED1とLED2を消灯
        if(left>right){
            IO.PDR8.BYTE |= 0x40;   //LED1を点灯
        }else if (left<right){
            IO.PDR8.BYTE |= 0x80;  //LED2を点灯
        }else{
            IO.PDR8.BYTE |= 0xc0;  //LED1とLED2を点灯
        }   
        msecWait(1000); //1秒待機
        AD.CSR.BIT.ADF=0;           /* 終了ﾌﾗｸﾞを０に戻す  */
    }
}