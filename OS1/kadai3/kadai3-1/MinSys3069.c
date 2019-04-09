/******************************************************************
HOS向け基本関数　小坂のまとめ
******************************************************************/

#include "kernel.h"
#include "kernel_id.h"
#include <stdarg.h>
#include "3069s.h"
#include "MinSys3069.h"

#define RECEIVERINGBUFFSIZE 32

static volatile int receiveptr_in;  /*input pointer for receive*/
static volatile int receiveptr_out; /*output pointer for receive*/
static unsigned char receiveringbuff[RECEIVERINGBUFFSIZE];

/* SCI初期化 */
void initSCI1(void)
{
	unsigned short int i;
	/*unsigned char dummy;*/
	SCI1.SCR.BYTE = 0;       /* clear all flags */
	                  /* 2400-38400baud are available at n=0(cks1=0,cks2=0) */
	SCI1.SMR.BYTE = 0;       /* Ascnc, 8bit , NoParity, stop1, 1/1 */
	SCI1.BRR = 15;	         /* 38400baud (CPU=20MHz) */
	for(i=0;i<60000;i++);      /* wait more than 1bit time */
	receiveptr_in=receiveptr_out=0;
	SCI1.SCR.BYTE |= 0x50;    /* scr = 0101 0000 (TIE=0,RIE=1,TE=0,RE=1) */
	SCI1.SCR.BYTE |= 0x70;    /* scr = 0111 0000 (TIE=0,RIE=1,TE=1,RE=1) */
	return;
}

/* SCI受信割り込み */
/*割り込みで直接起動ではないので通常の関数になっている*/
void SCI1_RXI_handler(VP_INT exinf)
{
	receiveringbuff[receiveptr_in]=SCI1.RDR;
	SCI1.SSR.BIT.RDRF = 0;
	receiveptr_in++;
	if (receiveptr_in==RECEIVERINGBUFFSIZE) receiveptr_in=0;
}

/*SCIエラー処理関数*/
/*割り込みで直接起動ではないので通常の関数になっている*/
void SCI1_ERI_handler(VP_INT exinf)
{
	SCI1.SSR.BIT.ORER = 0; /* Overrun Error Flag Clear */
	SCI1.SSR.BIT.FER = 0;  /* Framing Error Flag Clear */
	SCI1.SSR.BIT.PER = 0;  /* Parity  Error Flag Clear */
}

/* ------------------------------------------------- */
/* GET BYTE FROM SCI1 */
/* ------------------------------------------------- */
short int getCharSCI1(void)
/* return value 0x00-0xFF:received data */
/*              -3(0xFFFE):error */
{
	int ch;
	unsigned int loop;
	loop=60000;
	while (receiveptr_out==receiveptr_in) {
		loop--;
		if (!loop) return -3;
	}
	ch=receiveringbuff[receiveptr_out];
	receiveptr_out++;
	if (receiveptr_out==RECEIVERINGBUFFSIZE) receiveptr_out=0;
	return ch;
}

/* ------------------------------------------------- */
/* CHECK SCI BUFFER AND GET DATA */
/* ------------------------------------------------- */
short int chkgetCharSCI1(void)
/* return value -1(0xFFFF):no received data  */
/*              0x00-0xFF:received data */
{
	int ch;
	unsigned int loop;
	loop=60000;
	if (receiveptr_out==receiveptr_in) {
		return -1;
	}
	ch=receiveringbuff[receiveptr_out];
	receiveptr_out++;
	if (receiveptr_out==RECEIVERINGBUFFSIZE) receiveptr_out=0;
	return ch;
}

void putStringSCI1(char *str);

/*SCI1より文字列入力[return]が終端だが，'\n'は取得されない*/
/*^Hでバックスペイス*/
int getStringSCI1(char *buff,int max)
{
	int i,ch;
	for (i=0;i<max-1;i++) {
		ch=getCharSCI1(); /*1文字取得*/
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

/*SCI1へプロンプトを表示して，SCI1より整数値を入力*/
short int getIntSCI1(char prompt[])
/*getting integer from serial port*/
/* format 123[ret] */
/*        -123[ret] */
/*        0x1a[ret] */
/*        -0x100[ret] */
{
	short int x=0,y,m=0,n=0,v=0,i=0;
	char buff[16];
	putStringSCI1(prompt);
	getStringSCI1(buff,16);
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


/* ------------------------------------------------- */
/* PUT BYTE TO SCI1 */
/* ------------------------------------------------- */
void putBYTESCI1(char c)
{
	unsigned char tmp;
	do{
		tmp = SCI1.SSR.BYTE;
	} while((tmp & 0x80)==0);
	SCI1.TDR = c;
	SCI1.SSR.BIT.TDRE = 0;
	return;
}

/* ------------------------------------------------- */
/* PUT VHAR TO SCI1 */
/* ------------------------------------------------- */
void putCharSCI1(char c)
{
	unsigned char tmp;
	if (c=='\n') putCharSCI1('\r');
	do{
		tmp = SCI1.SSR.BYTE;
	} while((tmp & 0x80)==0);
	SCI1.TDR = c;
	SCI1.SSR.BIT.TDRE = 0;
	return;
}

void putStringSCI1(char *str)
{
	while(*str){
		putCharSCI1(*str);
		str++;
	}
}

/* Port4 -> LCD */
/* 7    6    5    4    3    2    1    0  */
/*          ES   RS  DB7  DB6  DB5  DB4  */

/* i/o */
#define LCD_Port            P4DR.BYTE
#define LCD_RegisterSelect  P4DR.BIT.B4
#define LCD_EnableSignal    P4DR.BIT.B5

static void LCDmsecwait(unsigned int msec)
/*mesc間なにもしない時間稼ぎ関数*/
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<3352;j++);    /*3352は実測によって求めた値 20MHz駆動*/
	}
}

static void LCDmicrosecwait(unsigned int microsec)
{/*だいたいmicrosec間なにもしない時間稼ぎ関数*/
	int i,j;
	for (i=0;i<microsec;i++) {
		for (j=0;j<4;j++);
	}
}

static void LCDputCommand(char command) /*command width must be 4bits*/
{
	LCD_Port=(LCD_Port&0xf0)|command;
	LCD_EnableSignal=1;
	LCDmicrosecwait(5);
	LCD_EnableSignal=0;
	LCDmicrosecwait(40);
}

static void LCDputCommand2(char command2)
{
	LCDputCommand((command2>>4)&0xf);
	LCDputCommand(command2&0xf);
}

/************************************************************
LCDに向けた putchar()
************************************************************/
void LCDputchar(char data)
{
	LCD_RegisterSelect=1;
	LCDputCommand((data>>4)&0xf);
	LCDputCommand(data&0xf);
	LCD_RegisterSelect=0;
}

/************************************************************
LCDに向けた puts()
************************************************************/
void LCDputs(char *str)
{
	while(*str) LCDputchar(*str++);
}

/************************************************************
LCDの初期化
************************************************************/
void initLCD( void )
{
	LCD_Port&=0xc0;
	LCDmsecwait(30);           /* wait 30ms */
	LCDputCommand(0x3);     /* function set */
	LCDmicrosecwait(4100);
	LCDputCommand(0x3);     /* function set */
	LCDmicrosecwait(100);
	LCDputCommand(0x3);     /* function set */
	LCDmicrosecwait(100);
	LCDputCommand(0x2);     /* function set data width=4bit*/
	LCDputCommand2(0x28);   /* function set 4bit duty:1/16,size:5*7 */
	LCDputCommand2(0x0c);   /* display on,cursor off,blink off */
	LCDputCommand2(0x06);   /* address:auto increment,cursor shift:right */
	LCDputCommand2(0x01);   /* clear display */
	LCDmicrosecwait(1640);
}

/************************************************************
LCDに向けた gotoxy()
************************************************************/

void LCDgotoxy(unsigned x,unsigned y)
{
	unsigned char point;
	point=0x80+x+0x40*y;
	LCDputCommand2(point);
}

/************************************************************
LCDに向けた clrscr()   clear screen
************************************************************/
void LCDclrscr(void)
{
	LCDputCommand2(0x01);    /* clear display */
	LCDmicrosecwait(1640);
}

const static char hexstring[]="0123456789abcdef0123456789ABCDEF";
#define MAXDIGIT 32
const static int SCI1device=1;
const static int LCDdevice=2;

static void Device_printf(int device, char *format, va_list arg_ptr)
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
	if (device==SCI1device) {
		device_putchar=putCharSCI1;
		device_puts=putStringSCI1;
	} else { /*device==LCDdevice*/
		device_putchar=LCDputchar;
		device_puts=LCDputs;
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


/**********************************************************
LED 0: Port4-bit6
LED 1: Port4-bit7
**********************************************************/
/* ------------------------------------------------- */
/* LET LED ON */
/* ------------------------------------------------- */
/*numberは0または1*/
void turnOnLed(short int number)
{
	const unsigned char mask[]={0x40,0x80};
	P4DR.BYTE |=mask[number];
	/*const(定数)が指定してあると，その変数はROMに配置される*/
}
/*******　追加説明　*******
この関数は次のように書いても同じ機能となる
void turnOnLed(short int number)
{
	if (number==0) P4DR.BYTE = P4DR.BYTE | 0x40
	if (number==2) P4DR.BYTE = P4DR.BYTE | 0x80
}
ここで
「P4DR.BYTE | 0x40」はP4DR.BYTEにおいて第6ビットを1にし，
他のビットに影響を与えないという「or演算」である

0x40 : 0100 0000
0x80 : 1000 0000
***************************/


/* ------------------------------------------------- */
/* LET LED OFF */
/* ------------------------------------------------- */
/*numberは0または1*/
void turnOffLed(short int number)
{
	const unsigned char mask[]={0xbf,0x7f};
	P4DR.BYTE &=mask[number];
	/*const(定数)が指定してあると，その変数はROMに配置される*/
}
/*******　追加説明　*******
この関数は次のように書いても同じ機能となる
void turnOffLed(short int number)
{
	if (number==0) P4DR.BYTE = P4DR.BYTE & 0xbf
	if (number==2) P4DR.BYTE = P4DR.BYTE & 0x7f
}
ここで
「P4DR.BYTE & 0xbf」はP4DR.BYTEにおいて第6ビットを0にし，
他のビットに影響を与えないという「and演算」である

0xbf : 1011 1111
0x7f : 0111 1111
***************************/



/* ------------------------------------------------- */
/* PUSH SW INITIALIZATION */
/* ------------------------------------------------- */
/**********************************************************
押しボタンスイッチS0： Port2-bit3
押しボタンスイッチS1： Port2-bit4
押しボタンスイッチS2： Port2-bit5
押しボタンスイッチS3： Port2-bit6
押しボタンスイッチS4： Port2-bit7
**********************************************************/

/* ------------------------------------------------- */
/* GET PUSH SW  */
/* ------------------------------------------------- */
/*押しボタンスイッチに対応する各ビットの状態を返す。ただしON=1，OFF=0。*/
/*押しボタンスイッチ0,1,2,3,4を第0,1,2,3,4ビットに対応させている*/
unsigned char getPushSW(void)
{
	return (((unsigned char)(~(P2DR.BYTE>>3)))&0x1f);
}

/*******　追加説明　*******
  ポートを読み込み，ビット反転し，スイッチが押され
  ているビットに１が見えるようになっている。
  演算記号「~」はすべてのビットを反転するという演算子である
***************************/

short int checkPushSW(short int number)
/*push sw 0,1,2,3,4の状態を調べる　number:0,1,2,3, or 4*/
/*押されていたら1、そうでなかったら0を返す*/
{
	short int ret;
	static const unsigned char mask[]={0x8,0x10,0x20,0x40,0x80};
	if (P2DR.BYTE&mask[number]) ret=0;
	else ret=1;
	return ret;
}

/* -------------------------------------------------
  4 BIT SW INITIALIZATION 
	P5-0 CN2-37 4bitSW-1
	P5-1 CN2-38 4bitSW-2
	P5-2 CN2-39 4bitSW-3
	P5-3 CN2-40 4bitSW-4
------------------------------------------------- */

/*4bitswの状態をそのまま返す*/
unsigned char get4BitSW(void)
{
	return (unsigned char)(~P5DR.BYTE);
}

short int check4BitSW(short int number)
/*4bitsw 0,1,2,3の状態を調べる　number:0,1,2 or 3*/
/*ONなら1、そうでなかったら0を返す*/
{
	short int ret;
	static const unsigned char mask[]={1,2,4,8};
	if (P5DR.BYTE&mask[number]) ret=0;
	else ret=1;
	return ret;
}

static void initTimer0Int(unsigned short int period)
/*ITU0による割り込みタイマーの設定(越智君2001による)*/
/*割り込み間隔は引数peiodで単位はμsecである*/
/*値は26214以下でなければならない*/
/*26.214msecまで*/
{
	unsigned long int lperiod=period;
	unsigned short int speriod;
	lperiod=lperiod*10/4;
	speriod=lperiod-1;
	ITU0.TCR.BIT.CCLR=1;  /*GRAのコンペアマッチでTCNTをクリア*/
	ITU0.TCR.BIT.CKEG=0;  /*立ち上がりエッジでカウント*/
	ITU0.TCR.BIT.TPSC=3;  /*内部クロックφ/8でカウント*/
	ITU0.GRA=speriod;  /*割り込みの周期をperiod[μs]に指定*/
	ITU.TISRA.BIT.IMIEA0=1; /*TCNT=GRAとなったときの割り込み要求を許可*/
	/* IMIA1 vector address=0x60 */
}

#define startTimer0() (ITU.TSTR.BYTE |= 0x01) /* Timer CH0 スタート */

/* OSタイマの初期化 */
void initSystemTimer(VP_INT exinf)
{
	initTimer0Int(1000); /*システムタイマは1msec*/
	startTimer0();
}

#define clearTimer0Flag() (ITU.TISRA.BIT.IMFA0=0)
/*ITU0 割り込みルーチン*/
/*割り込みで直接起動ではないので通常の関数になっている*/
void SystemTimerHandler(VP_INT exinf)
{
	/* 割り込み要因クリア */
	clearTimer0Flag();
	
	/* タイムティック供給 */
	isig_tim();
}


void idletask(VP_INT exinf)
{
	while(1);
}

