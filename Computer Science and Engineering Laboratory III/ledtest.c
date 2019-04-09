#include<3694.h>

int main (void)
{
	IO.PCR8|=0xC0;//P86,87を出力ポートに設定
	while(1){
    /*LED1:86
      LED2:87
      0x : P87 P86 P85 P84 P83 P82 P81 P80
      port8 の　6bit目、7bit目を点灯させたい
      0x40 : 100-0000 : 6bit目
      0x80 :1000-0000 : 7bit目
    */
		IO.PDR8.BYTE|=0x40;//LED1を点灯
		IO.PDR8.BYTE|=0x80; //LED2を点灯
	}
}
