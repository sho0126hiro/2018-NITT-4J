#include <3694.h>
#include "ltrc_lib.h"

/*
システムクロックの周波数20MHz
サブクロックの周波数：32.768kHz
*/

volatile int duty1=0;
volatile int duty2=0;
volatile int count=0;

//割り込みマスクのセット：割り込み
#define setCCR_I() asm volatile("orc.b #0x80,CCR")
//割り込みマスクのクリア：割り込み許可
#define clearCCR_I() asm volatile("andc.b #0x7f,CCR")

#pragma interrupt
void int_timera(void){
    /*割り込み時に実行する処理*/
    /*LEDの点灯消灯*/
    IRR1.BIT.IRRTA=0;
    if(count==100)count=0;
    if(count<=duty1)      IO.PDR8.BYTE |=0x40;  //LED1のみ点灯
    else if(count>duty1)  IO.PDR8.BYTE &= 0xbf; //LED1消灯
    if(count<=duty2)      IO.PDR8.BYTE |= 0x80;  //LED2点灯
    if(count>duty2)       IO.PDR8.BYTE &= 0x7f; //LED2消灯   
    count++;
    
}

void msecWait(unsigned long int length)
{
//時間待ちをする処理
    volatile unsigned  long int i;
    for(i=0;i<length*568;i++){
    }
}

int main(void){
    initSCI3();
    clearCCR_I(); /*割り込み許可*/
    IO.PCR8|=0xC0; //出力設定
    IRR1.BIT.IRRTA=0;
    IENR1.BIT.IENTA=1;
    TA.TMA.BYTE |= 0x07; // タイマクロック φ/8
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