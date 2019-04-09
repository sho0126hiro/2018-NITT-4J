/*  msecwait関数で1秒ごとのLEDのON-OFFを行う  */
#include <3048fone.h>

void msecwait(int msec)
/*msec間なにもしない時間稼ぎ関数*/
{
    int i,j;
    for (i=0;i<msec;i++) {
        for (j=0;j<2646;j++);    /*2646は実測によって求めた値*/
    }
}

main()
{
    /*P5の下位2ビットを出力に設定*/
    /* P5のDDRの下位2ビットに1を与えるとこの設定になる*/
    /*DDRとはDataDirectionRegister(データ方向設定レジスタ)*/
    P5.DDR =  0x3;  /*0x3 = 00000011(二進数)*/
    while(1) {/*これは無限ループ*/
        /*LED0をONにする  P5のDRの第0ビットを1にする*/
        /*DRとはDataRegister(データレジスタ)*/
        P5.DR.BIT.B0=1;
        /*LED1をOFFにする  P5のDRの第1ビットを0にする*/
        P5.DR.BIT.B1=0;
        msecwait(1000);/*1000msecの間なにもしない*/
        /*LED0をOFFにする  P5のDRの第0ビットを0にする*/
        P5.DR.BIT.B0=0;
        /*LED1をONにする  P5のDRの第1ビットを1にする*/
        P5.DR.BIT.B1=1;
        msecwait(1000);
    }
}
 
