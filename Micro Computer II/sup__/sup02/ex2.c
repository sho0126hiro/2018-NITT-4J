/**********************************************************
msecwait�֐���0.25�b���Ƃ�LED��ON-OFF���s��
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

void msecwait(int msec)
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<3352;j++);    /*3352�͎����ɂ���ċ��߂��l*/
	}
}

int count1=1000;
int count2;

main()
{
	int count3=3000;
	count2=2000;
	initSCI1(); /*�V���A���ʐM���j�b�gSCI1�̏�����*/
	initLed();  /*LED������*/
	while(1) {
		SCI1_printf("%5d %5d %5d\n",count1++,count2++,count3++);
		turnOnLed(0); /*LED0��ON*/
		turnOffLed(1); /*LED1��OFF*/
		msecwait(250);
		turnOffLed(0); /*LED0��OFF*/
		turnOnLed(1); /*LED1��ON*/
		msecwait(250);
	}
}
