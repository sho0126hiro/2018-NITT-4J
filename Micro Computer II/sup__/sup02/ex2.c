/**********************************************************
msecwait関数で0.25秒ごとのLEDのON-OFFを行う
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void msecwait(int msec)
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<3352;j++);    /*3352は実測によって求めた値*/
	}
}

int count1=1000;
int count2;

main()
{
	int count3=3000;
	count2=2000;
	initSCI1(); /*シリアル通信ユニットSCI1の初期化*/
	initLed();  /*LED初期化*/
	while(1) {
		SCI1_printf("%5d %5d %5d\n",count1++,count2++,count3++);
		turnOnLed(0); /*LED0のON*/
		turnOffLed(1); /*LED1のOFF*/
		msecwait(250);
		turnOffLed(0); /*LED0のOFF*/
		turnOnLed(1); /*LED1のON*/
		msecwait(250);
	}
}
