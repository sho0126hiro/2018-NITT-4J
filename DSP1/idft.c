#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES //M_PIを有効にする
#include <math.h>
#include <time.h>
#include <direct.h>

int DATASIZE;

//構造体宣言
typedef struct{
    double re; //real number
    double im; //imagination number   
}complex;

//file読み込み
void FileRead(char *filename,double data[]){
	FILE *fp;
	fp=fopen(filename,"r");
	if(fp==NULL){
		printf("can't open a file\n");
		exit(1);
		return;
	}
	int i=0;
	for(i=0;i<DATASIZE;i++)fscanf(fp,"%lf",&data[i]);
	fclose(fp);
}

//File書き込み
void FileWrite(char *filename,double data[],int length){
	FILE *fp;
	fp=fopen(filename,"w");
	if(fp==NULL){
		printf("[%d] can't open a file\n",__LINE__);
		exit(1);
		return;
	}
	for(int i=0;i<length;i++){
		fprintf(fp,"%f\n",data[i]);
	}
	fclose(fp);
}

void FwriteArrayConvert(complex X[],double re[], double im[]){
    for(int i=0;i<DATASIZE;i++){
        re[i]=X[i].re;
        im[i]=X[i].im;
    }
}

void FileWrite_complex(char *filename,complex data[],int length){
	FILE *fp;
    fp=fopen(filename,"w");
	if(fp==NULL){
		printf("[%d] can't open a file\n",__LINE__);
		exit(1);
        return;
	}
	fprintf(fp,"Real part\tImaginary part\n");    
	for(int i=0;i<length;i++){
		fprintf(fp,"%f\t%f\n",data[i].re,data[i].im);
	}
	fclose(fp);
}

// re,im >> complex
complex setComplex(double x,double y){
    complex result;
    result.re = x;
    result.im = y;
    return result;
}

//DFT or IDFT
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
    complex *Z;
    Z = (complex *)malloc(sizeof(complex)*(DATASIZE));
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
    }
    free(Z);
    return 0;
}

//複素数の大きさを求める。
void Magnitude(double Y[],complex X[]){
    //複素数で与えられるXの振幅スペクトル（複素数の大きさ）をYに格納する
    for(int i=0;i<DATASIZE;i++){
        Y[i]=sqrt(pow(X[i].re,2.0) + pow(X[i].im,2.0));
    }
}

//複素数の表示
void DisplayComplex(complex X[]){
    int i;
    for(i=0;i<DATASIZE;i++)printf("X[%d] = %lf + j(%lf)\n",i,X[i].re,X[i].im);
}

//振幅スペクトルの表示
void DisplayMagnitude(double X[]){
    int i;
    printf("|Xk|=(");
    for(i=0;i<DATASIZE-1;i++)printf("%lf,",X[i]);
    printf("%lf)\n",X[i]);
}

int main(){
    printf("データサイズを入力してください >> ");
    scanf("%d",&DATASIZE);
    double *input;
    input    = (double *)malloc(sizeof(double) * DATASIZE);
    complex *c_input,*c_idft;
    c_input  = (complex *)malloc(sizeof(complex) * DATASIZE); // 入力データ >> 複素数
    c_idft   = (complex *)malloc(sizeof(complex) * DATASIZE); // fft結果 >> 複素数
    // fileRead >> input{double} >> c_input{complex}
    char infname[512];
    char outfname[512];
    printf("idftをするファイル名を入力してください >> ");
    scanf("%s",infname);
    FileRead(infname,input);
    for(int i=0;i<DATASIZE;i++) c_input[i] = setComplex(input[i],0);
    int r = DiscreteFourieTransform(c_idft,c_input,-1);
    if(r==-1)return 0;
    printf("idft結果を出力するファイル名を入力して下さい。>> ");
    scanf("%s",outfname);
    FileWrite_complex(outfname,c_idft,DATASIZE);
    return 0;
}