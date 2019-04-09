#include <stdio.h>
#define DIM 196 // dimention 次元
#define CTGRY 46 // category (字種)
#define DATASIZE 180 // 読み込むデータ数

void fileRead(char *filename,int *data){
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
    for(i=0;i<DIM*DATASIZE;i++){
        fscanf(fp,"%d",data[i]);
    }
	fclose(fp);
}

void fileWrite(char *fname){

}

int main(){
    int data[DATASIZE];
    return 0;
}