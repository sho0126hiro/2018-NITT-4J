/****************************************************************
h8_3048fone.h
Copyright (c) Kosaka Lab CS TNCT

このインクルードファイルは小坂研究室の代々の研究生が開発した
h8/3048用の有用な関数群を改良して小坂がまとめたものである。
06 Mar 2013 h8_3048fone.h  小坂 教材用にリファイン
01 Jun 2009 h8-3048.h  小坂 教材用にリファイン
28 Jun 2006 h8-3048.h  小坂 chkgetSCI1のタイミング修正
 4 Dec 2003 h8-3048.h  小坂 printf更新,initLed更新,initDDR削除
08 Oct 2003 h8-3048.h  小坂 stopTimer追加,getIntSCI1でBS使用可
 6 Jan 2003 h8_3048.h  小坂 getIntSCIバックスペイスに対応。
17 Apr 2002 h8-01.h  小坂 %uの使い方をansiにあわせた。
14 Dec 2001 h8-01.h  小坂，越智
15 Jly 2000 h8-00.h  小坂，藤原
22 Dec 1999 h8-99.h  小坂，高沢
29 Oct 1999 h8-99.h  小坂
05 Feb 1999 lib.h    笠井


【１】SCI
【１．１】 ch1 関係
void initSCI1()
 SCI-ch1の初期化　38400baud, Async, 8bit , NoParity, stop1

short int SCI1_getChar()
 SCI-ch1から1byte入力コード。エラーがあると-2が戻る。
short int SCI1_chkgetChar()
 SCI-ch1を検査し，受信データがあれば1byte入力コード。なければ-1が，失敗すると-2が戻る。
int SCI1_getString(char *buff,int max)
 SCI1から最大max-1文字の文字列を受け取る。（buffのサイズはmaxでよい）
short int SCI1_getInt(char prompt[])
 SCI-ch1からプロンプト付で，short intの値を受け取る。
 正負の10進数または16進数を受け付ける。16進数は0xで始まる
long int SCI1_getInt4(char prompt[])
 SCI-ch1からプロンプト付で，long intの値を受け取る。
 正負の10進数または16進数を受け付ける。16進数は0xで始まる

void SCI1_putChar(char c)
 SCI-ch1に1バイト出力する。
void SCI1_putString(char *str)
 SCI-ch1に文字列を出力する。
void SCI1_printf(char *format,...)
  関数printfのSCI1版
  軽量化のためエラー処理はないので桁数指定の場合は注意
  対応書式
  %d   : [int] integer with sign. '%d','%4d','%-4d', and '%04d' are available
  %ld  : explicit [long int]  '%ld','%9ld','%-9ld', and '%09ld' are available
  %u   : [unsigbed int] unsigned integer.
			'%u','%4u','%-4u', and '%04u' are available
  %lu  : explicit [unsigned long int]
			'%lu','%9lu','%-9lu', and '%09lu' are available
  %x   : [unsigned int] in Hex  '%x','%4x','%-4x', and '%04x' are available
  %lx  : explicit [unsigned long int] in Hex  
			'%lx','%8lx','%-8lx', and '%08lx' are available
  %o   : [unsigned int] in Oct  '%o','%4o','%-4o', and '%04o' are available
  %lo  : explicit [unsigned long int] in Oct  
			'%lo','%8lo','%-8lo', and '%08lo' are available
  %b   : [unsigned int] in Bin  '%b','%8b','%-8b', and '%08b' are available
  %lb  : explicit [unsigned long int] in Bin  
			'%lb','%8lb','%-8lb', and '%08lb' are available
  %c   : char
  %s   : string %20s %-20s are available

【１．２】SCI ch0 関係
void initSCI0()
 SCI-ch0の初期化　38400baud, Async, 8bit , NoParity, stop1

short int SCI0_getChar()
 SCI-ch0から1byte入力コード。エラーがあると-2が戻る。
short int SCI0_chkgetChar()
 SCI-ch0を検査し，受信データがあれば1byte入力コード。なければ-1が，失敗すると-2が戻る。
int SCI0_getString(char *buff,int max)
 SCI0から最大max-1文字の文字列を受け取る。（buffのサイズはmaxでよい）
short int SCI0_getInt(char prompt[])
 SCI-ch0からプロンプト付で，short intの値を受け取る。
 正負の10進数または16進数を受け付ける。16進数は0xで始まる
long int SCI0_getInt4(char prompt[])
 SCI-ch0からプロンプト付で，long intの値を受け取る。
 正負の10進数または16進数を受け付ける。16進数は0xで始まる

void SCI0_putChar(char c)
 SCI-ch0に1バイト出力する。
void SCI0_putString(char *str)
 SCI-ch0に文字列を出力する。
void SCI0_printf(char *format,...)
  関数printfのSCI0版
  仕様はvoid SCI1_printf(char *format,...)参照

【２】LCD関係
void LCD_putchar(char data)
  LCDに向けた putchar()
void LCD_puts(char *str)
  LCDに向けた puts()
void initLCD( void )
  LCDの初期化
void LCD_gotoxy(unsigned x,unsigned y)
  LCDに向けた gotoxy()
void LCD_clrscr(void)
  LCDに向けた clrscr()   clear screen
void LCD_printf(char *format,...)
  関数printfのLCD版
  仕様はvoid SCI1_printf(char *format,...)参照

【３】文字列操作
void sprintf(char *buff,char *format,...)
  仕様はvoid SCI1_printf(char *format,...)参照
  buffのあふれは呼び出し側で起こらないようにしておく必要がある
long int atoi(char *buff)
  文字列を整数型の値に変換する
  正負の10進数または16進数の文字列を受け付ける。16進数は0xまたは-0xで始まる
 例 "123"
    "-123"
    "0x1a"
    "-0x100"

【４】AKI-H8マザーボード関係
void initLed()
 LEDの初期化
void turnOnLed(short int number)
 LEDの点灯　numberはLED番号で0または1を指定する
void turnOffLed(short int number)
 LEDの消灯　numberはLED番号で0または1を指定する

void initPushSW(void)
 押しボタンスイッチの初期化
unsigned char getPushSW(void)
 押しボタンスイッチの取得　ビット反転し，ONは1，OFFは0で取得される。
 押しボタンスイッチの状況は第0-第3ビットに現れる。
 これはマクロ定義で実現されている
short int checkPushSW(short int number)
 push sw 0,1,2,3の状態を調べる　number:0,1,2,or 3
 押されていたら1、そうでなかったら0を返す

void init8BitSW(void)
 8ビットスイッチの初期化
unsigned char get8BitSW(void)
 8ビットスイッチの取得　ビット反転し，ONは1，OFFは0で取得される。
 8ビットスイッチの状況は第0-第7ビットに現れる。
 これはマクロ定義で実現されている
short int check8BitSW(short int number)
 8bitsw 0,1,2,3,4,5,6,7の状態を調べる　number:0,1,2,3,4,5,6,or 7
 ONなら1、そうでなかったら0を返す

【５】インターバルタイマ割り込み
void initTimer1Int(unsigned short int period)
 ITU1による割り込みタイマーの設定
 割り込み間隔は引数peiodで単位はμsecである
 値は20971以下でなければならない。20.971msecまで設定可能

void startTimer1(void)
 Timer CH1 スタート
 これはマクロ定義で実現されている
void stopTimer1(void)
 Timer CH1 ストップ
 これはマクロ定義で実現されている
void clearTimer1Flag(void)
 Timer CH1 割り込みフラグのクリア
 これはマクロ定義で実現されている


****************************************************************/

#include<stdarg.h>

extern void E_INT();
extern void D_INT();

/*次の1行はMicrosoftHyperTerminal使用時に有効にする*/
/*有効な場合H8からシリアル送信時に\nを\r\nに自動変換する*/
#define HYPERTERMINAL

/*システムクロック関係*/
#define SYS_CLOCK 25 /*MHz 16,20,25 程度を想定*/

const int SCI0device=0;
const int SCI1device=1;
const int LCDdevice=2;
const int STRdevice= 3;

/*SCI関係の基本部分は笠井君(1998年度)藤原君(2000)の開発です*/
/* ------------------------------------------------- */
/* SCI1 INITIALIZATION fixed baud at 38400           */
/* ------------------------------------------------- */
void initSCI1()
{
	short int i;
	SCI1.SCR.BYTE = 0;       /* clear all flags */
					  /* 2400-38400baud are available at n=0(cks1=0,cks2=0) */
	SCI1.SMR.BYTE = 0;       /* Async, 8bit , NoParity, stop1, 1/1 */
	SCI1.BRR = (unsigned char)((8138L*SYS_CLOCK+5000L)/10000L-1);
	for(i=0;i<1000;i++);      /* wait more than 1bit time */
	SCI1.SCR.BYTE = 0x30;    /* scr = 0011 0000 (TE=1,RE=1) */
	return;
}

/* ------------------------------------------------- */
/* GET BYTE FROM SCI1 */
/* ------------------------------------------------- */
short int SCI1_getChar()
/* return value 0x00-0xFF:received data */
/*              -2(0xFFFE):error */
{
	short int flags,recdata;
	do {
		flags = SCI1.SSR.BYTE;
		if (flags&0x38) {/* error */
			SCI1.SSR.BIT.RDRF = 0;
			SCI1.SSR.BIT.ORER = 0;
			SCI1.SSR.BIT.FER = 0;
			SCI1.SSR.BIT.PER = 0;
			return -2;
		}
		if (flags&0x40) {/* normally received one data */
			SCI1.SSR.BIT.RDRF = 0;
			recdata=SCI1.RDR;
			return recdata;
		}
	} while (1);
}

/* ------------------------------------------------- */
/* CHECK SCI BUFFER AND GET DATA */
/* ------------------------------------------------- */
short int SCI1_chkgetChar()
/* return value -1(0xFFFF):no received data  */
/*              0x00-0xFF:received data */
/*              -2(0xFFFE):error */
{
	short int flags,recdata;
	flags = SCI1.SSR.BYTE;
	if (flags&0x38) {/* error */
		SCI1.SSR.BIT.RDRF = 0;
		SCI1.SSR.BIT.ORER = 0;
		SCI1.SSR.BIT.FER = 0;
		SCI1.SSR.BIT.PER = 0;
		return -2;
	}
	if (flags&0x40) {/* normally received one data */
		recdata=SCI1.RDR;
		SCI1.SSR.BIT.RDRF = 0;
		return recdata;
	} else {
		return -1;
	}
}

void SCI1_putString(char *str);

/*SCI1より文字列入力[return]が終端だが，'\n'は取得されない*/
/*^Hでバックスペイス*/
int SCI1_getString(char *buff,int max)
{
	int i,ch;
	for (i=0;i<max-1;i++) {
		ch=SCI1_getChar(); /*1文字取得*/
		*buff=(char)ch; /*1文字取得*/
		if (*buff=='\r'||ch<0) {
			*buff=0;
			return i+1;
		}
		if (*buff==0x8) {
			buff-=2;
			i-=2;
		}
		if (*buff!='\n') buff++;
		else i--;
	}
	*buff=0;
	return i+1;
}

/* ------------------------------------------------- */
/* PUT BYTE TO SCI1 */
/* ------------------------------------------------- */
void SCI1_putChar(char c)
{
	unsigned char tmp;
#ifdef HYPERTERMINAL
	if (c=='\n') SCI1_putChar('\r');
#endif
	do{
		tmp = SCI1.SSR.BYTE;
	} while((tmp & 0x80)==0);
	SCI1.TDR = c;
	SCI1.SSR.BIT.TDRE = 0;
	return;
}

void SCI1_putString(char *str)
{
	while(*str){
		SCI1_putChar(*str);
		str++;
	}
}


/* ------------------------------------------------- */
/* SCI0 INITIALIZATION fixed baud at 38400           */
/* ------------------------------------------------- */
void initSCI0()
{
	short int i;
	SCI0.SCR.BYTE = 0;       /* clear all flags */
					  /* 2400-38400baud are available at n=0(cks1=0,cks2=0) */
	SCI0.SMR.BYTE = 0;       /* Async, 8bit , NoParity, stop1, 1/1 */
	SCI0.BRR = (unsigned char)((8138L*SYS_CLOCK+5000L)/10000L-1);
	for(i=0;i<1000;i++);      /* wait more than 1bit time */
	SCI0.SCR.BYTE = 0x30;    /* scr = 0011 0000 (TE=1,RE=1) */
	return;
}

/* ------------------------------------------------- */
/* GET BYTE FROM SCI0 */
/* ------------------------------------------------- */
short int SCI0_getChar()
/* return value 0x00-0xFF:received data */
/*              -2(0xFFFE):error */
{
	short int flags,recdata;
	do {
		flags = SCI0.SSR.BYTE;
		if (flags&0x38) {/* error */
			SCI0.SSR.BIT.RDRF = 0;
			SCI0.SSR.BIT.ORER = 0;
			SCI0.SSR.BIT.FER = 0;
			SCI0.SSR.BIT.PER = 0;
			return -2;
		}
		if (flags&0x40) {/* normally received one data */
			SCI0.SSR.BIT.RDRF = 0;
			recdata=SCI0.RDR;
			return recdata;
		}
	} while (1);
}

/* ------------------------------------------------- */
/* CHECK SCI BUFFER AND GET DATA */
/* ------------------------------------------------- */
short int SCI0_chkgetChar()
/* return value -1(0xFFFF):no received data  */
/*              0x00-0xFF:received data */
/*              -2(0xFFFE):error */
{
	short int flags,recdata;
	flags = SCI0.SSR.BYTE;
	if (flags&0x38) {/* error */
		SCI0.SSR.BIT.RDRF = 0;
		SCI0.SSR.BIT.ORER = 0;
		SCI0.SSR.BIT.FER = 0;
		SCI0.SSR.BIT.PER = 0;
		return -2;
	}
	if (flags&0x40) {/* normally received one data */
		recdata=SCI0.RDR;
		SCI0.SSR.BIT.RDRF = 0;
		return recdata;
	} else {
		return -1;
	}
}

void SCI0_putString(char *str);
/*SCI0より文字列入力[return]が終端だが，'\n'は取得されない*/
/*^Hでバックスペイス*/
int SCI0_getString(char *buff,int max)
{
	int i,ch;
	for (i=0;i<max-1;i++) {
		ch=SCI0_getChar(); /*1文字取得*/
		*buff=(char)ch; /*1文字取得*/
		if (*buff=='\r'||ch<0) {
			*buff=0;
			return i+1;
		}
		if (*buff==0x8) {
			buff-=2;
			i-=2;
		}
		if (*buff!='\n') buff++;
		else i--;
	}
	*buff=0;
	return i+1;
}

/*拡張atoi*/
/* 123,-123,0x1a,-0x1a の形の文字列をlong intに変換する*/
long int atoi(char *buff)
{
	long int x=0;
	int y,m=0,n=0,v=0,i=0;
	y=buff[i];
	while(y!=0){
		if(y=='-') m=1;
		if('a'<=y&&y<='z') y=y-'a'+'A';
		if(y=='0') n=1;

		if(v==1){
			if('0'<=y&&y<='9'){
				y=y-'0';
			}
			else if('A'<=y&&y<='F'){
				y=y-'A'+10;
			}
			x=16*x+y;
		}

		if(n==1&&y=='X'){
			v=1;
		}
				
		if(v==0&&'0'<=y&&y<='9'){
			y=y-'0';
			x=10*x+y;
		}

		y=buff[++i];
	}
	if(m==1) x=-x;
	return x;
}

#define SCI1_getInt(prompt) ((short int)SCI1_getInt4(prompt))

/*SCI1へプロンプトを表示して，SCI1より整数値を入力*/
long int SCI1_getInt4(char prompt[])
/*getting integer from serial port*/
/* format 123[ret] */
/*        -123[ret] */
/*        0x1a[ret] */
/*        -0x100[ret] */
{
	char buff[16];
	SCI1_putString(prompt);
	SCI1_getString(buff,16);
	return atoi(buff);
}

#define SCI0_getInt(prompt) ((short int)SCI0_getInt4(prompt))

/*SCI0へプロンプトを表示して，SCI0より整数値を入力*/
long int SCI0_getInt4(char prompt[])
/*getting integer from serial port*/
/* format 123[ret] */
/*        -123[ret] */
/*        0x1a[ret] */
/*        -0x100[ret] */
{
	char buff[16];
	SCI0_putString(prompt);
	SCI0_getString(buff,16);
	return atoi(buff);
}


/* ------------------------------------------------- */
/* PUT BYTE TO SCI0 */
/* ------------------------------------------------- */
void SCI0_putChar(char c)
{
	unsigned char tmp;
#ifdef HYPERTERMINAL
	if (c=='\n') SCI0_putChar('\r');
#endif
	do{
		tmp = SCI0.SSR.BYTE;
	} while((tmp & 0x80)==0);
	SCI0.TDR = c;
	SCI0.SSR.BIT.TDRE = 0;
	return;
}

void SCI0_putString(char *str)
{
	while(*str){
		SCI0_putChar(*str);
		str++;
	}
}



/* Port3 -> LCD */
/* 7    6    5    4    3    2    1    0  */
/*          ES   RS  DB7  DB6  DB5  DB4  */

/* i/o */
#define init_LCD_Port()     P3.DDR = 0x3f
#define LCD_Port            P3.DR.BYTE
#define LCD_RegisterSelect  P3.DR.BIT.B4
#define LCD_EnableSignal    P3.DR.BIT.B5

static void LCD_waitmsec(unsigned int msec)
/*mesc間なにもしない時間稼ぎ関数*/
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<168*SYS_CLOCK;j++);
	}
}

static void LCD_waitmicrosec(unsigned int microsec)
{/*だいたいmicrosec間なにもしない時間稼ぎ関数*/
	int i,j;
	for (i=0;i<microsec;i++) {
		for (j=0;j<168*SYS_CLOCK/1000;j++);
	}
}

static void LCD_putCommand(char command) /*command width must be 4bits*/
{
	LCD_Port=(LCD_Port&0xf0)|command;
	LCD_EnableSignal=1;
	LCD_waitmicrosec(5);
	LCD_EnableSignal=0;
	LCD_waitmicrosec(40);
}

static void LCD_putCommand2(char command2)
{
	LCD_putCommand((command2>>4)&0xf);
	LCD_putCommand(command2&0xf);
}

/************************************************************
LCDに向けた putchar()
************************************************************/
void LCD_putchar(char data)
{
	LCD_RegisterSelect=1;
	LCD_putCommand((data>>4)&0xf);
	LCD_putCommand(data&0xf);
	LCD_RegisterSelect=0;
}

/************************************************************
LCDに向けた puts()
************************************************************/
void LCD_puts(char *str)
{
	while(*str) LCD_putchar(*str++);
}

/************************************************************
LCDの初期化
************************************************************/
void initLCD( void )
{
	init_LCD_Port();        /* output */
	LCD_Port&=0xc0;
	LCD_waitmsec(30);           /* wait 30ms */
	LCD_putCommand(0x3);     /* function set */
	LCD_waitmicrosec(4100);
	LCD_putCommand(0x3);     /* function set */
	LCD_waitmicrosec(100);
	LCD_putCommand(0x3);     /* function set */
	LCD_waitmicrosec(100);
	LCD_putCommand(0x2);     /* function set data width=4bit*/
	LCD_putCommand2(0x28);   /* function set 4bit duty:1/16,size:5*7 */
	LCD_putCommand2(0x0c);   /* display on,cursor off,blink off */
	LCD_putCommand2(0x06);   /* address:auto increment,cursor shift:right */
	LCD_putCommand2(0x01);   /* clear display */
	LCD_waitmicrosec(1640);
}

/************************************************************
LCDに向けた gotoxy()
************************************************************/

void LCD_gotoxy(unsigned x,unsigned y)
{
	unsigned char point;
	point=0x80+x+0x40*y;
	LCD_putCommand2(point);
}

/************************************************************
LCDに向けた clrscr()   clear screen
************************************************************/
void LCD_clrscr(void)
{
	LCD_putCommand2(0x01);    /* clear display */
	LCD_waitmicrosec(1640);
}

static char *currentstrptr;
static void STR_putChar(char ch)
{
	*currentstrptr++=ch;
	*currentstrptr=0;
}

static void STR_putString(char *ptr)
{
	while(*ptr) STR_putChar(*ptr++);
}


const char hexstring[]="0123456789abcdef0123456789ABCDEF";
#define MAXDIGIT 34

void Device_printf(int device, char *format, va_list arg_ptr)
{
	void (*device_putchar)(char ch);
	void (*device_puts)(char *ptr);
	char buf[MAXDIGIT];
	unsigned char flag=0;  /*%d:bit2 l:bit1 %:bit0 */
	unsigned char digit=0; /* 桁数 */
	unsigned char minus=0;
	char fill=' ',format1=' ';
	unsigned char radix=10; /*N進基数*/
	char sign=' ';
	char *ptr=buf; /*出力文字ポインタ*/
	unsigned char cntr=0; /*出力文字数カウンタ*/
	unsigned char shift=0; /*16進シフト 0 or 6*/
	unsigned char i;
	unsigned long int value=0;
	if (device==SCI0device) {
		device_putchar=SCI0_putChar;
		device_puts=SCI0_putString;
	} else if (device==SCI1device) {
		device_putchar=SCI1_putChar;
		device_puts=SCI1_putString;
	} else if (device==LCDdevice) {
		device_putchar=LCD_putchar;
		device_puts=LCD_puts;
	} else { /*device==STRdevice*/
		device_putchar=STR_putChar;
		device_puts=STR_putString;
	}
	/*va_start(arg_ptr,format);*/
	while (*format) {
		format1=*format;
		if (flag==0) {
			if (format1=='%') {
				flag=1;
				digit=0;
				fill=' ';
				minus=0;
				radix=0;
				ptr=&buf[MAXDIGIT-1];
				*ptr--='\0';
				cntr=0;
				shift=0;
				sign='+';
			} else {
				device_putchar(format1);
			}
		} else {
			if (format1=='l') {
				flag|=2;
			} else if ('0'<=(format1)&&(format1)<='9') {
				if (digit==0 && format1=='0') {
					fill='0';
				} else {
					digit=digit*10+((format1)-'0');
					if (MAXDIGIT-2<digit) digit=MAXDIGIT-2;
				}
			} else if (format1=='-') {
				minus=1;
			} else if (format1=='d') {
				flag|=4;
				radix=10;
			} else if (format1=='u') {
				radix=10;
			} else if (format1=='x') {
				radix=16;
			} else if (format1=='X') {
				radix=16;shift=16;
			} else if (format1=='o') {
				radix=8;
			} else if (format1=='b') {
				radix=2;
			} else if (format1=='p') {
				radix=16;shift=16;digit=8;fill='0';flag|=2;
			} else if (format1=='c') {
				device_putchar((unsigned char)(va_arg(arg_ptr,int)));
				flag=0;
			} else if (format1=='s') {
				if (digit) {
					cntr=0;ptr=va_arg(arg_ptr,char *);
					while (ptr[cntr]) cntr++; /*cntrは文字数*/
					if (!minus) for (i=cntr;i<digit;i++) device_putchar(' ');
					device_puts(ptr);
					if (minus) for (i=cntr;i<digit;i++) device_putchar(' ');
				} else {
					device_puts(va_arg(arg_ptr,char *));
				}
				flag=0;
			} else {
				device_putchar(format1);
				flag=0;
			}
			if (radix) {
				switch (flag&6) {
				case 0: /* unsig int */
					value=(unsigned int)va_arg(arg_ptr,int);
					break;
				case 2: /* unsig long int */
					value=va_arg(arg_ptr,long int);
					break;
				case 4: /* sig int */
					value=(long int)va_arg(arg_ptr,int);
					if ((long int)value<0) {
						value=-(long int)value;
						sign='-';
					}
					break;
				case 6: /* sig long int */
					value=va_arg(arg_ptr,long int);
					if ((long int)value<0) {
						value=-(long int)value;
						sign='-';
					}
					break;
				default:
					break;
				}
				while (value) {
					*ptr--=hexstring[value%radix+shift];
					cntr++;
					value/=radix;
				}
				if (cntr==0) {
					*ptr--='0';
					cntr++;
				}
				if (fill==' ') {
					if (sign=='-') {
						*ptr--='-';
						cntr++;
					}
					if (!minus) for (i=cntr;i<digit;i++) device_putchar(' ');
					device_puts(++ptr);
					if (minus) for (i=cntr;i<digit;i++) device_putchar(' ');
				} else {
					for (;cntr<digit-1;cntr++) *ptr--='0';
					if (sign!='-'&&cntr<digit) *ptr--='0';
					else if (sign=='-') *ptr--='-';
					device_puts(++ptr);
				}
				flag=0;
			}
		}
		format++;
	}
	/*va_end(arg_ptr);*/
}

void SCI0_printf(char *format,...)
{
	va_list arg;
	va_start(arg, format);
	Device_printf(SCI0device, format, arg);
	va_end(arg);
}

void SCI1_printf(char *format,...)
{
	va_list arg;
	va_start(arg, format);
	Device_printf(SCI1device, format, arg);
	va_end(arg);
}

void LCD_printf(char *format,...)
{
	va_list arg;
	va_start(arg, format);
	Device_printf(LCDdevice, format, arg);
	va_end(arg);
}

void sprintf(char *buff,char *format,...)
{
	va_list arg;
	va_start(arg, format);
	currentstrptr=buff;
	Device_printf(STRdevice, format, arg);
	va_end(arg);
}

/* ------------------------------------------------- */
/* LED INITIALIZATION */
/* ------------------------------------------------- */
/**********************************************************
LED 0:P5-0
LED 1:P5-1
LED 2:P5-2
LED 3:P5-3
下位4ビットを出力にする
**********************************************************/
void initLed()
{
	P5.DDR = 0xf;
}

/* ------------------------------------------------- */
/* LET LED ON */
/* ------------------------------------------------- */
/*numberは0または1*/
void turnOnLed(short int number)
{ 
	static const unsigned char mask[]={1,2,4,8};
	P5.DR.BYTE |= mask[number];
}

/* ------------------------------------------------- */
/* LET LED OFF */
/* ------------------------------------------------- */
/*numberは0または1*/
void turnOffLed(short int number)
{
	static const unsigned char mask[]={0xfe,0xfd,0xfb,0xf7};
	P5.DR.BYTE &= mask[number];
}

/* ------------------------------------------------- */
/* PUSH SW INITIALIZATION */
/* ------------------------------------------------- */
/**********************************************************
押しボタンスイッチS0：P4-4
押しボタンスイッチS1：P4-5
押しボタンスイッチS2：P4-6
押しボタンスイッチS3：P4-7
上位4ビットを入力にする．下位4ビットも一応入力にする
上位4ビットのプルアップコントロールをONにする
**********************************************************/
void initPushSW(void)
{
	P4.DDR = 0;
	P4.PCR.BYTE = 0xf0; /*P4-4,5,6,7はプルアップ */
}

/* ------------------------------------------------- */
/* GET PUSH SW  */
/* ------------------------------------------------- */
/*push swのポートを取得し，反転し，右4シフトして返す
unsigned char getPushSW(void)
{
	return ((((unsigned char)(~P4.DR.BYTE))&0xf0)>>4);
}
*/
#define getPushSW() ((((unsigned char)(~P4.DR.BYTE))&0xf0)>>4)

short int checkPushSW(short int number)
/*push sw 0,1,2,3の状態を調べる　number:0,1,2,or 3*/
/*押されていたら1、そうでなかったら0を返す*/
{
	short int ret;
	static const unsigned char mask[]={0x10,0x20,0x40,0x80};
	if (P4.DR.BYTE&mask[number]) ret=0;
	else ret=1;
	return ret;
}

/* ------------------------------------------------- */
/* PUSH 8 BIT SW INITIALIZATION */
/* ------------------------------------------------- */
/**********************************************************
8ビットスイッチS0：P2-0
8ビットスイッチS1：P2-1
8ビットスイッチS2：P2-2
8ビットスイッチS3：P2-3
8ビットスイッチS4：P2-4
8ビットスイッチS5：P2-5
8ビットスイッチS6：P2-6
8ビットスイッチS7：P2-7
全8ビットを入力にする．
全8ビットのプルアップコントロールをONにする
**********************************************************/
void init8BitSW(void)
{
	P2.DDR = 0;
	P2.PCR.BYTE = 0xff;/*8bitSWのプルアップ設定*/
}

/*8bitswのポートを取得し，反転して返す
unsigned char get8BitSW(void)
{
	return (unsigned char)(~P2.DR.BYTE);
}
*/
#define get8BitSW() (unsigned char)(~P2.DR.BYTE)

short int check8BitSW(short int number)
/*8bitsw 0,1,2,3,4,5,6,7の状態を調べる　number:0,1,2,3,4,5,6,or 7*/
/*ONなら1、そうでなかったら0を返す*/
{
	short int ret;
	static const unsigned char mask[]={1,2,4,8,0x10,0x20,0x40,0x80};
	if (P2.DR.BYTE&mask[number]) ret=0;
	else ret=1;
	return ret;
}

/*インターバルタイマ割り込みオリジナルは笠井君(1998)，越智君(2001)による開発です*/
/* ------------------------------------------------- */
/* TIMER INITIALIZATION */
/* ------------------------------------------------- */
void initTimer1Int(unsigned short int period)
/*ITU1による割り込みタイマーの設定(越智君2001による)*/
/*割り込み間隔は引数peiodで単位はμsecである*/
/*値は20971以下でなければならない*/
/*20.971msecまで*/
/*割り込みベクトル　H'000070  ;IMIA1*/
{
	unsigned int periodGRA=(unsigned int)((SYS_CLOCK*(long int)period+4)>>3);
	ITU1.TCR.BIT.CCLR=1;  /*GRAのコンペアマッチでTCNTをクリア*/
	ITU1.TCR.BIT.CKEG=0;  /*立ち上がりエッジでカウント*/
	ITU1.TCR.BIT.TPSC=3;  /*内部クロックφ/8でカウント*/
	ITU1.GRA=periodGRA-1;  /*割り込みの周期をperiod[μs]に指定*/
	ITU1.TIER.BIT.IMIEA=1; /*TCNT=GRAとなったときの割り込み要求を許可*/
	ITU1.TIER.BIT.OVIE=0;  /*オーバー・アンダーフロー発生時の割り込みを禁止*/
	ITU1.TIER.BIT.IMIEB=0;  /*TCNT=GRBとなったときの割り込みを禁止*/
}

/* ------------------------------------------------- */
/* TIMER START */
/* ------------------------------------------------- */
/*
Timer CH1 スタート
void startTimer1(void)
{
	ITU.TSTR.BYTE |= 0x02;
}

Timer CH1 ストップ
void stopTimer1(void)
{
	ITU.TSTR.BYTE &= ~0x02;
}

Timer CH1 割り込みフラグのクリア
void clearTimer1Flag(void)
{
	ITU1.TSR.BIT.IMFA=0;
}

*/
#define startTimer1()  (ITU.TSTR.BYTE |= 0x02)  /* Timer CH1 スタート   */
#define stopTimer1()   (ITU.TSTR.BYTE &= ~0x02) /* Timer CH1 ストップ   */
#define clearTimer1Flag() (ITU1.TSR.BIT.IMFA=0) /* Timer CH1 flagクリア */


