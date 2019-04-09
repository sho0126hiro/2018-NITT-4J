/**********************************************************
タイマ割り込み処理に入った瞬間の出来事
タイマ割り込みだけれど1回だけ割り込みが起こる
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"


volatile int done=0; /*最初は0,割り込み処理が終わったら1になる*/

main()
{
	initLed();   /*LEDユニットの初期化　点滅させるが，動作確認用*/
	initSCI1();  /*シリアル通信の初期化*/
	SCI1_printf("\n\n\n  *** interrupt function starting demo ***\n\n");
	SCI1_printf("Check LEDs. If you see LEDs are off, push [ENTER] key.\n");
	getCharSCI1();

	initTimer01Int(500); /*時間割り込み500msec ITUch0,1使用*/
	E_INT();        /*CPU割り込み許可*/
	startTimer01();  /*時間割り込みタイマスタートch0,ch1*/

	while(!done); /*割り込み処理が終わるまでループ*/

	stopTimer01();   /*時間割り込みタイマーストップch0,ch1*/
	D_INT();         /*CPU割り込み禁止*/

	SCI1_printf("Done!   Check LEDs. If LEDs are lightend, OK!!\n");
	while(1);     /*無限ループ*/
}

/*この作業によってLEDが点灯し割り込み処理に入ったことが確認される*/
void lightenLED()
{
	SCI1_printf("Turning on LEDs.\n");
	turnOnLed(0);
	turnOnLed(1);
}

/*ベクトルテーブルの設定*/
#pragma asm
	.SECTION    MYVEC, DATA, LOCATE=H'000070
	.ORG        H'000070  ;IMIA1
	.DATA.L     _TimerIntFunction
	.SECTION    P,CODE,ALIGN=2 ;これを忘れてはいけない
#pragma endasm

#pragma interrupt (TimerIntFunction)
void TimerIntFunction()
{
	lightenLED();
	done=1;
	ITU1.TSR.BIT.IMFA=0; /*タイマユニットに割込を受付けたことを知らせる*/
}


/*
実行結果
起動後LEDが消えているのを確認し，EnterKeyを押すと，さらに進んで以下の
ようになって止まったように見える。

  *** interrupt function starting demo ***

Check LEDs. If you see LEDs are off, push [ENTER] key.

Turning on LEDs.
Done!   Check LEDs. If LEDs are lightend, OK!!
*/
