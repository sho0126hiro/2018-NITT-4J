/****************************************************************
MinSys3069.h
Copyright (c) Kosaka Lab CS TNCT

���̃C���N���[�h�t�@�C���͏��⌤�����̑�X�̌���������у��{�R���[�~�̊w��
���J�������L�p�Ȋ֐��Q�����ǂ��ď��₪�܂Ƃ߂����̂ł���B
10 Oct 2008 ksk3048.h  ���� .c .h �����@E_INT(),D_INT()
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

�y�P�zSCI ch1 �֌W�@�����PC�Ƃ̊Ԃł̒ʐM�Ɏg����
�@�@�@�g�p���\�[�X�@SCI1
void initSCI1(VP_INT exinf)
    SCI-ch1�̏������@38400baud, Ascnc, 8bit , NoParity, stop1

short int getCharSCI1()
    SCI-ch1����1byte���̓R�[�h�B�G���[�������-2���߂�B
short int chkgetCharSCI1()
    SCI-ch1���������C��M�f�[�^�������1byte���̓R�[�h�B�Ȃ����-1���C���s�����-2���߂�B
    getCharSCI1()���Ăяo���Ƃƃf�[�^������܂Ŗ߂��Ă��Ȃ����C
    chkgetCharSCI1()���Ăяo�������ɂ͂����ɖ߂��Ă���
short int getIntSCI1(char prompt[])
    SCI-ch1����v�����v�g�t�ŁCshort int�̒l���󂯎��B
    ������10�i���܂���16�i�����󂯕t����B16�i����0x�Ŏn�܂�

void putBYTESCI1(char c)
    SCI-ch1��1�o�C�g�o�͂���B
void putCharSCI1(char c)
    SCI-ch1��1�����o�͂���B'\n'�o�͎���'\r'��ǉ��o�͂���
void putStringSCI1(char *str)
    SCI-ch1�ɕ�������o�͂���B
void SCI1_printf(char *format,...)
      �֐�printf��SCI��
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

�y�Q�zLCD�֌W
void initLCD( void )
    LCD�̏�����
void LCDputchar(char data)
    LCD�Ɍ����� putchar()
void LCDputs(char *str)
    LCD�Ɍ����� puts()
void LCDgotoxy(unsigned x,unsigned y)
    LCD�Ɍ����� gotoxy()
    (0,0)�X�^�[�g
void LCDclrscr(void)
    LCD�Ɍ����� clrscr()   clear screen
void LCD_printf(char *format,...)
      �֐�printf��LCD��
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

�y�R�zAKI-H8�}�U�[�{�[�h�֌W
�@�@�@�g�p���\�[�X�@P2,P4,P5
void turnOnLed(short int number)
    LED�̓_���@number��LED�ԍ���0�܂���1,2,3���w�肷��
void turnOffLed(short int number)
    LED�̏����@number��LED�ԍ���0�܂���1,2,3���w�肷��

unsigned char getPushSW(void)
    �����{�^���X�C�b�`�̎擾�@�������|�[�g��ǂݍ��݁C�r�b�g���]�B
    �����{�^���X�C�b�`0,1,2,3,4���0,1,2,3,4�r�b�g�ɑΉ������Ă���B
    ON�ɂȂ��Ă���Ƃ���̃r�b�g��1�C�����łȂ��Ƃ���̃r�b�g��0
short int checkPushSW(short int number)
    push sw 0,1,2,3,4�̏�Ԃ𒲂ׂ�@number:0,1,2,3 or 4
    ������Ă�����1�A�����łȂ�������0��Ԃ�
unsigned char get4BitSW(void)
    4�r�b�g�X�C�b�`�̎擾�@�������|�[�g��ǂݍ��݁C�r�b�g���]�̂݁B
    4�r�b�g�X�C�b�`�̏󋵂͑�0-��7�r�b�g�Ɍ����B
    ON�ɂȂ��Ă���Ƃ���̃r�b�g��1�C�����łȂ��Ƃ���̃r�b�g��0
short int check4BitSW(short int number)
    4bitsw 0,1,2,3�̏�Ԃ𒲂ׂ�@number:0,1,2,or 3
    ON�Ȃ�1�A�����łȂ�������0��Ԃ�


�y�R�z�V�X�e���^�C�}�pITU0�֌W
void initSystemTimer()
****************************************************************/


/*SCI1�֌W*/
void initSCI1(void);
short int getCharSCI1(void);
short int chkgetCharSCI1(void);
int getStringSCI1(char *buff,int max);
short int getIntSCI1(char prompt[]);
void putCharSCI1(char c);
void putBYTESCI1(char c);
void putStringSCI1(char *str);
void SCI1_printf(char *format,...);
void SCI1_RXI_handler(VP_INT exinf);  /* SCI1���͗p���荞�݃n���h�� */
void SCI1_ERI_handler(VP_INT exinf);  /* SCI1�G���[�p���荞�݃n���h�� */

/*LCD�֌W*/
void LCDputchar(char data);
void LCDputs(char *str);
void LCDgotoxy(unsigned x,unsigned y);
void LCDclrscr(void);
void LCD_printf(char *format,...);

/*LED�֌W*/
void turnOnLed(short int number);
void turnOffLed(short int number);

/*�v�b�V���X�C�b�`�֌W*/
unsigned char getPushSW(void);
short int checkPushSW(short int number);

/*4�r�b�g�f�B�b�v�X�C�b�`�֌W*/
unsigned char get4BitSW(void);
short int check4BitSW(short int number);

/*�V�X�e���^�C�}�pITU0�֌W*/
void initSystemTimer(VP_INT exinf);
void SystemTimerHandler(VP_INT exinf);  /* �^�C�}�p���荞�݃n���h�� */

/*�J�[�l���̃A�C�h�����[�v�N���ݒ肪�ł��Ă��Ȃ����߂̑΍�*/
void idletask(VP_INT exinf);
