//������H30�N�x�EDSP1-4�E�ԍ�42������

#include <stdio.h>

#define DATASIZE 701 //���ݑ��֌W���@data size
#define DATASIZE_2 71 //���ȑ��֌W���@data size

//Signature
void Signature(){
	printf("//H30�N�x");
	printf("/dsp1-4");
	printf("/42 �A���@��");
	//how to use
	printf("\n1�Da.txt��b.txt��ǂݍ��݁A���ݑ��֌W�������߂�B\n");
	printf("�@�@�܂��A�w�肳�ꂽ���ݑ��֌W���̈ꕔ���^�[�~�i���ɏo�͂���B\n");
	printf("2�D���߂����ݑ��֌W����Rxy.txt�Ƃ��ăt�@�C���o�͂���B\n");
	printf("3�Dc.txt��ǂݍ��݁A���ȑ��֌W�������߂�B\n");
	printf("�@�@�܂��A�w�肳�ꂽ���ȑ��֌W���̈ꕔ���^�[�~�i���ɏo�͂���B\n");
	printf("4�D���߂����ȑ��֌W����Rxx.txt�Ƃ��ăt�@�C���o�͂���B\n");
}
//file�ǂݍ���
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
//File��������
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
//���ݑ��֌W���̎Z�o
void CrossCorrelation(double data1[],double data2[],double Rxy[]){
	//Rxy:Xi,Yi+m�̓��ό��ʊi�[�z��
	/******�Z�o�菇*****************
	Rxy(m) = 1/N ��(i:0 ~ N-1) X(i) �~ Y(i+m)
	N : datasize
	m : ���ԍ�
	1. Xi��Yi+m�̓��ς��Ƃ�A�z��Ɋi�[����
	2�D�z��̒��g��S������
	3�D�f�[�^�T�C�Y�Ŋ���B
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
	printf("\n===���ݑ��֌W��===\n");
	int x[10]={0,100,200,300,400,500,600,700};
	for(i=0;i<8;i++)printf("Rxy(%d)=%f\n",x[i],Rxy[x[i]]);
}
//���ȑ��֌W���̎Z�o
void AutoCorrelation(double data1[],double Rxx[]){
	//Rxx:Xi,Xi+m�̓��ό��ʊi�[�z��
	/******�Z�o�菇*****************
	Rxx(m) = 1/N ��(i:0 ~ N-1) X(i) �~ X(i+m)
	N : datasize
	m : ���ԍ�
	1. Xi��Xi+m�̓��ς��Ƃ�A�z��Ɋi�[����
	2�D�z��̒��g��S������
	3�D�f�[�^�T�C�Y�Ŋ���B
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
	printf("\n===���ȑ��֌W��===\n");
	int x[10]={0,10,20,30,40,50,60,70};
	for(i=0;i<8;i++)printf("Rxx(%d)=%f\n",x[i],Rxx[x[i]]);
}
//main
int main(){
	//����
	Signature();
	//�l���f�[�^�i�[�z��
	double data1[DATASIZE]={0};//a.txt
	double data2[DATASIZE]={0};//b.txt
	double data3[DATASIZE_2]={0};//b.txt
	//�t�@�C���̒��g��ǂݍ��݁Adata�Ɋi�[����
	FileRead("a.txt",data1);
	FileRead("b.txt",data2);
	//�i�[�I��
	double Rxy[DATASIZE-1]={0};//���ݑ��֌W���i�[�p�z��
	CrossCorrelation(data1,data2,Rxy);
	FileWrite("Rxy.txt",Rxy,DATASIZE);

	FileRead("c.txt",data3);
	double Rxx[DATASIZE_2-1]={0};//���ȑ��֌W���i�[�p�z��
	AutoCorrelation(data3,Rxx);
	FileWrite("Rxx.txt",Rxx,DATASIZE_2);
	return 0;
}
/****���s����*****
===���ݑ��֌W��===
Rxy(0)=0.025116
Rxy(100)=0.075794
Rxy(200)=0.029542
Rxy(300)=0.007626
Rxy(400)=0.007195
Rxy(500)=0.007679
Rxy(600)=0.001238
Rxy(700)=0.000000

===���ȑ��֌W��===
Rxx(0)=0.180281
Rxx(10)=-0.027261
Rxx(20)=-0.056572
Rxx(30)=0.013220
Rxx(40)=0.002022
Rxx(50)=-0.012665
Rxx(60)=0.000095
Rxx(70)=0.010008
****************/