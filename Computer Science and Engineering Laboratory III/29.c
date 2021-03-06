#include <3694.h>
#include "ltrc_lib.h"

/*-----------------------------------------WAIT-----------------------------------------*/
void msecWait(unsigned long int length)
{
    //時間待ちをする処理
    volatile unsigned long int i;
    for(i=0;i<length*568;i++){ 
  }
}
/*-----------------------------------------DUTY-----------------------------------------*/
//右のみデューティ比を変化させたい場合
unsigned int GRBset(int duty){
    IO.PDR1.BYTE&=0xf9; // 1111 1001
    unsigned int b=0.01*duty*625; //GRA=625に対するdutyの割合を出す
    if(b==625)b--; //duty=100
    else if(b==0)b++; //duty=0
    TW.GRB=b
}
//左のみデューティ比を変化させたい場合
unsigned int GRCset(int duty){
    IO.PDR1.BYTE&=0xf9; // 1111 1001
    unsigned int c=0.01*duty*625; //GRA=625に対するdutyの割合を出す
    if(c==625)c--; //duty=100
    else if(b==0)c++; //duty=0
    TW.GRC=c
}
//両方同時にデューティ比を変化させたい場合
void GRset(int dutyL,int dutyR){
    GRBset(dutyL);
    GRCset(dutyR);
}
/*-----------------------------------------BRAKE-----------------------------------------*/
//両方同時ブレーキをしたい場合
void Brake(){
    GRset(100,100);
    IO.PDR1.BYTE|=0x06; // 0000 0110
}
//左のみブレーキをしたい場合：P11
void Brake_L(){
    GRBset(100);
    IO.PDR1.BYTE|=0x02; //0000 0010
}
//右のみブレーキをしたい場合：P12
void Brake_R(){
    GRCset(100);
    IO.PDR1.BYTE|=0x04; // 0000 0100
}
/*-----------------------------------------OPERATE-----------------------------------------*/
void setOperation(int B_duty,int C_duty){
    if(B_duty==-1 && C_duty==-1) Brake();
    else if(B_duty==-1)          Brake_L();
    else if(C_duty==-1)          Brake_R();
    else                         GRset(B_duty,C_duty);
}
/*-----------------------------------------MAIN-----------------------------------------*/
int main(void)
{
    //P86,P87を出力ポートに設定（動作確認用LED）
    IO.PCR8|=0xc0;
    //P11,P12を出力ポートに設定（モータ）
    IO.PCR1|=0x06;
    initSCI3();
    TW.TMRW.BYTE=0x03; //(0000 0011) : FTIOB FTIOC >> pwm mode
    TW.TCRW.BYTE=0xB6; //(1011 0110) : コンペアマッチAでTNCTがクリア
                                     //クロックφ/8
                                     //FTIOB FTIOC 出力端子の出力値の設定(1)
    TW.TCNT=0x0000;    // TCNTの初期化 
    TW.GRA=625;       // 0.25ms (4kHz)
    TW.TMRW.BIT.CTS=1; // TCNTカウンタスタート
    //正転：デューティ比を設定　停止：デューティ比0％　ブレーキ：-1
    //                    1     2     3     4     5     6     7     8     9    10    11
    int B_duty[11] = {    0,  100,  100,    0,   50,    0,   -1,    0,  100,    0,   -1};//left
    int C_duty[11] = {    0,  100,    0,  100,   50,    0,   -1,    0,  100,    0,   -1};//right
    int time[11]   = {    1, 2000, 2000, 2000, 2000,    1, 2000,    1, 2000,    1, 2000};//time(ms)
    int i;
    while(1){
        for(i=0;i<11;i++){
        	SCI3printf("[%d] %d %d [%dms]\n",i,B_duty[i],C_duty[i],time[i]);
            setOperation(B_duty[i],C_duty[i]);
            msecWait(time[i]);
        }
    }
}