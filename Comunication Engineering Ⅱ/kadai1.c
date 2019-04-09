#include <stdio.h>
#define _USE_MATH_DEFINES //M_PI��L���ɂ���
#include <math.h>
#include <stdlib.h>

#define B_SIZE 6
int BITRATE= 200; // bitrate (bps)
double clock = 5; // �N���b�N���g��(ms)
double f_c = 200; //(ms)
int resolution = 200; // �����g��1������200���̓_�ɕ�������
double f_sample = 40000; // �T���v�����O���g���F40kHz >> T=25��sec(1/40000)

// @param : n:sampleNo. a:amp f:frequency p:phase
double getSin(int n,double a,double f,double p){
    return a*sin(2*M_PI*f*n/f_sample + p);
}

// @param : *out : wave a:amp f:frequency p:phase
void _createSin(double *out,double a,double f,double p){
    for(int i=0;i<f_sample;i++){
        out[i] = getSin(i,a,f,p);
    }
}

//File��������
void _FileWrite(char *filename,double data[],int length){
	FILE *fp;
    double t;
	fp=fopen(filename,"w");
	if(fp==NULL){
		printf("[%d] can't open a file\n",__LINE__);
		exit(1);
		return;
	}
	for(int i=0;i<1000;i++){
        t = i/f_sample;
		fprintf(fp,"%f\t%f\n",t,data[i]);
	}
	fclose(fp);
}

int main(){
    double *out = (double *)malloc(sizeof(double) * f_sample);
    double A=1.0,phi=0, f=200;
    _createSin(out,A,f,phi);
    _FileWrite("kadai1_out.txt",out,f_sample);
    return 0;
}