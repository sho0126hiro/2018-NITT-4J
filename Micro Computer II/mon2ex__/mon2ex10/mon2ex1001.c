short int x00=0x0002;
short int x10=0x0003;
short int y0; /* y0=x00*x10 */

int Multiplication(short int x0,short int x1){
	short int x2;
	x2=0;
	do {
        if(x1&1) x2+=x0;
        x0<<=1;
        x1>>=1;
    } while (x1);
    return x2;
}

int main()
{
    unsigned short int x0,x1,x2;
    y0=Multiplication(x00,x10);
}
