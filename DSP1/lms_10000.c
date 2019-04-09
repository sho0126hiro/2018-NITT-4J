#include <stdio.h>
#define _USE_MATH_DEFINES //M_PIを有効にする
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define ALPHA 0.95
int _wn_size=100; //wnのファイルサイズ (=xn fileSize)
int _sample=12000; //wnのファイルサイズ (=xn fileSize)
double _lambda = 0.000001; // ステップゲインmyuが0になるのを防ぐ非常に小さな値

/** 外部出力するものを格納する**/
double error[12000];
double _e[12000];
double _x0[12000];
double _d[12000];
double _y[12000];
double _ara11[12000];

int FileCounter(char *filename){
    FILE *fp;
    char tmp[512];
	int fileCount = 0;
    fp=fopen(filename,"r");
	if(fp==NULL){
		printf("can't open a file\n");
		exit(1);
		return -1;
	}
	int i=0;
	while (fgets(tmp, 512, fp) != NULL) fileCount++;
	fclose(fp);
    return fileCount;
}
// file読み込み
void FileRead(char *filename,double data[],int length){
	FILE *fp;
	fp=fopen(filename,"r");
	if(fp==NULL){
		printf("can't open a file\n");
		exit(1);
		return;
	}
	int i=0;
	for(i=0;i<length;i++)fscanf(fp,"%lf",&data[i]);
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

void initArray(double *target){
    for(int i=0;i<_wn_size;i++){
        target[i] = 0.0;
    }
}
// ホワイトノイズ作成
double _whitenoise(){
    double r1,r2,shigma=1.0,myu=0.0; // shigma : 分散
    r1 = (double)rand()/RAND_MAX;
    r2 = (double)rand()/RAND_MAX;
    while(!r1)r1=(double)rand()/RAND_MAX;
    return sqrt(-2*log(r1))*cos(2.0*M_PI*r2)*sqrt(shigma);
}
// 有色信号
double _colored(void)
{
	double now;
	static double previous=0.0;
	now = _whitenoise() + ALPHA * previous;
	previous = now;
	return now;
}

// 配列a,bの内積を返す
double InnerProduct(double a[],double b[],int N){
	double c=0;
	double sum=0;
	for(int i=0;i<N;i++){
		c=a[i]*b[i];
		sum=sum+c;
	}
	return sum;
}

// 配列a,bのノルムを返す
double Norm(double a[],int N){
	double c=0;
	double sum=0;
	for(int i=0;i<N;i++){
		c=a[i]*a[i];
		sum=sum+c;
	}
	return sum;
}
void lsm(double *xn,double *hn,double *wn){
    double d,y,e,myu;
    double e_pre; // eの前回のデータを保存する
    initArray(xn);
    initArray(hn);
    // error = (double *)malloc(sizeof(double) * _sample);
    for(int i=0;i<_sample;i++){
        // 入力信号の更新
        for(int j=_wn_size-1;j>0;j--) xn[j]= xn[j-1];
         xn[0] = _whitenoise(); //白色信号
        // xn[0] = _colored();  // 有色信号
        // xn[0] = _ara11[i];     // 音声信号
        _x0[i]=xn[0];
        // dを計算ｎする
        d = InnerProduct(xn,wn,_wn_size);
        y = InnerProduct(hn,xn,_wn_size);
        _d[i] = d;
        _y[i] = y;
        e = d-y;
        // myu = 1/(Norm(xn,_wn_size)+_lambda);
        for(int j=0;j<_wn_size;j++){
            hn[j]+= xn[j]*e*1/(Norm(xn,_wn_size)+_lambda);
        }
        if(!e)e=e_pre;
        error[i] = 10*log10(pow(e,2));
        _e[i] = e;
        if(i<30)printf("e = %lf\n",e);
        e_pre = e;
    }
    // fileWrite
    FileWrite("white_error.txt",error,_sample);
    FileWrite("ara11_e.txt",_e,_sample);
    FileWrite("ara11_x.txt",_x0,_sample);
    FileWrite("ara11_d.txt",_y,_sample);
    FileWrite("ara11_y.txt",_d,_sample);
}

int main(){
    double *xn;			//入力信号ベクトル
	double *hn;			//推定システム
	double *wn;			//未知システム
	// double *input;		//入力ファイル
    srand((unsigned)time(NULL));
    // _datasize = FileCounter("test.txt");
    // input = (double *)malloc(sizeof(double) * _datasize);
    xn = (double *)malloc(sizeof(double) * _wn_size);
    hn = (double *)malloc(sizeof(double) * _wn_size);
    wn = (double *)malloc(sizeof(double) * _wn_size);
    // FileRead("test.txt",input,_datasize);
    FileRead("ara11_s.txt",_ara11,_sample);
    FileRead("wn.txt",wn,_wn_size);
    lsm(xn,hn,wn);
    
    return 0;
}