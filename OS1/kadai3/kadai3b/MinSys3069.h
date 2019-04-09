/****************************************************************
MinSys3069.h
Copyright (c) Kosaka Lab CS TNCT

このインクルードファイルは小坂研究室の代々の研究生およびロボコンゼミの学生
が開発した有用な関数群を改良して小坂がまとめたものである。
10 Oct 2008 ksk3048.h  小坂 .c .h 分離　E_INT(),D_INT()
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

【１】SCI ch1 関係　これはPCとの間での通信に使われる
　　　使用リソース　SCI1
void initSCI1(VP_INT exinf)
    SCI-ch1の初期化　38400baud, Ascnc, 8bit , NoParity, stop1

short int getCharSCI1()
    SCI-ch1から1byte入力コード。エラーがあると-2が戻る。
short int chkgetCharSCI1()
    SCI-ch1を検査し，受信データがあれば1byte入力コード。なければ-1が，失敗すると-2が戻る。
    getCharSCI1()を呼び出すととデータが来るまで戻ってこないが，
    chkgetCharSCI1()を呼び出した時にはすぐに戻ってくる
short int getIntSCI1(char prompt[])
    SCI-ch1からプロンプト付で，short intの値を受け取る。
    正負の10進数または16進数を受け付ける。16進数は0xで始まる

void putBYTESCI1(char c)
    SCI-ch1に1バイト出力する。
void putCharSCI1(char c)
    SCI-ch1に1文字出力する。'\n'出力時に'\r'を追加出力する
void putStringSCI1(char *str)
    SCI-ch1に文字列を出力する。
void SCI1_printf(char *format,...)
      関数printfのSCI版
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

【２】LCD関係
void initLCD( void )
    LCDの初期化
void LCDputchar(char data)
    LCDに向けた putchar()
void LCDputs(char *str)
    LCDに向けた puts()
void LCDgotoxy(unsigned x,unsigned y)
    LCDに向けた gotoxy()
    (0,0)スタート
void LCDclrscr(void)
    LCDに向けた clrscr()   clear screen
void LCD_printf(char *format,...)
      関数printfのLCD版
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

【３】AKI-H8マザーボード関係
　　　使用リソース　P2,P4,P5
void turnOnLed(short int number)
    LEDの点灯　numberはLED番号で0または1,2,3を指定する
void turnOffLed(short int number)
    LEDの消灯　numberはLED番号で0または1,2,3を指定する

unsigned char getPushSW(void)
    押しボタンスイッチの取得　ただしポートを読み込み，ビット反転。
    押しボタンスイッチ0,1,2,3,4を第0,1,2,3,4ビットに対応させている。
    ONになっているところのビットが1，そうでないところのビットは0
short int checkPushSW(short int number)
    push sw 0,1,2,3,4の状態を調べる　number:0,1,2,3 or 4
    押されていたら1、そうでなかったら0を返す
unsigned char get4BitSW(void)
    4ビットスイッチの取得　ただしポートを読み込み，ビット反転のみ。
    4ビットスイッチの状況は第0-第7ビットに現れる。
    ONになっているところのビットが1，そうでないところのビットは0
short int check4BitSW(short int number)
    4bitsw 0,1,2,3の状態を調べる　number:0,1,2,or 3
    ONなら1、そうでなかったら0を返す


【３】システムタイマ用ITU0関係
void initSystemTimer()
****************************************************************/


/*SCI1関係*/
void initSCI1(void);
short int getCharSCI1(void);
short int chkgetCharSCI1(void);
int getStringSCI1(char *buff,int max);
short int getIntSCI1(char prompt[]);
void putCharSCI1(char c);
void putBYTESCI1(char c);
void putStringSCI1(char *str);
void SCI1_printf(char *format,...);
void SCI1_RXI_handler(VP_INT exinf);  /* SCI1入力用割り込みハンドラ */
void SCI1_ERI_handler(VP_INT exinf);  /* SCI1エラー用割り込みハンドラ */

/*LCD関係*/
void LCDputchar(char data);
void LCDputs(char *str);
void LCDgotoxy(unsigned x,unsigned y);
void LCDclrscr(void);
void LCD_printf(char *format,...);

/*LED関係*/
void turnOnLed(short int number);
void turnOffLed(short int number);

/*プッシュスイッチ関係*/
unsigned char getPushSW(void);
short int checkPushSW(short int number);

/*4ビットディップスイッチ関係*/
unsigned char get4BitSW(void);
short int check4BitSW(short int number);

/*システムタイマ用ITU0関係*/
void initSystemTimer(VP_INT exinf);
void SystemTimerHandler(VP_INT exinf);  /* タイマ用割り込みハンドラ */

/*カーネルのアイドルループ起動設定ができていないための対策*/
void idletask(VP_INT exinf);
