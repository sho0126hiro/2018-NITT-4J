#include <stdio.h>
#define _USE_MATH_DEFINES //M_PIを有効にする
#include <math.h>
#include <string.h>
#include <stdlib.h>

int DATASIZE=500; //sampling data size

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


//方形窓 : Xに方形窓をかけたデータをYに格納する
void Rectanglar_Window(double Y[],double X[]){
    for(int n=0;n<DATASIZE;n++)Y[n]=X[n]*1;
}

//ハニング窓 : Xにハニング窓をかけたデータをYに格納する
void Hanning_Window(double Y[],double X[]){
    for(int n=0;n<DATASIZE;n++)Y[n]=X[n]*(0.5-0.5*cos((2*M_PI*n)/DATASIZE));
}

//ハミング窓 : Xにハミング窓をかけたデータをYに格納する
void Hamming_Window(double Y[],double X[]){
    for(int n=0;n<DATASIZE;n++)Y[n]=X[n]*(0.54-0.46*cos((2*M_PI*n)/DATASIZE));
}

//ブラックマン窓 : Xにブラックマン窓をかけたデータをYに格納する
void Blackman_Window(double Y[],double X[]){
    for(int n=0;n<DATASIZE;n++)Y[n]=X[n]*(0.42-0.5*cos((2*M_PI*n)/DATASIZE)+0.08*cos((4*M_PI*n)/DATASIZE));
}

void Flattop_Window(double Y[],double X[]){
    for(int n=0;n<DATASIZE;n++)Y[n]=X[n] * (1-1.93*cos((2*M_PI*n)/DATASIZE)+1.29*cos((4*M_PI*n)/DATASIZE)-0.388*cos((6*M_PI)/DATASIZE)+0.032*cos((8*M_PI*n)/DATASIZE));
}

int main(){
    char infname[512];
    char outfname[512];
    printf("データサイズを入力してください >> ");
    scanf("%d",&DATASIZE);
    double *input,*output;
    input  = (double *)malloc(sizeof(double) * DATASIZE);
    output = (double *)malloc(sizeof(double) * DATASIZE);
    printf("対象のファイル名を入力してください。 >> ");
    scanf("%s",infname);
    FileRead(infname,input);
    //Window Function
    printf("w");
    Hanning_Window(output,input);
    sprintf(outfname,"hanning_%s",infname);
    FileWrite(outfname,output,DATASIZE);
    Hamming_Window(output,input);
    sprintf(outfname,"hamming_%s",infname);
    FileWrite(outfname,output,DATASIZE);
    Blackman_Window(output,input);
    sprintf(outfname,"blackman_%s",infname);
    FileWrite(outfname,output,DATASIZE);
    Flattop_Window(output,input);
    sprintf(outfname,"flattop_%s",infname);
    FileWrite(outfname,output,DATASIZE);
    printf("w");
    return 0;
}