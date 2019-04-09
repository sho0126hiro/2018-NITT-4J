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

//File��������
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

/* MIN ~ MAX�̒��̐����������_���ŕԂ�*/
int getRand(){
    return RAND_RANGE_MIN + (int)(rand()*(RAND_RANGE_MAX-RAND_RANGE_MIN+1.0)/(1.0+RAND_MAX));
}

/*2�̗ݏ�̃����_���Ȑ������t�@�C���o�͂���*/
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
    srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
    printf("�����_���ȃf�[�^���t�@�C���o�͂��܂��B\n");
    printf("�o�͐�̃f�B���N�g�������L�����Ă������� >>");
    scanf("%s",OUT_DIR);
    if(_mkdir(OUT_DIR)!=0)printf("error!\n");
    printf("�f�[�^�T�C�Y�F2�̗ݏ�:2^x~2^y�܂�\n");       
    printf("x��y����͂��Ă��������B(x y) >> ");
    scanf("%d %d",&POW_SIZE_START,&POW_SIZE_END);
    // printf("�����_���ȃf�[�^�͈̔͂���͂��Ă��������B\n");
    // printf("�ŏ��lx , �ő�ly : (x y) >> ");
    // scanf("%d %d",&RAND_RANGE_MIN,&RAND_RANGE_MAX);

    // rand
    for(int i=POW_SIZE_START;i<=POW_SIZE_END;i++){
        pow2randMaker((int)pow(2,i));
        //printf("%lf\n",pow(2,i));
    }
    return 0;
}