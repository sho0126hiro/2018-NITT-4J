//実験21
#include <3694.h>
#include "ltrc_lib.h"
/*
組み合わせ
n : LED1 LED2
1 : OFF  OFF
2 : ON   OFF
3 : OFF  ON
4 : ON   ON

IO.PDR8.BYTE|=0x40;  //LED1を点灯
IO.PDR8.BYTE&=0xbf;  //LED1を消灯
IO.PDR8.BYTE|=0x80;  //LED2を点灯
IO.PDR8.BYTE&=0xef;  //LED2を消灯
*/
void msecWait(unsigned long int length)
{
//時間待ちをする処理
  volatile unsigned  long int i;
  for(i=0;i<length*568;i++){
  }
}

int main(void){
    //P86,P87を出力ポートに設定
    IO.PCR8|=0xC0;
    
    initSCI3();

    SCI3printf("\n-----------------------------\n");
    while(1){
        //pattern1
        IO.PDR8.BYTE &=0x3f;  //LED1とLED2を消灯
        msecWait(1000); //1000ms
        SCI3printf("%08b \n",IO.PDR8.BYTE);
        
        //pattern2
        IO.PDR8.BYTE |=0x40;  //LED1のみ点灯
        msecWait(1000);  //1000ms
        SCI3printf("%08b \n",IO.PDR8.BYTE);
     
        //pattern3
        IO.PDR8.BYTE &= 0xbf;  //LED1消灯
        IO.PDR8.BYTE |= 0x80;  //LED2点灯
        msecWait(1000); //1000ms
        SCI3printf("%08b \n",IO.PDR8.BYTE);
        //pattern4
        IO.PDR8.BYTE |= 0xc0;  //LED1とLED2を点灯
        msecWait(1000); //1000ms
        SCI3printf("%08b \n",IO.PDR8.BYTE);
        
    }
}

/*実行結果

00000000
01000000
10000000
11000000
00000000
01000000
10000000
11000000
00000000
01000000
10000000
11000000
*/

