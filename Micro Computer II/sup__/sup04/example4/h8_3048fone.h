/****************************************************************
h8_3048fone.h
Copyright (c) Kosaka Lab CS TNCT

���̃C���N���[�h�t�@�C���͏��⌤�����̑�X�̌��������J������
h8/3048�p�̗L�p�Ȋ֐��Q�����ǂ��ď��₪�܂Ƃ߂����̂ł���B
06 Mar 2013 h8_3048fone.h  ���� ���ޗp�Ƀ��t�@�C��
01 Jun 2009 h8-3048.h  ���� ���ޗp�Ƀ��t�@�C��
28 Jun 2006 h8-3048.h  ���� chkgetSCI1�̃^�C�~���O�C��
 4 Dec 2003 h8-3048.h  ���� printf�X�V,initLed�X�V,initDDR�폜
08 Oct 2003 h8-3048.h  ���� stopTimer�ǉ�,getIntSCI1��BS�g�p��
 6 Jan 2003 h8_3048.h  ���� getIntSCI�o�b�N�X�y�C�X�ɑΉ��B
17 Apr 2002 h8-01.h  ���� %u�̎g������ansi�ɂ��킹���B
14 Dec 2001 h8-01.h  ����C�z�q
15 Jly 2000 h8-00.h  ����C����
22 Dec 1999 h8-99.h  ����C����
29 Oct 1999 h8-99.h  ����
05 Feb 1999 lib.h    �}��


�y�P�zSCI
�y�P�D�P�z ch1 �֌W
void initSCI1()
 SCI-ch1�̏������@38400baud, Async, 8bit , NoParity, stop1

short int SCI1_getChar()
 SCI-ch1����1byte���̓R�[�h�B�G���[�������-2���߂�B
short int SCI1_chkgetChar()
 SCI-ch1���������C��M�f�[�^�������1byte���̓R�[�h�B�Ȃ����-1���C���s�����-2���߂�B
int SCI1_getString(char *buff,int max)
 SCI1����ő�max-1�����̕�������󂯎��B�ibuff�̃T�C�Y��max�ł悢�j
short int SCI1_getInt(char prompt[])
 SCI-ch1����v�����v�g�t�ŁCshort int�̒l���󂯎��B
 ������10�i���܂���16�i�����󂯕t����B16�i����0x�Ŏn�܂�
long int SCI1_getInt4(char prompt[])
 SCI-ch1����v�����v�g�t�ŁClong int�̒l���󂯎��B
 ������10�i���܂���16�i�����󂯕t����B16�i����0x�Ŏn�܂�

void SCI1_putChar(char c)
 SCI-ch1��1�o�C�g�o�͂���B
void SCI1_putString(char *str)
 SCI-ch1�ɕ�������o�͂���B
void SCI1_printf(char *format,...)
  �֐�printf��SCI1��
  �y�ʉ��̂��߃G���[�����͂Ȃ��̂Ō����w��̏ꍇ�͒���
  �Ή�����
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

�y�P�D�Q�zSCI ch0 �֌W
void initSCI0()
 SCI-ch0�̏������@38400baud, Async, 8bit , NoParity, stop1

short int SCI0_getChar()
 SCI-ch0����1byte���̓R�[�h�B�G���[�������-2���߂�B
short int SCI0_chkgetChar()
 SCI-ch0���������C��M�f�[�^�������1byte���̓R�[�h�B�Ȃ����-1���C���s�����-2���߂�B
int SCI0_getString(char *buff,int max)
 SCI0����ő�max-1�����̕�������󂯎��B�ibuff�̃T�C�Y��max�ł悢�j
short int SCI0_getInt(char prompt[])
 SCI-ch0����v�����v�g�t�ŁCshort int�̒l���󂯎��B
 ������10�i���܂���16�i�����󂯕t����B16�i����0x�Ŏn�܂�
long int SCI0_getInt4(char prompt[])
 SCI-ch0����v�����v�g�t�ŁClong int�̒l���󂯎��B
 ������10�i���܂���16�i�����󂯕t����B16�i����0x�Ŏn�܂�

void SCI0_putChar(char c)
 SCI-ch0��1�o�C�g�o�͂���B
void SCI0_putString(char *str)
 SCI-ch0�ɕ�������o�͂���B
void SCI0_printf(char *format,...)
  �֐�printf��SCI0��
  �d�l��void SCI1_printf(char *format,...)�Q��

�y�Q�zLCD�֌W
void LCD_putchar(char data)
  LCD�Ɍ����� putchar()
void LCD_puts(char *str)
  LCD�Ɍ����� puts()
void initLCD( void )
  LCD�̏�����
void LCD_gotoxy(unsigned x,unsigned y)
  LCD�Ɍ����� gotoxy()
void LCD_clrscr(void)
  LCD�Ɍ����� clrscr()   clear screen
void LCD_printf(char *format,...)
  �֐�printf��LCD��
  �d�l��void SCI1_printf(char *format,...)�Q��

�y�R�z�����񑀍�
void sprintf(char *buff,char *format,...)
  �d�l��void SCI1_printf(char *format,...)�Q��
  buff�̂��ӂ�͌Ăяo�����ŋN����Ȃ��悤�ɂ��Ă����K�v������
long int atoi(char *buff)
  ������𐮐��^�̒l�ɕϊ�����
  ������10�i���܂���16�i���̕�������󂯕t����B16�i����0x�܂���-0x�Ŏn�܂�
 �� "123"
    "-123"
    "0x1a"
    "-0x100"

�y�S�zAKI-H8�}�U�[�{�[�h�֌W
void initLed()
 LED�̏�����
void turnOnLed(short int number)
 LED�̓_���@number��LED�ԍ���0�܂���1���w�肷��
void turnOffLed(short int number)
 LED�̏����@number��LED�ԍ���0�܂���1���w�肷��

void initPushSW(void)
 �����{�^���X�C�b�`�̏�����
unsigned char getPushSW(void)
 �����{�^���X�C�b�`�̎擾�@�r�b�g���]���CON��1�COFF��0�Ŏ擾�����B
 �����{�^���X�C�b�`�̏󋵂͑�0-��3�r�b�g�Ɍ����B
 ����̓}�N����`�Ŏ�������Ă���
short int checkPushSW(short int number)
 push sw 0,1,2,3�̏�Ԃ𒲂ׂ�@number:0,1,2,or 3
 ������Ă�����1�A�����łȂ�������0��Ԃ�

void init8BitSW(void)
 8�r�b�g�X�C�b�`�̏�����
unsigned char get8BitSW(void)
 8�r�b�g�X�C�b�`�̎擾�@�r�b�g���]���CON��1�COFF��0�Ŏ擾�����B
 8�r�b�g�X�C�b�`�̏󋵂͑�0-��7�r�b�g�Ɍ����B
 ����̓}�N����`�Ŏ�������Ă���
short int check8BitSW(short int number)
 8bitsw 0,1,2,3,4,5,6,7�̏�Ԃ𒲂ׂ�@number:0,1,2,3,4,5,6,or 7
 ON�Ȃ�1�A�����łȂ�������0��Ԃ�

�y�T�z�C���^�[�o���^�C�}���荞��
void initTimer1Int(unsigned short int period)
 ITU1�ɂ�銄�荞�݃^�C�}�[�̐ݒ�
 ���荞�݊Ԋu�͈���peiod�ŒP�ʂ̓�sec�ł���
 �l��20971�ȉ��łȂ���΂Ȃ�Ȃ��B20.971msec�܂Őݒ�\

void startTimer1(void)
 Timer CH1 �X�^�[�g
 ����̓}�N����`�Ŏ�������Ă���
void stopTimer1(void)
 Timer CH1 �X�g�b�v
 ����̓}�N����`�Ŏ�������Ă���
void clearTimer1Flag(void)
 Timer CH1 ���荞�݃t���O�̃N���A
 ����̓}�N����`�Ŏ�������Ă���


****************************************************************/

#include<stdarg.h>

extern void E_INT();
extern void D_INT();

/*����1�s��MicrosoftHyperTerminal�g�p���ɗL���ɂ���*/
/*�L���ȏꍇH8����V���A�����M����\n��\r\n�Ɏ����ϊ�����*/
#define HYPERTERMINAL

/*�V�X�e���N���b�N�֌W*/
#define SYS_CLOCK 25 /*MHz 16,20,25 ���x��z��*/

const int SCI0device=0;
const int SCI1device=1;
const int LCDdevice=2;
const int STRdevice= 3;

/*SCI�֌W�̊�{�����͊}��N(1998�N�x)�����N(2000)�̊J���ł�*/
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

/*SCI1��蕶�������[return]���I�[�����C'\n'�͎擾����Ȃ�*/
/*^H�Ńo�b�N�X�y�C�X*/
int SCI1_getString(char *buff,int max)
{
	int i,ch;
	for (i=0;i<max-1;i++) {
		ch=SCI1_getChar(); /*1�����擾*/
		*buff=(char)ch; /*1�����擾*/
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
/*SCI0��蕶�������[return]���I�[�����C'\n'�͎擾����Ȃ�*/
/*^H�Ńo�b�N�X�y�C�X*/
int SCI0_getString(char *buff,int max)
{
	int i,ch;
	for (i=0;i<max-1;i++) {
		ch=SCI0_getChar(); /*1�����擾*/
		*buff=(char)ch; /*1�����擾*/
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

/*�g��atoi*/
/* 123,-123,0x1a,-0x1a �̌`�̕������long int�ɕϊ�����*/
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

/*SCI1�փv�����v�g��\�����āCSCI1��萮���l�����*/
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

/*SCI0�փv�����v�g��\�����āCSCI0��萮���l�����*/
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
/*mesc�ԂȂɂ����Ȃ����ԉ҂��֐�*/
{
	int i,j;
	for (i=0;i<msec;i++) {
		for (j=0;j<168*SYS_CLOCK;j++);
	}
}

static void LCD_waitmicrosec(unsigned int microsec)
{/*��������microsec�ԂȂɂ����Ȃ����ԉ҂��֐�*/
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
LCD�Ɍ����� putchar()
************************************************************/
void LCD_putchar(char data)
{
	LCD_RegisterSelect=1;
	LCD_putCommand((data>>4)&0xf);
	LCD_putCommand(data&0xf);
	LCD_RegisterSelect=0;
}

/************************************************************
LCD�Ɍ����� puts()
************************************************************/
void LCD_puts(char *str)
{
	while(*str) LCD_putchar(*str++);
}

/************************************************************
LCD�̏�����
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
LCD�Ɍ����� gotoxy()
************************************************************/

void LCD_gotoxy(unsigned x,unsigned y)
{
	unsigned char point;
	point=0x80+x+0x40*y;
	LCD_putCommand2(point);
}

/************************************************************
LCD�Ɍ����� clrscr()   clear screen
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
	unsigned char digit=0; /* ���� */
	unsigned char minus=0;
	char fill=' ',format1=' ';
	unsigned char radix=10; /*N�i�*/
	char sign=' ';
	char *ptr=buf; /*�o�͕����|�C���^*/
	unsigned char cntr=0; /*�o�͕������J�E���^*/
	unsigned char shift=0; /*16�i�V�t�g 0 or 6*/
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
					while (ptr[cntr]) cntr++; /*cntr�͕�����*/
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
����4�r�b�g���o�͂ɂ���
**********************************************************/
void initLed()
{
	P5.DDR = 0xf;
}

/* ------------------------------------------------- */
/* LET LED ON */
/* ------------------------------------------------- */
/*number��0�܂���1*/
void turnOnLed(short int number)
{ 
	static const unsigned char mask[]={1,2,4,8};
	P5.DR.BYTE |= mask[number];
}

/* ------------------------------------------------- */
/* LET LED OFF */
/* ------------------------------------------------- */
/*number��0�܂���1*/
void turnOffLed(short int number)
{
	static const unsigned char mask[]={0xfe,0xfd,0xfb,0xf7};
	P5.DR.BYTE &= mask[number];
}

/* ------------------------------------------------- */
/* PUSH SW INITIALIZATION */
/* ------------------------------------------------- */
/**********************************************************
�����{�^���X�C�b�`S0�FP4-4
�����{�^���X�C�b�`S1�FP4-5
�����{�^���X�C�b�`S2�FP4-6
�����{�^���X�C�b�`S3�FP4-7
���4�r�b�g����͂ɂ���D����4�r�b�g���ꉞ���͂ɂ���
���4�r�b�g�̃v���A�b�v�R���g���[����ON�ɂ���
**********************************************************/
void initPushSW(void)
{
	P4.DDR = 0;
	P4.PCR.BYTE = 0xf0; /*P4-4,5,6,7�̓v���A�b�v */
}

/* ------------------------------------------------- */
/* GET PUSH SW  */
/* ------------------------------------------------- */
/*push sw�̃|�[�g���擾���C���]���C�E4�V�t�g���ĕԂ�
unsigned char getPushSW(void)
{
	return ((((unsigned char)(~P4.DR.BYTE))&0xf0)>>4);
}
*/
#define getPushSW() ((((unsigned char)(~P4.DR.BYTE))&0xf0)>>4)

short int checkPushSW(short int number)
/*push sw 0,1,2,3�̏�Ԃ𒲂ׂ�@number:0,1,2,or 3*/
/*������Ă�����1�A�����łȂ�������0��Ԃ�*/
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
8�r�b�g�X�C�b�`S0�FP2-0
8�r�b�g�X�C�b�`S1�FP2-1
8�r�b�g�X�C�b�`S2�FP2-2
8�r�b�g�X�C�b�`S3�FP2-3
8�r�b�g�X�C�b�`S4�FP2-4
8�r�b�g�X�C�b�`S5�FP2-5
8�r�b�g�X�C�b�`S6�FP2-6
8�r�b�g�X�C�b�`S7�FP2-7
�S8�r�b�g����͂ɂ���D
�S8�r�b�g�̃v���A�b�v�R���g���[����ON�ɂ���
**********************************************************/
void init8BitSW(void)
{
	P2.DDR = 0;
	P2.PCR.BYTE = 0xff;/*8bitSW�̃v���A�b�v�ݒ�*/
}

/*8bitsw�̃|�[�g���擾���C���]���ĕԂ�
unsigned char get8BitSW(void)
{
	return (unsigned char)(~P2.DR.BYTE);
}
*/
#define get8BitSW() (unsigned char)(~P2.DR.BYTE)

short int check8BitSW(short int number)
/*8bitsw 0,1,2,3,4,5,6,7�̏�Ԃ𒲂ׂ�@number:0,1,2,3,4,5,6,or 7*/
/*ON�Ȃ�1�A�����łȂ�������0��Ԃ�*/
{
	short int ret;
	static const unsigned char mask[]={1,2,4,8,0x10,0x20,0x40,0x80};
	if (P2.DR.BYTE&mask[number]) ret=0;
	else ret=1;
	return ret;
}

/*�C���^�[�o���^�C�}���荞�݃I���W�i���͊}��N(1998)�C�z�q�N(2001)�ɂ��J���ł�*/
/* ------------------------------------------------- */
/* TIMER INITIALIZATION */
/* ------------------------------------------------- */
void initTimer1Int(unsigned short int period)
/*ITU1�ɂ�銄�荞�݃^�C�}�[�̐ݒ�(�z�q�N2001�ɂ��)*/
/*���荞�݊Ԋu�͈���peiod�ŒP�ʂ̓�sec�ł���*/
/*�l��20971�ȉ��łȂ���΂Ȃ�Ȃ�*/
/*20.971msec�܂�*/
/*���荞�݃x�N�g���@H'000070  ;IMIA1*/
{
	unsigned int periodGRA=(unsigned int)((SYS_CLOCK*(long int)period+4)>>3);
	ITU1.TCR.BIT.CCLR=1;  /*GRA�̃R���y�A�}�b�`��TCNT���N���A*/
	ITU1.TCR.BIT.CKEG=0;  /*�����オ��G�b�W�ŃJ�E���g*/
	ITU1.TCR.BIT.TPSC=3;  /*�����N���b�N��/8�ŃJ�E���g*/
	ITU1.GRA=periodGRA-1;  /*���荞�݂̎�����period[��s]�Ɏw��*/
	ITU1.TIER.BIT.IMIEA=1; /*TCNT=GRA�ƂȂ����Ƃ��̊��荞�ݗv��������*/
	ITU1.TIER.BIT.OVIE=0;  /*�I�[�o�[�E�A���_�[�t���[�������̊��荞�݂��֎~*/
	ITU1.TIER.BIT.IMIEB=0;  /*TCNT=GRB�ƂȂ����Ƃ��̊��荞�݂��֎~*/
}

/* ------------------------------------------------- */
/* TIMER START */
/* ------------------------------------------------- */
/*
Timer CH1 �X�^�[�g
void startTimer1(void)
{
	ITU.TSTR.BYTE |= 0x02;
}

Timer CH1 �X�g�b�v
void stopTimer1(void)
{
	ITU.TSTR.BYTE &= ~0x02;
}

Timer CH1 ���荞�݃t���O�̃N���A
void clearTimer1Flag(void)
{
	ITU1.TSR.BIT.IMFA=0;
}

*/
#define startTimer1()  (ITU.TSTR.BYTE |= 0x02)  /* Timer CH1 �X�^�[�g   */
#define stopTimer1()   (ITU.TSTR.BYTE &= ~0x02) /* Timer CH1 �X�g�b�v   */
#define clearTimer1Flag() (ITU1.TSR.BIT.IMFA=0) /* Timer CH1 flag�N���A */


