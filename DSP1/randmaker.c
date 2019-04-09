#include <stdio.h>
#include <math.h>
#include <direct.h>
#include <stdlib.h>
#include <time.h>

int POW_SIZE_START;
int POW_SIZE_END;
int RAND_RANGE_MAX = 50000;
int RAND_RANGE_MIN = 0;
char OUT_DIR[512];

//File書き込み
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

/* MIN ~ MAXの中の数字をランダムで返す*/
int getRand(){
    return RAND_RANGE_MIN + (int)(rand()*(RAND_RANGE_MAX-RAND_RANGE_MIN+1.0)/(1.0+RAND_MAX));
}

/*2の累乗のランダムな数字をファイル出力する*/
/*filepath : ./pow/2^n.txt*/
void pow2randMaker(int size){
    double *out;
    out = (double *)malloc(sizeof(double)*size);
    for(int i=0;i<size;i++){
        out[i] = (double)(getRand() * 0.0001);
    }
    char fname[512];
    sprintf(fname,"%s/2^%d.txt",OUT_DIR,(int)log2(size));
    FileWrite(fname,out,size);
    free(out);
}

int main(){
    //rand init
    srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
    printf("ランダムなデータをファイル出力します。\n");
    printf("出力先のディレクトリ名を記入してください >>");
    scanf("%s",OUT_DIR);
    if(_mkdir(OUT_DIR)!=0)printf("error!\n");
    printf("データサイズ：2の累乗:2^x~2^yまで\n");       
    printf("xとyを入力してください。(x y) >> ");
    scanf("%d %d",&POW_SIZE_START,&POW_SIZE_END);
    // printf("ランダムなデータの範囲を入力してください。\n");
    // printf("最小値x , 最大値y : (x y) >> ");
    // scanf("%d %d",&RAND_RANGE_MIN,&RAND_RANGE_MAX);

    // rand
    for(int i=POW_SIZE_START;i<=POW_SIZE_END;i++){
        pow2randMaker((int)pow(2,i));
        //printf("%lf\n",pow(2,i));
    }
    return 0;
}