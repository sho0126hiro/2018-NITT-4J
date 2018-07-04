unsigned short int x00=0x87;
unsigned short int x10=0xa;
unsigned short int y0,y1; /* x00 div x10 = y1 ... y0 */

int main()
{
    unsigned short int x0,x1,x2,x3;
    x0=x00;
    x1=x10;
    x2=0;
    x3=1;
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
    y1=x2;
    y0=x0;
}