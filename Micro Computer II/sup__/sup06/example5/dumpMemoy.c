/**********************************************************
dumpMemory関数でメモリダンプした後
msecwait関数で0.25秒ごとのLEDのON-OFFを行う
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void msecwait(int msec)
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<3352;j++);    /*3352は実測によって求めた値 20MHz駆動*/
	}
}

void dumpMemory(long int address, long int tail)
{
	long int i;
	unsigned char ch;
	address&=0xfffffff0;
	tail&=0xfffffff0;
	SCI1_printf("address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F   0123456789ABCDEF\n");
	for (; address<tail; address++) {
		if (address%0x10==0) SCI1_printf ("%05lx : ",address);
		SCI1_printf("%02x ",*(unsigned char*)address);
		if (address%0x10==0xf) {
			SCI1_printf(": ");
			for (i=-0xf; i<=0; i++) {
				ch=*(unsigned char*)(address+i);
				SCI1_printf("%c",isprint(ch)?ch:'.');
			}
			SCI1_printf("\n");
		}
	}
	SCI1_printf("\n");
}

int count1=0x1234;
int count2;

main()
{
	int count3=0x3456;
	count2=0x2345;
	initSCI1(); /*シリアル通信ユニットSCI1の初期化*/
	initLed();  /*LED初期化*/
	dumpMemory(0L,0x1130L); /*ROM領域*/
	dumpMemory(0xfef10L,0xfef30L); /*RAM領域*/
	while(1) {
		SCI1_printf("%4x %4x %4x\n",count1++,count2++,count3++);
		turnOnLed(0); /*LED0のON*/
		turnOffLed(1); /*LED1のOFF*/
		msecwait(250);
		turnOffLed(0); /*LED0のOFF*/
		turnOnLed(1); /*LED1のON*/
		msecwait(250);
	}
}
