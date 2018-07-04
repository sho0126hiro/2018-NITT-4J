<<<<<<< HEAD
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
=======
//�ｼ奇ｼ奇ｼ芥30蟷ｴ蠎ｦ繝ｻDSP1-4繝ｻ逡ｪ蜿ｷ42�ｼ奇ｼ奇ｼ�

#include <stdio.h>

#define DATASIZE 701 //逶ｸ莠堤嶌髢｢菫よ焚縲�data size
#define DATASIZE_2 71 //閾ｪ蟾ｱ逶ｸ髢｢菫よ焚縲�data size

//Signature
void Signature(){
	printf("//H30蟷ｴ蠎ｦ");
	printf("/dsp1-4");
	printf("/42 蟒｣轢ｬ縲�鄙�");
	//how to use
	printf("\n1�ｼ斬.txt縺ｨb.txt繧定ｪｭ縺ｿ霎ｼ縺ｿ縲∫嶌莠堤嶌髢｢菫よ焚繧呈ｱゅａ繧九��\n");
	printf("縲�縲�縺ｾ縺溘�∵欠螳壹＆繧後◆逶ｸ莠堤嶌髢｢菫よ焚縺ｮ荳�驛ｨ繧偵ち繝ｼ繝溘リ繝ｫ縺ｫ蜃ｺ蜉帙☆繧九��\n");
	printf("2�ｼ取ｱゅａ縺溽嶌莠堤嶌髢｢菫よ焚繧坦xy.txt縺ｨ縺励※繝輔ぃ繧､繝ｫ蜃ｺ蜉帙☆繧九�ゅ��\n");
	printf("3�ｼ残.txt繧定ｪｭ縺ｿ霎ｼ縺ｿ縲∬�ｪ蟾ｱ逶ｸ髢｢菫よ焚繧呈ｱゅａ繧九��\n");
	printf("縲�縲�縺ｾ縺溘�∵欠螳壹＆繧後◆閾ｪ蟾ｱ逶ｸ髢｢菫よ焚縺ｮ荳�驛ｨ繧偵ち繝ｼ繝溘リ繝ｫ縺ｫ蜃ｺ蜉帙☆繧九��\n");
	printf("4�ｼ取ｱゅａ縺溯�ｪ蟾ｱ逶ｸ髢｢菫よ焚繧坦xx.txt縺ｨ縺励※繝輔ぃ繧､繝ｫ蜃ｺ蜉帙☆繧九��\n");
}
//file隱ｭ縺ｿ霎ｼ縺ｿ
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
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
<<<<<<< HEAD
//File書き込み
=======
//File譖ｸ縺崎ｾｼ縺ｿ
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
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
<<<<<<< HEAD
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
=======
//逶ｸ莠堤嶌髢｢菫よ焚縺ｮ邂怜�ｺ
void CrossCorrelation(double data1[],double data2[],double Rxy[]){
	//Rxy:Xi,Yi+m縺ｮ蜀�遨咲ｵ先棡譬ｼ邏埼�榊��
	/******邂怜�ｺ謇矩��*****************
	Rxy(m) = 1/N ﾎ｣(i:0 ~ N-1) X(i) ﾃ� Y(i+m)
	N : datasize
	m : 譎る俣蟾ｮ
	1. Xi縺ｨYi+m縺ｮ蜀�遨阪ｒ縺ｨ繧翫��驟榊�励↓譬ｼ邏阪☆繧�
	2�ｼ朱�榊�励�ｮ荳ｭ霄ｫ繧貞�ｨ驛ｨ雜ｳ縺�
	3�ｼ弱ョ繝ｼ繧ｿ繧ｵ繧､繧ｺ縺ｧ蜑ｲ繧九��
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
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
<<<<<<< HEAD
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
=======
	printf("\n===逶ｸ莠堤嶌髢｢菫よ焚===\n");
	int x[10]={0,100,200,300,400,500,600,700};
	for(i=0;i<8;i++)printf("Rxy(%d)=%f\n",x[i],Rxy[x[i]]);
}
//閾ｪ蟾ｱ逶ｸ髢｢菫よ焚縺ｮ邂怜�ｺ
void AutoCorrelation(double data1[],double Rxx[]){
	//Rxx:Xi,Xi+m縺ｮ蜀�遨咲ｵ先棡譬ｼ邏埼�榊��
	/******邂怜�ｺ謇矩��*****************
	Rxx(m) = 1/N ﾎ｣(i:0 ~ N-1) X(i) ﾃ� X(i+m)
	N : datasize
	m : 譎る俣蟾ｮ
	1. Xi縺ｨXi+m縺ｮ蜀�遨阪ｒ縺ｨ繧翫��驟榊�励↓譬ｼ邏阪☆繧�
	2�ｼ朱�榊�励�ｮ荳ｭ霄ｫ繧貞�ｨ驛ｨ雜ｳ縺�
	3�ｼ弱ョ繝ｼ繧ｿ繧ｵ繧､繧ｺ縺ｧ蜑ｲ繧九��
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
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
<<<<<<< HEAD
	printf("\n===自己相関係数===\n");
=======
	printf("\n===閾ｪ蟾ｱ逶ｸ髢｢菫よ焚===\n");
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
	int x[10]={0,10,20,30,40,50,60,70};
	for(i=0;i<8;i++)printf("Rxx(%d)=%f\n",x[i],Rxx[x[i]]);
}
//main
int main(){
<<<<<<< HEAD
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
=======
	//鄂ｲ蜷�
	Signature();
	//莠ｺ蜿｣繝�繝ｼ繧ｿ譬ｼ邏埼�榊��
	double data1[DATASIZE]={0};//a.txt
	double data2[DATASIZE]={0};//b.txt
	double data3[DATASIZE_2]={0};//b.txt
	//繝輔ぃ繧､繝ｫ縺ｮ荳ｭ霄ｫ繧定ｪｭ縺ｿ霎ｼ縺ｿ縲‥ata縺ｫ譬ｼ邏阪☆繧�
	FileRead("a.txt",data1);
	FileRead("b.txt",data2);
	//譬ｼ邏咲ｵゆｺ�
	double Rxy[DATASIZE-1]={0};//逶ｸ莠堤嶌髢｢菫よ焚譬ｼ邏咲畑驟榊��
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
	CrossCorrelation(data1,data2,Rxy);
	FileWrite("Rxy.txt",Rxy,DATASIZE);

	FileRead("c.txt",data3);
<<<<<<< HEAD
	double Rxx[DATASIZE_2-1]={0};//自己相関係数格納用配列
=======
	double Rxx[DATASIZE_2-1]={0};//閾ｪ蟾ｱ逶ｸ髢｢菫よ焚譬ｼ邏咲畑驟榊��
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
	AutoCorrelation(data3,Rxx);
	FileWrite("Rxx.txt",Rxx,DATASIZE_2);
	return 0;
}
<<<<<<< HEAD
/****実行結果*****
===相互相関係数===
=======
/****螳溯｡檎ｵ先棡*****
===逶ｸ莠堤嶌髢｢菫よ焚===
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
Rxy(0)=0.025116
Rxy(100)=0.075794
Rxy(200)=0.029542
Rxy(300)=0.007626
Rxy(400)=0.007195
Rxy(500)=0.007679
Rxy(600)=0.001238
Rxy(700)=0.000000

<<<<<<< HEAD
===自己相関係数===
=======
===閾ｪ蟾ｱ逶ｸ髢｢菫よ焚===
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
Rxx(0)=0.180281
Rxx(10)=-0.027261
Rxx(20)=-0.056572
Rxx(30)=0.013220
Rxx(40)=0.002022
Rxx(50)=-0.012665
Rxx(60)=0.000095
Rxx(70)=0.010008
<<<<<<< HEAD
****************/
=======
****************/
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
