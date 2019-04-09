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
    double *input,*amp;
    input    = (double *)malloc(sizeof(double) * DATASIZE);
    amp      = (double *)malloc(sizeof(double) * DATASIZE);
    complex *c_input,*c_dft,*c_idft;
    c_input  = (complex *)malloc(sizeof(complex) * DATASIZE); // 入力データ >> 複素数
    c_dft    = (complex *)malloc(sizeof(complex) * DATASIZE);
    c_idft   = (complex *)malloc(sizeof(complex) * DATASIZE); // fft結果 >> 複素数
    // fileRead >> input{double} >> c_input{complex}
    char infname[512];
    char outfname[512];
    char outfname_dft[512];
    char outfname_idft[512];
    char outfname_amp[512];
    printf("dft - idftをするファイル名を入力してください >> ");
    scanf("%s",infname);
    sprintf(infname,"%s.txt",infname);
    FileRead(infname,input);
    printf("dft - idft結果を出力するファイル名を入力して下さい。>> ");
    scanf("%s",outfname);
    if(_mkdir(outfname)==0) printf("mkdir_ok\n");
    else printf("mkdir_error\n");
    sprintf(outfname_dft,"%s/%s_dft.txt",outfname,outfname);
    sprintf(outfname_idft,"%s/%s_idft.txt",outfname,outfname);
    sprintf(outfname_amp,"%s/%s_amp.txt",outfname,outfname);
    // set input_data
    for(int i=0;i<DATASIZE;i++) c_input[i] = setComplex(input[i],0);
    clock_t start,end;
    start = clock();
    // dft
    if(DiscreteFourieTransform(c_dft,c_input,1)==-1)return 0;
    end = clock();
    FileWrite_complex(outfname_dft,c_dft,DATASIZE);   
    printf("dft time = %lf[s]\n", (double)(end-start)/CLOCKS_PER_SEC);
    // amplitude spectrum
    Magnitude(amp,c_dft);
    FileWrite(outfname_amp,amp,DATASIZE);
    // ifft
    if(DiscreteFourieTransform(c_idft,c_dft,-1)==-1)return 0;
    FileWrite_complex(outfname_idft,c_idft,DATASIZE);
    // free
    free(input);
    free(amp);
    free(c_input);
    free(c_dft);
    free(c_idft);
    return 0;
}