#include <stdio.h>
#define _USE_MATH_DEFINES //M_PIを有効にする
#include <math.h>
#include <stdlib.h>
#define DATASIZE 11025
#define ALPHA 0.95

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
int main(){
    double whitenoise[DATASIZE];
    double color[DATASIZE];
    for(int i=0;i<DATASIZE;i++)whitenoise[i] = 8000*_whitenoise();
    for(int i=0;i<DATASIZE;i++)color[i] = 2000*_colored();
    FileWrite("whiteNoise.txt",whitenoise,DATASIZE);
    FileWrite("color.txt",color,DATASIZE);
    return 0;
}

