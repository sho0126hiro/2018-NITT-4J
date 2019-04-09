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
/*-----------------------------------------MAIN-----------------------------------------*/
int main(void)
{
    //P86,P87を出力ポートに設定（動作確認用LED）
    IO.PCR8|=0xc0;
    //P11,P12を出力ポートに設定（モータ）
    IO.PCR1|=0x06;
    initSCI3();
    // ad
    AD.CSR.BYTE = 0x39; //AD変換初期設定
                          //0011 1001
                          //AD変換開始
                          //Scan mode
                          //(70ステート)
                          //AN0-AN1
    //出力レジスタの初期化
    AD.DRA=0x0000;
    AD.DRB=0x0000;
    
    TW.TMRW.BYTE=0x03; //(0000 0011) : FTIOB FTIOC >> pwm mode
    TW.TCRW.BYTE=0xB6; //(1011 0110) : コンペアマッチAでTNCTがクリア
                                     //クロックφ/8
                                     //FTIOB FTIOC 出力端子の出力値の設定(1)
    TW.TCNT=0x0000;    // TCNTの初期化 
    TW.GRA=625;       // 0.25ms (4kHz)
    TW.TMRW.BIT.CTS=1; // TCNTカウンタスタート
    while(1){
        unsigned int left,right;
        while(AD.CSR.BIT.ADF!=1);  /* 変換結果がでるまで待つ  */
        //A-D変換終了
        left = AD.DRA >> 6;//left
        right = AD.DRB >> 6;//right
        //LED
        //SCI3printf("left= %b (%d)[%x]  right = %b (%d)[%x]\n",left,left,left,right,right,right);
        IO.PDR8.BYTE &=0x3f;  //LED1とLED2を消灯
        if(left > 0x3ed && right > 0x3ed){
            //SCI3printf("all very white\n");
            //どちらも確実に白
            setOperation(70,70);
            //msecWait(100);
        }else if(left > 0x1c2 && right > 0x1c2){
            //どちらも多分白
           // SCI3printf("all white\n");
            setOperation(70,70);
            //msecWait(100);
        }else if(left > 0x1c2 && right <0x1c2){
            //右が境界に入ったら
            if( right < 0x78){
                //右めっちゃ黒
                //SCI3printf("left white , right very black\n");
                // うちがわ
                setOperation(85,40);
            }else{
                // そとがわ
                //SCI3printf("left white,right  tyoi black\n");
                setOperation(65,35);
            }
        }else if(left < 0x1c2 && right > 0x1c2){
            //左が境界に入ったら
            if(left < 0x87){
                //mettya kuro
                // うちがわ
                //SCI3printf("left very black right white\n");
                setOperation(40,85);
            }else{
                //SCI3printf("left tyoi black,right white\n");
                // そとがわ
                setOperation(35,65);
            }
        }else{
            //SCI3printf("soreigai\n");
        }
        AD.CSR.BIT.ADF =0; //一応
    }
}