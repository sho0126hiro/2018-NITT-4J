#include <stdio.h>
#define _USE_MATH_DEFINES //M_PIを有効にする
#include <math.h>
#include <stdlib.h>

#define B_SIZE 6
int BITRATE= 200; // bitrate (bps)
double clock = 5; // クロック周波数(ms)
double f_c = 200; //(ms)
int resolution = 200; // 搬送波の1周期を200この点に分解する
double f_sample = 40000; // サンプリング周波数：40kHz >> T=25μsec(1/40000)


void _BPSK(double *out, double A_c,double phi_c,double *bt){
    int i,j;
    double tmp;
    for(i=0;i<B_SIZE;i++){
        if(bt[i]){
            for(j=0;j<resolution;j++){
                tmp = 2*M_PI*f_c*((resolution*i+j)/f_sample)+phi_c+M_PI;
                out[resolution*i+j] = A_c*cos(tmp);
            }
        }else{
            for(j=0;j<resolution;j++){
                out[resolution*i+j] = A_c*cos(2*M_PI*f_c*((resolution*i+j)/f_sample)+phi_c);
            }
        }
    }
    //for(int i=0;i<200;i++)printf("out:%f",out[resolution*i+j]);
}

//File書き込み
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
    double bt[B_SIZE]={1.0,0.0,1.0,1.0,0.0,1.0}; //1 or 0
    double *out = (double *)malloc(sizeof(double) * f_sample);
    double A_c=1.0,phi_c;
    phi_c = -1*M_PI/2;
    _BPSK(out,A_c,phi_c,bt);
    FileWrite("pre1_out.txt",out,f_sample);
    return 0;
}