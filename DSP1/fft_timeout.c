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
    fp = fopen(filename,"r");
	if(fp==NULL){
		printf("can't open a file\n");
		exit(1);
		return;
	}
	for(int i=0;i<DATASIZE;i++)fscanf(fp,"%lf",&data[i]);
	fclose(fp);
}
// file書き込み
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

void FileWrite_time(char *filename,double data[],int line){
	FILE *fp;
    fp=fopen(filename,"w");
	if(fp==NULL){
		printf("[%d] can't open a file\n",__LINE__);
		exit(1);
        return;
	}
	fprintf(fp,"pow(2^n)\ttime\n");    
	for(int i=0;i<line;i++){
		fprintf(fp,"%d\t%f\n",i+1,data[i]);
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
// complex[] >> re[] , im[]
void complex_reim(complex z[] ,double re[],double im[]){
    for(int i=0;i<DATASIZE;i++){
        re[i] = z[i].re;
        im[i] = z[i].im;
    }
}

// --------------------------------------------------------//
// 複素数の和(x + y)を返す
complex ComplexAddition(complex x,complex y){
    complex result;
    result.re = x.re + y.re;
    result.im = x.im + y.im;
    return result;
}
// 複素数の差(x - y)を返す
complex ComplexSubstraction(complex x,complex y){
    complex result;
    result.re = x.re - y.re;
    result.im = x.im - y.im;
    return result;
}
// 複素数の積(x * y)を返す
complex ComplexMultiplication(complex x,complex y){
    complex result;
    result.re = x.re * y.re - x.im * y.im;
    result.im = x.re * y.im + x.im * y.re;
    return result;
}
// 複素数の商(x / y)を返す
complex ComplexDivision(complex x,complex y){
    complex result;
    result.re = (x.re * y.re + x.im * y.im)/(pow(y.re,2.0)+(pow(y.im,2.0)));
    result.im = (x.im * y.re - x.re * y.im)/(pow(y.re,2.0)+(pow(y.im,2.0)));
    return result;
}
// 共役複素数を返す
complex ComplexConjugate(complex x){
    complex result;
    result.re =      x.re;
    result.im = -1 * x.im;
    return result;
}
// 複素数の表示
void DisplayComplex(complex X[]){
    int i;
    for(i=0;i<DATASIZE;i++)printf("X[%d] = %lf + j(%lf)\n",i,X[i].re,X[i].im);
}
// --------------------------------------------------------//

// N個の回転子Wを計算する
void Rotor(complex w[],int N){
    for(int i=0;i<N/2;i++){
            w[i].re =      cos((2*M_PI/DATASIZE) * i);
            w[i].im = -1 * sin((2*M_PI/DATASIZE) * i);
    }
}
void DisplayRotor(complex X[]){
    int i;
    for(i=0;i<DATASIZE/2;i++)printf("X[%d] = %lf + j(%lf)\n",i,X[i].re,X[i].im);
}
// 複素数の大きさを求める。
// X {complex[]}の振幅スペクトルをY{double[]}に代入する
void Magnitude(double Y[],complex X[]){
    for(int i=0;i<DATASIZE;i++){
        Y[i]=sqrt(pow(X[i].re,2.0) + pow(X[i].im,2.0));
    }
}

// 振幅スペクトルの表示用
void DisplayMagnitude(double X[]){
    int i;
    printf("|Xk|=(");
    for(i=0;i<DATASIZE-1;i++){
        printf("%lf,",X[i]);
    }
    printf("%lf)\n",X[i]);
}

// =========== ビットリバーサル用 ===================
void initDeal(int deal[],int N){
    for(int i=0;i<N;i++)deal[i]=i;
}

void displayDeal(int deal[],int N){
    for (int i=0;i<DATASIZE;i++)printf("%d\n",deal[i]);
}

// 反転処理をして、順番を決める
void BitReversal(int *deal,int N){
    int i,j,tmp,result;
    for(i=0;i<N;i++){
        result = 0;
        for(j=0;j<log2f(N);j++){
            tmp = (deal[i] >> j) & 1;
            tmp <<= (int)log2(N) - 1-j;
            result += (tmp);
        }
        deal[i] = result;
    }
}

// dealに示された番号順にresultの中身を入れ替える
void rearrangeArray(double result[],int deal[]){
    double *tmp;
    tmp = (double *)malloc(sizeof(double) * DATASIZE);
    int i;
    for(i=0;i<DATASIZE;i++) tmp[i] = result[deal[i]];
    for(i=0;i<DATASIZE;i++) result[i] = tmp[i];
    free(tmp);
}
// dealに示された番号順にresultの中身を入れ替える(result:complex)
void rearrangeComplex(complex result[],int deal[]){
    complex *tmp;
    tmp = (complex *)malloc(sizeof(complex) * DATASIZE);
    int i;
    for(i=0;i<DATASIZE;i++){
        tmp[i].re = result[deal[i]].re;
        tmp[i].im = result[deal[i]].im;
    }
    for(i=0;i<DATASIZE;i++){
        result[i].re = tmp[i].re;
        result[i].im = tmp[i].im;
    }
    free(tmp);
}
// ==================================================

//FFT or IFFT
void FastFourieTransform(complex Y[],complex X[],int mode){
    // Xを FFTorIFFT した結果がYに代入される
    // mode = 0 : ifft mode != 0 ：fft
    // x >> y (input >> output)
    int i,j,k;
    int *deal;     // 並び順
    deal = (int *)malloc(sizeof(int) * DATASIZE);
    initDeal(deal,DATASIZE);
    BitReversal(deal,DATASIZE);
    rearrangeComplex(X,deal);
    complex *c_W;
    c_W = (complex *)malloc(sizeof(complex) * (DATASIZE/2));
    Rotor(c_W,DATASIZE);
    if(mode==1)for(int i=0;i<DATASIZE/2;i++)c_W[i] = ComplexConjugate(c_W[i]);
    // DisplayRotor(c_W);
    
    // fft
    for(k=0;k<(int)log2(DATASIZE);k++){
        if(k==0){
            for(j=0;j<DATASIZE;j+=2){
                // in[j] in[j+1]
                Y[j]   = ComplexAddition(X[j],ComplexMultiplication(c_W[0],X[j+1]));
                Y[j+1] = ComplexSubstraction(X[j],ComplexMultiplication(c_W[0],X[j+1]));
            }
        }else{
            for(j=0;j<DATASIZE;j+=(int)pow(2,k+1)){
                int d = 0; // 回転子配列に与える番号
                for(i=0;i<pow(2,k);i++,d+= DATASIZE / ((int)pow(2,k+1))){
                    if(d >= DATASIZE/2) d = 0;
                    complex tmp[2];
                    tmp[0] = ComplexAddition(Y[j+i],ComplexMultiplication(c_W[d],Y[j+i+(int)pow(2,k)]));
                    tmp[1] = ComplexSubstraction(Y[j+i],ComplexMultiplication(c_W[d],Y[j+i+(int)pow(2,k)]));
                    Y[j+i]  = tmp[0];
                    Y[j+i+(int)pow(2,k)]  = tmp[1];
                }
            }
        }
    }
    if(mode==1){
        // 1/Nの処理
        for(i=0;i<DATASIZE;i++){
            Y[i].re/=DATASIZE;
            Y[i].im/=DATASIZE;
        }
    }
    free(deal);
    free(c_W);
}


double fft_time(){
    double *input;
    input    = (double *)malloc(sizeof(double) * DATASIZE);
    complex *c_input,*c_fft;
    c_input  = (complex *)malloc(sizeof(complex) * DATASIZE); // 入力データ >> 複素数
    c_fft    = (complex *)malloc(sizeof(complex) * DATASIZE);
    char infname[512];
    sprintf(infname,"pow2/2^%d.txt",(int)log2(DATASIZE));
    FileRead(infname,input);
    for(int i=0;i<DATASIZE;i++) c_input[i] = setComplex(input[i],0);
    clock_t start,end;
    start = clock();
    FastFourieTransform(c_fft,c_input,0);
    end = clock();
    // 秒数を返す　単位は秒
    double time = (double)(end-start)/CLOCKS_PER_SEC;
    free(input);
    free(c_input);
    free(c_fft);
    return time;
}

int main(){
    int pow_max,pow_min;
    double times[50];
    char dir[20];
    printf("2の累乗:2^x~2^yまでのfftのタイムをファイル出力します\n");       
    printf("xとyを入力してください。(x y) >> ");
    scanf("%d %d",&pow_min,&pow_max);
    printf("ディレクトリ名を入力してください。");
    scanf("%s",dir);
    if(_mkdir(dir)==0) printf("mkdir_ok\n");
    else printf("dirmkdir_error\n");
    double *input;
    complex *c_input,*c_fft;
    int j = 0;
    for(int i=pow_min;i<=pow_max;i++,j++){
        DATASIZE = pow(2,i);
        // fft
        input    = (double *)malloc(sizeof(double) * DATASIZE);
        c_input  = (complex *)malloc(sizeof(complex) * DATASIZE); // 入力データ >> 複素数
        c_fft    = (complex *)malloc(sizeof(complex) * DATASIZE);
        char infname[512];
        sprintf(infname,"pow2/2^%d.txt",(int)log2(DATASIZE));
        FileRead(infname,input);
        for(int i=0;i<DATASIZE;i++) c_input[i] = setComplex(input[i],0);
        clock_t start,end;
        start = clock();
        FastFourieTransform(c_fft,c_input,0);
        end = clock();
        // 単位は秒
        double time = (double)(end-start)/CLOCKS_PER_SEC;
        printf("[%d] time:%lf\n",i,time);
        times[j] = time;
        free(input);
        free(c_input);
        free(c_fft);
    }
    char out[512];
    sprintf(out,"%s/fft_time.txt",dir);
    FileWrite_time(out,times,(pow_max-pow_min+1));
    return 0;
}