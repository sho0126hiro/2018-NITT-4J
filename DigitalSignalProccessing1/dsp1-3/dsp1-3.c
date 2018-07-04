#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//相関係数を求める
//注意：配列を-1で初期化するため，読み込みファイル内に-1が含まれている場合
//      使用できない．
//      atoi関数を使用しているため、読み込みファイル内の値はオーバーフローする値を取ってはならない。
//      -2147483649~2147483648

#define DATASIZE 128 //data size
#define MAX_STR_SIZE 1024 // 読み込むファイルの1行の最大文字数
#define length(data) (sizeof(data)/sizeof(data[0])) //配列の要素数を返す（main内で使うこと）

//Signature
void Signature(){
	printf("//H30年度");
	printf("/dsp1-3");
	printf("/42 廣瀬　翔");
	//how to use
	printf("\n指定するデータを配列に格納し、相関係数を求める。\n");
}

//debug
void print_data(int data[]){
	for(int i=0;i<DATASIZE;i++){
		if(i!=0 && i%10==0)printf("\n");
		printf(" %4d",data[i]);
	}
	printf("\n");
}
//debug2
void print_double_data(double data[]){
	for(int i=0;i<DATASIZE;i++){
		if(i!=0 && i%10==0)printf("\n");
		printf(" %f",data[i]);
	}
	printf("\n");
}
void init_data(int data[],int length){
	for(int i=0;i<length;i++)data[i]=-1;
}

void init_double_data(double data[],int length){
	for(int i=0;i<length;i++)data[i]=-1;
}

//ファイルの中身を読み込み、dataに格納する
void FileRead(char filename[],int data[]){
	FILE *fp;
	//printf("| function : %s | filename:%s |\n",__FUNCTION__,filename);
	fp=fopen(filename,"r");
	if(fp==NULL){
		printf("can't open a file\n");
		//exit(1);
		return;
	}
	
	char strdata[512];//読み込み時作業用配列
	int i=0;
	while(fgets(strdata,512,fp)!=NULL){
		//printf("%d : %s : %d\n",i,strdata,atoi(strdata));
		data[i]=atoi(strdata);
		i++;
	}
	//printf("| L : %d  | ===============DATA=============== |\n",__LINE__);
	//print_data(data);
	fclose(fp);
}
//平均値を求める
double average(int data[]){
	double sum=0.0;
	int i=0;
	while(data[i]!=-1){
		sum+=data[i];
		i++;
	}
	//printf("sum : %f",sum);
	sum=sum/i;
	return sum;
}
double InnerProduct(double a[],double b[],int N){
	//二本のベクトルと要素数を入力して内積を出力
	double c=0;
	double sum=0;
	for(int i=0;i<N;i++){
		c=a[i]*b[i];
		//printf("c=%f a[i]=%f b[i]=%f\n",c,a[i],b[i]);
		sum=sum+c;
		//printf("sum=%f\n",sum);
	}
	return sum;
}
void del_extension(char str[]){
	int i=0;
	while(str[i]!='.'){
		i++;
	}
	str[i]='\0';
}
void Calculation(int data1[],int data2[]){
	/*算出手順
	1.それぞれのデータについて平均値を算出する。
	2.それぞれのデータについて、データから平均値を引く。
	3.平均値を引いたそれぞれのデータを掛け合わせて全て足す。（共分散）
	4.それぞれのデータを二乗するして全て足し、ルートを取る。（ここまで内積とノルムを用いる）
	5.その後、二つのデータをかける。
	6.共分散を二つのデータをかけたものでわる。（相関係数）
	*/
	int i=0;
	double d1_a_sub[DATASIZE];//平均値を引いたデータ
	double d2_a_sub[DATASIZE];
	init_double_data(d1_a_sub,DATASIZE);
	init_double_data(d2_a_sub,DATASIZE);
	double ave1=average(data1);
	double ave2=average(data2);
	//平均値を引いた値
	//printf("\nverage(data1) : %f\n",average(data1));
	while(data1[i]!=-1){
		d1_a_sub[i]=data1[i]-ave1;
		i++;
	}
	i=0;
	while(data2[i]!=-1){
		d2_a_sub[i]=data2[i]-ave2;
		i++;
	}
	//print_double_data(d1_a_sub);
	//print_double_data(d2_a_sub);
	//掛け合わせて全て足す：内積を取る
	//d1_a_subとd2_a_sub[i]の内積を取る
	//printf("i=%d",i); //i=86
	double covariance;
	double d1_norm;
	double d2_norm;
	covariance=InnerProduct(d1_a_sub,d2_a_sub,i);
	d1_norm=sqrt(InnerProduct(d1_a_sub,d1_a_sub,i));
	d2_norm=sqrt(InnerProduct(d2_a_sub,d2_a_sub,i));
	double r;
	r=covariance/(d1_norm*d2_norm);
	//表示
	printf("相関係数r=%f\n",r);
}
void misCalculation(int data1[],int data2[]){
	int i=0;
	double d1_a_sub[DATASIZE];//平均値を引いたデータ
	double d2_a_sub[DATASIZE];
	init_double_data(d1_a_sub,DATASIZE);
	init_double_data(d2_a_sub,DATASIZE);
	//double ave1=average(data1);
	//double ave2=average(data2);
	//平均値を引いた値
	//printf("\nverage(data1) : %f\n",average(data1));
	
	while(data1[i]!=-1){
		d1_a_sub[i]=data1[i]-0;
		i++;
	}
	i=0;
	while(data2[i]!=-1){
		d2_a_sub[i]=data2[i]-0;
		i++;
	}
	
	//print_double_data(d1_a_sub);
	//print_double_data(d2_a_sub);
	//掛け合わせて全て足す：内積を取る
	//d1_a_subとd2_a_sub[i]の内積を取る
	//printf("i=%d",i); //i=86
	double covariance;
	double d1_norm;
	double d2_norm;
	covariance=InnerProduct(d1_a_sub,d2_a_sub,i);
	d1_norm=sqrt(InnerProduct(d1_a_sub,d1_a_sub,i));
	d2_norm=sqrt(InnerProduct(d2_a_sub,d2_a_sub,i));
	double r;
	r=covariance/(d1_norm*d2_norm);
	//表示
	printf("相関係数r=%f\n",r);
}
int main(){
	//署名
	Signature();
	//人口データ格納配列
	int data1[DATASIZE]={0};//H16男性人口
	int data2[DATASIZE]={0};//H16女性人口
	int data3[DATASIZE]={0};//H16総人口
	int data4[DATASIZE]={0};//S23総人口
	/*
	//各配列の要素数を取得
	int data1_length=length(data1);
	int data2_length=length(data2);
	int data3_length=length(data3);
	int data4_length=length(data4);
	*/
	//読み込みファイル名
	char fname1[]="H16男性人口.txt";
	char fname2[]="H16女性人口.txt";
	char fname3[]="H16総人口.txt";
	char fname4[]="S24総人口.txt";
	
	//dataを全て初期化（いるかまだ分からない）
	init_data(data1,DATASIZE);
	init_data(data2,DATASIZE);
	init_data(data3,DATASIZE);	
	init_data(data4,DATASIZE);
	
	//ファイルの中身を読み込み、dataに格納する
	FileRead(fname1,data1);
	FileRead(fname2,data2);
	FileRead(fname3,data3);
	FileRead(fname4,data4);
	//格納終了
	//拡張子の削除
	del_extension(fname1);
	del_extension(fname2);
	del_extension(fname3);
	del_extension(fname4);
	//data1(H16,man)とdata2(H16,woman)の相関係数を求めて表示する
	printf("平均値除去結果\n");
	printf(" %s と %s の ",fname1,fname2);
	Calculation(data1,data2);
	printf(" %s と %s の ",fname1,fname3);
	Calculation(data1,data3);
	printf(" %s と %s の ",fname1,fname4);
	Calculation(data1,data4);
	
	printf("平均値未除去結果\n");
	printf(" %s と %s の ",fname1,fname2);
	misCalculation(data1,data2);
	printf(" %s と %s の ",fname1,fname3);
	misCalculation(data1,data3);
	printf(" %s と %s の ",fname1,fname4);
	misCalculation(data1,data4);
	return 0;	
}
