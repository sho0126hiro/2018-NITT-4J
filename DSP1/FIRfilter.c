#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int DATASIZE;

//file読み込み
void FileRead(char *filename,double data[]){
	FILE *fp;
    fp = fopen(filename,"r");
	if(fp==NULL){
		printf("can't open a file\n");
		exit(1);
		return;
	}
	for(int i=0;i<DATASIZE;i++)fscanf(fp,"%lf",&data[i]);
	fclose(fp);
}

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

// 拡張子を削除する
void deleteExtension(char *str){
    if(str == NULL) {
        printf("[%s] Error (strがNULLです) ",__func__);
        exit(1);
    }
    for(int i=strlen(str);i>0;i--){
        if(str[i] == '.'){
            str[i] = '\0';
            return;
        }
    }
}

//二本のベクトルと要素数を入力して内積を出力
double InnerProduct(double a[],double b[],int N){
	double c=0;
	double sum=0;
	for(int i=0;i<N;i++){
		c=a[i]*b[i];
		sum=sum+c;
	}
	return sum;
}

// FIRフィルタ
void FIR_filter(double *h,double *x,double *y){
    double *x_tmp = (double *)malloc(sizeof(double) * (DATASIZE*2-1));
    for(int i=0;i<DATASIZE*2-1;i++)x_tmp[i] = 0;
    for(int i=0;i<DATASIZE;i++){
        // shift
        for(int j=DATASIZE-1;j>0;j--){
            x_tmp[j] = x_tmp[j-1];
        }
        x_tmp[0] = x[i];
        printf("x : %lf\n",x[i]);
        y[i] = InnerProduct(x_tmp,h,DATASIZE);
        printf("y : %lf\n",y[i]);
    }
    for(int i=0;i<DATASIZE-1;i++){
        // shift
        for(int j=DATASIZE-1;j>0;j--){
            x_tmp[j] = x_tmp[j-1];
        }
        x_tmp[0] = 0;
         y[DATASIZE+i] = InnerProduct(x_tmp,h,DATASIZE);
    }
    free(x_tmp);
}
int main(){
    printf("データサイズを入力してください >> ");
    scanf("%d",&DATASIZE);
    double *h,*x,*y;
    h = (double *)malloc(sizeof(double) * DATASIZE);
    x = (double *)malloc(sizeof(double) * DATASIZE);
    y = (double *)malloc(sizeof(double) * (DATASIZE*2-1));
    
    char hfname[512];
    char xfname[512];
    // char xfname[512] = "ara11_s.txt";
    char yfname[512];

    printf("フィルタ係数(h)を読み込むファイル名を入力してください >> ");
    scanf("%s",hfname);    
    FileRead(hfname,h);
    
    
    printf("入力信号(x)を読み込むファイル名を入力して下さい。>> ");
    scanf("%s",xfname);
    
    FileRead(xfname,x);
    // for(int i=0;i<DATASIZE;i++)printf("x[%d] %lf\n",i,x[i]);
    FIR_filter(h,x,y);

    
    printf("出力信号(y)を書き出すファイル名を入力してください。>> ");
    scanf("%s",yfname);    
    
    deleteExtension(xfname); // 入力ファイル名
    deleteExtension(hfname); // フィルタファイル名
    //sprintf(yfname,"%s___%s.txt",xfname,hfname);
    FileWrite(yfname,y,(DATASIZE*2-1));
    free(y);
    free(h);
    free(x);
    return 0;
}