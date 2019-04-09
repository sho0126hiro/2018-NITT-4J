unsigned short int x00=0x3;
unsigned short int x10=0x2;
unsigned short int y0,y1; /* x00 div x10 = y1 ... y0 */

int Division(unsigned short int x0,unsigned short int x1){
	unsigned short int x2,x3;
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
    return x2;
}

int main()
{
    unsigned short int x0,x1,x2,x3;
    y1=Division(x00,x10);
}