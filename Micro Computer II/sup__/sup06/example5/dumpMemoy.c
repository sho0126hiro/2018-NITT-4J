/**********************************************************
dumpMemory�֐��Ń������_���v������
msecwait�֐���0.25�b���Ƃ�LED��ON-OFF���s��
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void msecwait(int msec)
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<3352;j++);    /*3352�͎����ɂ���ċ��߂��l 20MHz�쓮*/
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
	initSCI1(); /*�V���A���ʐM���j�b�gSCI1�̏�����*/
	initLed();  /*LED������*/
	dumpMemory(0L,0x1130L); /*ROM�̈�*/
	dumpMemory(0xfef10L,0xfef30L); /*RAM�̈�*/
	while(1) {
		SCI1_printf("%4x %4x %4x\n",count1++,count2++,count3++);
		turnOnLed(0); /*LED0��ON*/
		turnOffLed(1); /*LED1��OFF*/
		msecwait(250);
		turnOffLed(0); /*LED0��OFF*/
		turnOnLed(1); /*LED1��ON*/
		msecwait(250);
	}
}
