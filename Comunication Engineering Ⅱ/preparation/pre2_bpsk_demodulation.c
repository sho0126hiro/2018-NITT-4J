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

// demodulation �����g�i�����g���悶�邾���j
void _de_BPSK(double *out, double A_c,double phi_c,double *in){
    int i,j;
    double tmp;
    for(i=0;i<f_sample;i++){
        out[i] = in[i] * A_c*cos(2*M_PI*f_c*(i/f_sample)+phi_c);
    }
}

//file�ǂݍ���
void FileRead(char *filename,double data[]){
	FILE *fp;
    double tmp;
	fp=fopen(filename,"r");
	if(fp==NULL){
		printf("can't open a file\n");
		exit(1);
		return;
	}
	int i=0;
	for(i=0;i<f_sample;i++)fscanf(fp,"%lf\t%lf",&tmp,&data[i]);
	fclose(fp);
}

//File��������
void FileWrite(char *filename,double data[],int length){
	FILE *fp;
    double t;
	fp=fopen(filename,"w");
	if(fp==NULL){
		printf("[%d] can't open a file\n",__LINE__);
		exit(1);
		return;
	}
	for(int i=0;i<length;i++){
        // if(i<200)printf("%f",data[i]);
        t = i/f_sample;
		fprintf(fp,"%f\t%f\n",t,data[i]);
	}
	fclose(fp);
}

int main(){
    double  *in = (double *)malloc(sizeof(double) * f_sample);
    FileRead("pre1_out.txt",in);
    
    double *out = (double *)malloc(sizeof(double) * f_sample);
    double A_c=1.0,phi_c;
    phi_c = -1*M_PI/2;
    _de_BPSK(out,A_c,phi_c,in);
    FileWrite("pre2_out.txt",out,f_sample);
    return 0;
}