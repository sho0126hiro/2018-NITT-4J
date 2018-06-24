//＊＊＊H30年度・DSP1-4・番号42＊＊＊

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DATASIZE 701 //data size

//Signature
void Signature(){
	printf("//H30年度");
	printf("/dsp1-4");
	printf("/42 廣瀬　翔");
	//how to use
	printf("\na.txtとb.txtを入力し、相互相関係数を求める\n");
	printf("求めた相互相関係数をc-2.txtに出力する。\n");
	printf("また、指定されたデータをprintfで出力する。\n");
}
//file読み込み
void FileRead(char filename[],double data[]){
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
void FileWrite(char filename[],double data[]){
	FILE *fp;
	printf("| function : %s | filename:%s |\n",__FUNCTION__,filename);
	fp=fopen(filename,"w");
	if(fp==NULL){
		printf("[%d] can't open a file\n",__LINE__);
		//exit(1);
		return;
	}
	for(int i=0;i<DATASIZE-1;i++){
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
		for(i=1;i<=DATASIZE-1-m;i++){
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
void AutoCorrelation(double data1[],double Rxx[]){
	//Rxx:Xi,Xi+mの内積結果格納配列
	/******算出手順*****************
	Rxx(m) = 1/N Σ(i:0 ~ N-1) X(i) × X(i+m)
	N : datasize
	m : 時間差
	1. XiとXi+mの内積をとり、配列に格納する
	2．配列の中身を全部足す
	3．データサイズで割る。

	dataとしてそれが存在しな場合、0として内積を計算する。
	*******************************/ 
	int i,m,j;
	double sum;
	for(m=0;m<=DATASIZE-1;m++){
		sum=0;
		for(i=1;i<=DATASIZE-1-m;i++){
			sum+=data1[i]*data1[m+i];
		}
		sum/=DATASIZE;
        Rxx[m]=sum;
		//printf("Rxy[%d]=%f",m,Rxy[m]);
	}
	printf("\n===自己相関係数===\n");
	int x[10]={0,10,200,30,40,50,60,70};
	for(i=0;i<8;i++)printf("Rxx(%d)=%f\n",x[i],Rxx[x[i]]);
}
//main
int main(){
	//署名
	Signature();
	//人口データ格納配列
	double data1[DATASIZE]={0};//a.txt
	double data2[DATASIZE]={0};//b.txt

	//読み込みファイル名
	char fname1[]="a.txt";
	char fname2[]="b.txt";


	//ファイルの中身を読み込み、dataに格納する
	FileRead(fname1,data1);
	FileRead(fname2,data2);
	//格納終了
	//print_double_data(data1);
	double Rxy[DATASIZE-1]={0};//Xi,Yi+mの内積結果格納配列
	double Rxx[DATASIZE-1]={0};

	CrossCorrelation(data1,data2,Rxy);
	AutoCorrelation(data1,Rxx);

	char fname3[]="c.txt"; //相互相関係数出力ファイル名
	char fname4[]="d.txt"; //自己相関係数出力ファイル名
	//fileへの書き込み
	FileWrite(fname3,Rxy);
	FileWrite(fname4,Rxx);

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
Rxx(0)=0.153434
Rxx(10)=0.017043
Rxx(200)=0.018082
Rxx(30)=-0.029945
Rxx(40)=-0.041221
Rxx(50)=-0.042206
Rxx(60)=-0.015651
Rxx(70)=-0.025268
****************/
