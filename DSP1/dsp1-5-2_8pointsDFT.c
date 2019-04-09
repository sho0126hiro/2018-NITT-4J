#include <stdio.h>
#define _USE_MATH_DEFINES //M_PIを有効にする
#include <math.h>

#define DATASIZE 8 //sampling data size

//構造体宣言
typedef struct{
    double re;//real number
    double im;//imagination number   
}complex;

//Signature
void Signature(){

	//how to use
	printf("\n1．8点DFTを行う\n");
	printf("　　問題の通り，信号系列は\n(1, -2^(1/2), -3, -2^(1/2)，1, 2^(1/2), 1, 2^(1/2))である。\n");
	printf("2．DFTを行い，振幅スペクトル・位相スペクトルを求める\n");
	printf("3．最後に，再びIDFTを行う．\n");
	printf("\n");
}

void init_complex(complex X[] ,double re[], double im[]){
    int i;
    for(i=0;i<DATASIZE;i++){
        X[i].re=re[i];
        X[i].im=im[i];
    }
}

int DiscreteFourieTransform(complex Y[],complex X[],int mode){
    //mode=1 : DFT mode=-1 : IDFT
    //XをDFTorIDFTした結果がYに代入される
    int a,b,n,k;
    if(mode==1){
        a=1;
        b=1;
    }else if (mode==-1){
        a=-1;
        b=DATASIZE;
    }else{
        printf("error");
        return -1;
    }
    complex Z[DATASIZE];
    complex Y_sum;
    //DFT or IDFT
    for(k=0;k<DATASIZE;k++){
        Y_sum.re = 0;
        Y_sum.im = 0;
        for(n=0;n<DATASIZE;n++){
            Z[n].re = X[n].re * cos((2*M_PI*n*k)/DATASIZE) + a*X[n].im * sin((2*M_PI*n*k)/DATASIZE);
            Z[n].im = X[n].im * cos((2*M_PI*n*k)/DATASIZE) - a*X[n].re * sin((2*M_PI*n*k)/DATASIZE);
            Y_sum.re += Z[n].re;
            Y_sum.im += Z[n].im;
        }
        Y[k].re=Y_sum.re / b;
        Y[k].im=Y_sum.im / b;
        
        if(0.000000 < Y[k].re && 0.000001 > Y[k].re) Y[k].re = 0.0;
        if(0.000000 < Y[k].im && 0.000001 > Y[k].im) Y[k].im = 0.0;
        if(-0.000000 > Y[k].re && -0.000001 < Y[k].re) Y[k].re = 0.0;
        if(-0.000000 > Y[k].im && -0.000001 < Y[k].im) Y[k].im = 0.0;
    }
    return 0;
}

void Magnitude(double Y[],complex X[]){
    //複素数で与えられるXの振幅スペクトル（複素数の大きさ）をYに格納する
    for(int i=0;i<DATASIZE;i++){
        Y[i]=sqrt(pow(X[i].re,2.0) + pow(X[i].im,2.0));
    }
}

void Phase(double Y[] , complex X[]){
    //複素数で与えられる位相スペクトルをYに格納する
    for(int i=0;i<DATASIZE;i++){
        Y[i] = atan2(X[i].im,X[i].re);
    }
}

void DisplayComplex(complex X[]){
    int i;
    for(i=0;i<DATASIZE;i++)printf("X[%d] = %lf + j(%lf)\n",i,X[i].re,X[i].im);
}

void DisplayMagnitude(double X[]){
    int i;
    printf("|Xk|=(");
    for(i=0;i<DATASIZE-1;i++)printf("%lf,",X[i]);
    printf("%lf)\n",X[i]);
}

void DisplayPhase(double X[]){
    int i;
    printf("arg(Xk)=(");
    for(i=0;i<DATASIZE-1;i++){
        printf("%lf,",X[i]);
    }
    printf("%lf)\n",X[i]);
}

void DisplayWord(complex X[] , double M[], double P[]){
    //DFT結果と振幅スペクトル・位相スペクトルを表示（ワード貼り付け用）
    int i;
    printf("Xk = (");
    for(i=0;i<DATASIZE-1;i++){
        printf("%1.0lf+(%1.0lf)j,",X[i].re,X[i].im);
    }
    printf("%1.0lf+(%1.0lf)j)\n",X[i].re,X[i].im);
    printf("|Xk|=(");
    for(i=0;i<DATASIZE-1;i++)printf("%1.1lf,",M[i]);
    printf("%1.1lf)\n",M[i]);
    printf("arg(X)=(");
    for(i=0;i<DATASIZE-1;i++)printf("%1.2lf,",P[i]);
    printf("%1.2lf)\n",P[i]);
}



int main(){
    Signature();
    complex Xk[DATASIZE];
    double Xk_M[DATASIZE]; //振幅スペクトル保存用
    double Xk_P[DATASIZE]; // 位相スペクトル保存用
    complex Xn[DATASIZE];
    double Xn_re[DATASIZE]={1,-1*sqrt(2),-3,-1*sqrt(2),1,sqrt(2),1,sqrt(2)};
    double Xn_im[DATASIZE]={0,         0, 0,         0,0,      0,0,     0 };
    int r=0;
    init_complex(Xn,Xn_re,Xn_im);
    printf("=======元データ=======\n");
    DisplayComplex(Xn);
    r = DiscreteFourieTransform(Xk,Xn,1);
    if(r==-1)return 0;
    printf("=======DFT結果(位相スペクトル）=======\n");
    DisplayComplex(Xk);
    printf("=======振幅スペクトル=======\n");
    Magnitude(Xk_M,Xk);
    DisplayMagnitude(Xk_M);
    printf("=======位相スペクトル=======\n");
    Phase(Xk_P,Xk);
    DisplayPhase(Xk_P);
    printf("=======Word貼り付け用=======\n");
    DisplayWord(Xk,Xk_M,Xk_P);
    r = DiscreteFourieTransform(Xn,Xk,-1);
    if(r==-1)return 0;
    printf("=======IDFT結果=======\n");
    DisplayComplex(Xn);
    return 0;
}