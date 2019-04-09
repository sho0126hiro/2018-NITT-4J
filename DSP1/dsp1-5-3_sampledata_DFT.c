#define _USE_MATH_DEFINES //M_PIを有効にする
#include <math.h>

#define DATASIZE 50 //sampling data size

//構造体宣言
typedef struct{
    double re;//real number
    double im;//imagination number   
}complex;

//file読み込み
void FileRead(char *filename,double data[]){
	FILE *fp;
	//printf("| function : %s | filename:%s |\n",__FUNCTION__,filename);a
	fp=fopen(filename,"r");
	if(fp==NULL){
		printf("can't open a file\n");
		//exit(1);
		return;
	}
	int i=0;
	//while(fscanf(fp,"%lf",&data[i])!= EOF)i++;
	for(i=0;i<DATASIZE;i++)fscanf(fp,"%lf",&data[i]);
	fclose(fp);
}

void FwriteArrayConvert(complex X[],double re[], double im[]){
    for(int i=0;i<DATASIZE;i++){
        re[i]=X[i].re;
        im[i]=X[i].im;
    }
}

//File書き込み
void FileWrite(char *filename,double data[],int length){
	FILE *fp;
	//printf("| function : %s | filename:%s |\n",__FUNCTION__,filename);
	fp=fopen(filename,"w");
	if(fp==NULL){
		printf("[%d] can't open a file\n",__LINE__);
		//exit(1);
		return;
	}
	for(int i=0;i<length;i++){
		fprintf(fp,"%f\n",data[i]);
	}
	fclose(fp);
}

//complex初期化
void init_complex(complex X[DATASIZE] ,double re[DATASIZE], double im[DATASIZE]){
    int i;
    for(i=0;i<DATASIZE;i++){
        X[i].re=re[i];
        X[i].im=im[i];
    }
}

//DFT or IDFT
int DiscreteFourieTransform(complex Y[DATASIZE],complex X[DATASIZE],int mode){
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
    }
    return 0;
}

//複素数の大きさを求める。
void Magnitude(double Y[DATASIZE],complex X[DATASIZE]){
    //複素数で与えられるXの振幅スペクトル（複素数の大きさ）をYに格納する
    for(int i=0;i<DATASIZE;i++){
        Y[i]=sqrt(pow(X[i].re,2.0) + pow(X[i].im,2.0));
    }
}

//複素数の表示
void DisplayComplex(complex X[DATASIZE]){
    int i;
    for(i=0;i<DATASIZE;i++)printf("X[%d] = %lf + j(%lf)\n",i,X[i].re,X[i].im);
}

//振幅スペクトルの表示
void DisplayMagnitude(double X[DATASIZE]){
    int i;
    printf("|Xk|=(");
    for(i=0;i<DATASIZE-1;i++)printf("%lf,",X[i]);
    printf("%lf)\n",X[i]);
}

int main(){
    complex Xk[DATASIZE];
    double Xk_Mag[DATASIZE]; //振幅スペクトル保存用
    complex Xn[DATASIZE];
    double Xn_re[DATASIZE];
    double Xn_im[DATASIZE]={0};
    int r=0;
    //File read >> init
    FileRead("sampledata.txt",Xn_re);
    init_complex(Xn,Xn_re,Xn_im);
    //DFT
    r = DiscreteFourieTransform(Xk,Xn,1);
    if(r==-1)return 0;
    double Xk_re_w[DATASIZE]; //ファイル書き込み用配列
    double Xk_im_w[DATASIZE]; //ファイル書き込み用配列
    FwriteArrayConvert(Xk,Xk_re_w,Xk_im_w);
    FileWrite("sampledata_DFT_re.txt",Xk_re_w,DATASIZE);
    FileWrite("sampledata_DFT_im.txt",Xk_im_w,DATASIZE);
    //Amplitude Spectrum
    Magnitude(Xk_Mag,Xk);
    FileWrite("sampledata_AmpSpectrum.txt",Xk_Mag,DATASIZE);
    //IDFT
    r = DiscreteFourieTransform(Xn,Xk,-1);
    if(r==-1)return 0;
    double Xn_re_w[DATASIZE]; //ファイル書き込み用配列
    double Xn_im_w[DATASIZE]; //ファイル書き込み用配列
    FwriteArrayConvert(Xn,Xn_re_w,Xn_im_w);
    FileWrite("sampledata_IDFT_re.txt",Xn_re_w,DATASIZE);
    FileWrite("sampledata_IDFT_im.txt",Xn_im_w,DATASIZE);
    return 0;
}