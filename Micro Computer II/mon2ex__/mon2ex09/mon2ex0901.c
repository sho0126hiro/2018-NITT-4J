short int x00=0xfff5;
short int x10=0x0004;
short int y0,y1; /* x00 div x10 = y1 ... y0 */

int main()
{
    short int x0,x1,x2,x3,xt;
    short int opecase;
    x0=x00;
    x1=x10;
    xt=x10;
    /*P-M判定*/
    if (0<x0) {
        if (0<x1) {
            opecase=0; /*P-P*/
        } else {
            opecase=1; /*P-M*/
            x1=-x1;
        }
    } else {
        if (0<x1) {
            opecase=2; /*M-P*/
            x0=-x0;
        } else {
            opecase=3; /*M-M*/
            x1=-x1;
            x0=-x0;
            xt=-xt;
        }
    }
    /*P-M判定おわり*/
    x2=0;
    x3=1;
    /*割り算のプログラム*/
    while (x1<x0) {
        x1<<=1;
        x3<<=1;
    }
    while (x3!=0) {
        if(x1<=x0) {
            x0-=x1;
            x2+=x3;
        }
        x1>>=1;
        x3>>=1;
    }
    /*割り算終わり*/
    /*符号変更*/
    if (opecase==0) {
    } else if (opecase==1) {
        x2=-x2;
    } else  {
        if (0<x0) {
            x0=xt-x0;
            x2++;
        }
        if (opecase==2) {
            x2=-x2;
        }
    }
    y1=x2;
    y0=x0;
}