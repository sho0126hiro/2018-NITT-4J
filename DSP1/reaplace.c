#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int DATASIZE;
int RANGE;

// \tより前のデータだけを抽出する
void tsvColumn1(char *str){
    if(str == NULL) {
        printf("[%s] Error (strがNULLです) ",__func__);
        exit(1);
    }
    for(int i=strlen(str);i>0;i--){
        if(str[i] == '\t'){
            str[i] = '\0';
            return;
        }
    }
}

//file読み込み
// Tabで分けられている時の一列目を配列に格納する。
void FileRead_re(char *filename,double data[]){
	FILE *fp;
	char *tmp;
	tmp  = (char *)malloc(sizeof(char) * DATASIZE);
	//printf("| function : %s | filename:%s |\n",__FUNCTION__,filename);a
	fp=fopen(filename,"r");
	if(fp==NULL){
		printf("can't open a file\n");
		//exit(1);
		return;
	}
	int i=0;
	//while(fscanf(fp,"%lf",&data[i])!= EOF)i++;
	for(i=0;i<DATASIZE;i++){
        fscanf(fp,"%s",&tmp[i]);
        data[i] = tsvColumn1(tmp[i]); 
    }
	fclose(fp);
}


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


// 入れ替え
// arg配列を並び替え、retに格納する
void Replace(int *ret,int *arg,int range){
    int i;
    for(i=0;i<RANGE;i++)ret[i]=arg[DATASIZE-RANGE+i];
    for(i=RANGE;i<2*RANGE;i++)ret[i]=arg[i-RANGE];
}

int main(){
    printf("データサイズを入力してください >> ");
    scanf("%d",&DATASIZE);
    printf("入れ替え個数を選択してください。 >> ");
    scanf("%d",&RANGE);
    if(DATASIZE/2<=RANGE){
        printf("datasizeとrangeの値が間違っている可能性があります。\n");
        return 0;
    }
    double *input,*output;
    char infname[512];
    char outfname[512];
    input  = (double *)malloc(sizeof(double) * DATASIZE);
    output = (double *)malloc(sizeof(double) * 2*RANGE);
    printf("並び替え対象のファイル名を入力してください。 >> ");
    scanf("%s",infname);
    FileRead(infname,input);
    printf("並び替えデータの出力ファイル名を入力してください。 >> ");
    FileRead(infname,input);
    scanf("%s",outfname);
    Replace(output,input,RANGE);
    FileWrite_complex(outfname,output,DATASIZE);
    return 0;
}