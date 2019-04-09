/**********************************************************
タイマ割り込み処理に入った瞬間の出来事
タイマ割り込みだけれど1回だけ割り込みが起こる
**********************************************************/
#include <3048fone.h>
#include "h8_3048fone.h"

unsigned long int stackpointer; /*スタックポインタの値を保存する場所*/
unsigned char stack[0x30];      /*スタック領域を保存する場所*/

volatile int done=0; /*最初は0,割り込み処理が終わったら1になる*/

void dumpStackBuffer(void)
{
	unsigned long int address=0xFFEF0;
	int i;
	SCI1_printf("address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F\n");
	for (i=0; i<0x30; i++,address++) {
		if (i%0x10==0) SCI1_printf ("%05lx : ",address);
		SCI1_printf("%02x ",stack[i]);
		if (i%0x10==0xf) SCI1_printf("\n");
	}
}


main()
{
	initLed();   /*LEDユニットの初期化　点滅させるが，動作確認用*/
	initSCI1();  /*シリアル通信の初期化*/
	SCI1_printf("\n\n\n  *** interrupt function starting demo ***\n\n");
	SCI1_printf("Check LEDs. If you see LEDs are off, push [ENTER] key.\n");
	getCharSCI1();

	/*スタックポインタの値とスタック領域をCの変数に保存する　アセンブリ言語でないと書けない*/
#pragma asm
    mov.l er7, @_stackpointer       ;er7(SP)の値をCの変数stackpointerに格納
                                    ;stackpointerはCの変数stackpointerのアドレスを意味するので
                                    ;「@」をつけて，そのアドレスの指す場所の意味にしている
    mov.l #H'FFEF0, er0             ;er0に0xffef0を格納
    mov.l #_stack,  er1             ;er1にCの変数stackのアドレスを格納
                                    ;すなわちCの配列変数stackの先頭アドレス
    mov.b #H'30:8,  r2h             ;r2hに0x30（8bit値）を格納
    bra   la02
la01:
    mov.b @er0+,     r2l            ;er0の指しているバイト値をr2lに格納し，その後er0の値を１増やす
    mov.b r2l,      @er1            ;r2lの値を，er1の指しているアドレスに保存
    inc.l #1,       er1             ;er1の値を１増やす
    dec.b           r2h             ;r2hの値を１減らす
la02:
    bne   la01                      ;直前の演算結果が0でなかったらla01へジャンプ
#pragma endasm

	SCI1_printf("Stack Area (main satrting)\n");
	dumpStackBuffer();
	SCI1_printf("StackPointer= %05lx\n\n", stackpointer);

	initTimer01Int(500); /*時間割り込み500msec ITUch0,1使用*/
	E_INT();        /*CPU割り込み許可*/
	startTimer01();  /*時間割り込みタイマスタートch0,ch1*/

	while(!done); /*割り込み処理が終わるまでループ*/

	/*スタックポインタの値とスタック領域をCの変数に保存する　アセンブリ言語でないと書けない*/
	/*上にあったアセンブリプログラムの部分と同じ*/
#pragma asm
    mov.l er7, @_stackpointer
    mov.l #H'FFEF0, er0
    mov.l #_stack,  er1
    mov.b #H'30:8,  r2h
    bra   lb02
lb01:
    mov.b @er0+,     r2l
    mov.b r2l,      @er1
    inc.l #1,       er1
    dec.b           r2h
lb02:
    bne   lb01
#pragma endasm

	stopTimer01();   /*時間割り込みタイマーストップch0,ch1*/
	D_INT();         /*CPU割り込み禁止*/

	SCI1_printf("Stack Area (main terminating)\n");
	dumpStackBuffer();
	SCI1_printf("StackPointer= %05lx\n\n", stackpointer);

	SCI1_printf("Done!   Check LEDs. If LEDs are lightend, OK!!\n");
	while(1);     /*無限ループ*/
}  /*end of main*/


/*この作業によってLEDが点灯し割り込み処理に入ったことが確認される*/
void lightenLED()
{
	SCI1_printf("Turning on LEDs.\n");
	turnOnLed(0);
	turnOnLed(1);
}


void printSituation(void)
{
	SCI1_printf("Stack Area in interrupt routine\n");
	dumpStackBuffer();
	SCI1_printf("StackPointer= %05lx\n\n", stackpointer);
}


/*ベクトルテーブルの設定*/
#pragma asm
    .SECTION    MYVEC, DATA, LOCATE=H'000070
    .ORG        H'000070  ;IMIA1
    .DATA.L     _TimerIntFunction
    .SECTION    P,CODE,ALIGN=2 ;これを忘れてはいけない
#pragma endasm

#pragma asm
_TimerIntFunction:                   ; function: _TimerIntFunction()
    ;スタックポインタの値とスタック領域ををCの変数に保存する
    ;本来なら非割り込みルーチンはある仕事をしているはずなので，er0などのレジスタは
    ;使用中であり，割り込みルーチン内でこれらのレジスタを利用する場合は，レジスタの
    ;内容をスタックに退避させ，割り込みルーチン終了直前に復帰させるのが普通の使い方である。
    ;本プログラムでは，main関数は何も作業していないので，レジスタ退避を行っていない。

    ;この部分は上にあったアセンブリプログラムの部分と同じ

    mov.l er7, @_stackpointer;
    mov.l #H'FFEF0, er0
    mov.l #_stack,  er1
    mov.b #H'30:8,  r2h
    bra   lx02
lx01:
    mov.b @er0+,     r2l
    mov.b r2l,      @er1
    inc.l #1,       er1
    dec.b           r2h
lx02:
    bne   lx01

    ;  保存したスタックポインタの値とスタック領域を表示する  
    jsr @_printSituation

    ;  ここに来た証拠にLEDを点灯  
    jsr @_lightenLED

    ;  割り込み処理があったことをmainに知らせる
    mov.w  #1, r0
    mov.w  r0, @_done             ;Cの変数doneに1を代入

    ;タイマユニットに割り込みを受け付けたことを知らせる
    BCLR.B #0,@H'FFFF71:8         ;ITU1.TSR.BIT.IMFA=0;

    rte                    ; ReTurn from Exception
#pragma endasm

/*
実行結果
起動後LEDが消えているのを確認し，EnterKeyを押すと，さらに進んで以下の
ようになって止まったように見える。

  *** interrupt function starting demo ***

Check LEDs. If you see LEDs are off, push [ENTER] key.

Stack Area (main satrting)
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ffef0 : 00 00 00 00 00 00 00 04 00 00 0c b4 00 0f ff 0c
fff00 : 00 00 00 00 00 00 0e ea 00 00 0e f0 00 00 01 56
fff10 : ff ff ff ff ff ff ff ff ff ff ff ff 7f 00 00 00
StackPointer= fff0c

Stack Area in interrupt routine
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ffef0 : 00 00 00 04 00 00 0c b4 00 0f ff 08 00 00 00 00
fff00 : 00 00 0f 42 00 00 11 f4 44 00 0f 5e 00 00 01 56
fff10 : ff ff ff ff ff ff ff ff ff ff ff ff 7f 00 00 00
StackPointer= fff08

Turning on LEDs.
Stack Area (main terminating)
address +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
ffef0 : 00 00 0c b4 00 0f ff 04 00 00 00 00 00 00 00 00
fff00 : 00 00 00 00 00 00 10 50 44 00 0f 5e 00 00 01 56
fff10 : ff ff ff ff ff ff ff ff ff ff ff ff 7f 00 00 00
StackPointer= fff0c

Done!   Check LEDs. If LEDs are lightend, OK!!
*/

/* map
      _main                                H'00000EC4           DAT
      _printSituation                      H'00000FF0           DAT
*/
