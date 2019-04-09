short int x00=0x55;
short int x10=0x02;
short int y0; /* y0=x00*x10 */
int main()
{
    short int x0,x1,x2;
    x0=x00;
    x1=x10;
    x2=0;
    do {
        if(x1&1) x2+=x0;
        x0<<=1;
        x1>>=1;
    } while (x1);
    y0=x2;
}