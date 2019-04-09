#include <3694.h>
#include "ltrc_lib.h"

/*-----------------------------------------INIT-----------------------------------------*/
void init(){
    //出力ポート設定
    IO.PCR8|=0xc0;//P86,P87（動作確認用LED）
    IO.PCR1|=0x06;//P11,P12（モータ）
    //SCI3printf
    initSCI3();
    //AD変換初期設定(Scanmode,70State,AN0-AN1)
    AD.CSR.BYTE = 0x39; 
    //出力レジスタの初期化
    AD.DRA=0x0000;
    AD.DRB=0x0000;
    //pwm 初期設定
    TW.TMRW.BYTE=0x03; //(0000 0011) : FTIOB FTIOC >> pwm mode
    TW.TCRW.BYTE=0xB6; //(1011 0110) : コンペアマッチAでTNCTがクリア
                                     //クロックφ/8
                                     //FTIOB FTIOC 出力端子の出力値の設定(1)
    TW.TCNT=0x0000;    // TCNTの初期化 
    TW.GRA=625;        // 0.25ms (4kHz)
    TW.TMRW.BIT.CTS=1; // TCNTカウンタスタート
}
/*-----------------------------------------WAIT-----------------------------------------*/
void msecWait(unsigned long int length){
    volatile unsigned long int i;
    for(i=0;i<length*568;i++){ 
  }
}
/*-----------------------------------------AD-CONVERT-----------------------------------------*/
void ADget(unsigned int left,unsigned int right){
    while(AD.CSR.BIT.ADF!=1);
    left  = AD.DRA; //left  : AN0 : PB0 :10
    right = AD.DRB; //right : AN1 : PB1 : 9
}
void ADled(unsigned int left,unsigned int right){
    IO.PDR8.BYTE &=0x3f;  //LED1とLED2を消灯
    if(left>right){
        IO.PDR8.BYTE |= 0x40;   //LED1を点灯
    }else if (left<right){
        IO.PDR8.BYTE |= 0x80;  //LED2を点灯
    }else{
        IO.PDR8.BYTE |= 0xc0;  //LED1とLED2を点灯
    }   
}
/*-----------------------------------------DUTY-----------------------------------------*/
//右のみデューティ比を変化させたい場合
unsigned int GRBset(int duty){
    IO.PDR1.BYTE&=0xf9; // 1111 1001
    unsigned int b=0.01*duty*625; //GRA=625に対するdutyの割合を出す
    if(b==625)b--; //duty=100
    else if(b==0)b++; //duty=0
    TW.GRB=b;
}
//左のみデューティ比を変化させたい場合
unsigned int GRCset(int duty){
    IO.PDR1.BYTE&=0xf9; // 1111 1001
    unsigned int c=0.01*duty*625; //GRA=625に対するdutyの割合を出す
    if(c==625)c--; //duty=100
    else if(c==0)c++; //duty=0
    TW.GRC=c;
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
/*-----------------------------------------OPERATE-----------------------------------------*/
void Trace(unsigned int left[],unsigned int right[],int i){
    int x;
    /*
    if(i==0){
        //i=1の時の（前回の）AD変換値と比較
      
            x=left[1]]-left[0];
            // 右に行く
            if(x>300)setOperation(80,100);
            else if(x>500)setOperation(40,100);
            else setOperation(35,65);
        }
    }else{
        //i=0の時の（前回の）AD変換値と比較
        if(right)
    }
    */
    if(left>right){
        //左が白
        x=left-rignt;
        if(x>800)setOperation(80,50);
        else setOperation(100,100);
    }else{
        //右が白
        x=right-left;
        if(x>800)setOperation(50,80);
        else setOperation(100,100);
    }
    if(left>800 && right>800){
        //見失った場合
        setOperation(0,100);//とりあえず左回転
    }
}
/*-----------------------------------------MAIN-----------------------------------------*/
int main(void){
    init();
    unsigned int ADL[2]={0};//AD変換値格納用変数
    unsigned int ADR[2]={0};//AD変換値格納用変数
    ADL[1]=0;
    ADR[1]=0;
    while(1){
        ADget(ADL[0],ADR[0]);//AD変換値の取得
        ADled(ADL[0],ADR[0]);//AD変換値によるLED点灯の変化
        Trace(ADL,ADR,0);
        msecWait(50);//50ms
        ADget(ADL[0],ADR[0]);//AD変換値の取得
        ADled(ADL[1],ADR[1]);//AD変換値によるLED点灯の変化
        Trace(ADL,ADR,1);
        msecWait(50);//50ms
    }
}