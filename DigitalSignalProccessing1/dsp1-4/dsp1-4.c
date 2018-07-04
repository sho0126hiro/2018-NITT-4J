//＊＊＊H30年度・DSP1-4・番号42＊＊＊

#include <stdio.h>

#define DATASIZE 701 //相互相関係数　data size
#define DATASIZE_2 71 //自己相関係数　data size

//Signature
void Signature(){
	printf("//H30年度");
	printf("/dsp1-4");
	printf("/42 廣瀬　翔");
	//how to use
	printf("\n1．a.txtとb.txtを読み込み、相互相関係数を求める。\n");
	printf("　　また、指定された相互相関係数の一部をターミナルに出力する。\n");
	printf("2．求めた相互相関係数をRxy.txtとしてファイル出力する。\n");
	printf("3．c.txtを読み込み、自己相関係数を求める。\n");
	printf("　　また、指定された自己相関係数の一部をターミナルに出力する。\n");
	printf("4．求めた自己相関係数をRxx.txtとしてファイル出力する。\n");
}
//file読み込み
void FileRead(char *filename,double data[]){
	FILE *fp;
	//printf("| function : %s | filename:%s |\n",__FUNCTION__,filename);
	fp=fopen(filename,"r");
	if(fp==NULL){
		printf("can't open a file\n");
		//exit(1);
		return;
	}
	int i=0;
	while(fscanf(fp,"%lf",&data[i])!= EOF)i++;
	fclose(fp);
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
//相互相関係数の算出
void CrossCorrelation(double data1[],double data2[],double Rxy[]){
	//Rxy:Xi,Yi+mの内積結果格納配列
	/******算出手順*****************
	Rxy(m) = 1/N Σ(i:0 ~ N-1) X(i) × Y(i+m)
	N : datasize
	m : 時間差
	1. XiとYi+mの内積をとり、配列に格納する
	2．配列の中身を全部足す
	3．データサイズで割る。
	*******************************/
	int i,m,j;
	double sum;
	for(m=0;m<=DATASIZE-1;m++){
		sum=0;
		for(i=0;i<=DATASIZE-1-m;i++){
			sum+=data1[i]*data2[m+i];
		}
		sum/=DATASIZE;
        Rxy[m]=sum;
		//printf("Rxy[%d]=%f",m,Rxy[m]);
	}
	printf("\n===相互相関係数===\n");
	int x[10]={0,100,200,300,400,500,600,700};
	for(i=0;i<8;i++)printf("Rxy(%d)=%f\n",x[i],Rxy[x[i]]);
}
//自己相関係数の算出
void AutoCorrelation(double data1[],double Rxx[]){
	//Rxx:Xi,Xi+mの内積結果格納配列
	/******算出手順*****************
	Rxx(m) = 1/N Σ(i:0 ~ N-1) X(i) × X(i+m)
	N : datasize
	m : 時間差
	1. XiとXi+mの内積をとり、配列に格納する
	2．配列の中身を全部足す
	3．データサイズで割る。
	*******************************/ 
	int i,m,j;
	double sum;
	for(m=0;m<=DATASIZE_2-1;m++){
		sum=0;
		for(i=0;i<=DATASIZE_2-1-m;i++){
			sum+=data1[i]*data1[m+i];
		}
		sum/=DATASIZE_2;
        Rxx[m]=sum;
		//printf("Rxy[%d]=%f",m,Rxy[m]);
	}
	printf("\n===自己相関係数===\n");
	int x[10]={0,10,20,30,40,50,60,70};
	for(i=0;i<8;i++)printf("Rxx(%d)=%f\n",x[i],Rxx[x[i]]);
}
//main
int main(){
	//署名
	Signature();
	//人口データ格納配列
	double data1[DATASIZE]={0};//a.txt
	double data2[DATASIZE]={0};//b.txt
	double data3[DATASIZE_2]={0};//b.txt
	//ファイルの中身を読み込み、dataに格納する
	FileRead("a.txt",data1);
	FileRead("b.txt",data2);
	//格納終了
	double Rxy[DATASIZE-1]={0};//相互相関係数格納用配列
	CrossCorrelation(data1,data2,Rxy);
	FileWrite("Rxy.txt",Rxy,DATASIZE);

	FileRead("c.txt",data3);
	double Rxx[DATASIZE_2-1]={0};//自己相関係数格納用配列
	AutoCorrelation(data3,Rxx);
	FileWrite("Rxx.txt",Rxx,DATASIZE_2);
	return 0;
}
/****実行結果*****
===相互相関係数===
Rxy(0)=0.025116
Rxy(100)=0.075794
Rxy(200)=0.029542
Rxy(300)=0.007626
Rxy(400)=0.007195
Rxy(500)=0.007679
Rxy(600)=0.001238
Rxy(700)=0.000000

===自己相関係数===
Rxx(0)=0.180281
Rxx(10)=-0.027261
Rxx(20)=-0.056572
Rxx(30)=0.013220
Rxx(40)=0.002022
Rxx(50)=-0.012665
Rxx(60)=0.000095
Rxx(70)=0.010008
****************/