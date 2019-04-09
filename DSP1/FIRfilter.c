#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int DATASIZE;

//file�ǂݍ���
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

// file��������
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

// �g���q���폜����
void deleteExtension(char *str){
    if(str == NULL) {
        printf("[%s] Error (str��NULL�ł�) ",__func__);
        exit(1);
    }
    for(int i=strlen(str);i>0;i--){
        if(str[i] == '.'){
            str[i] = '\0';
            return;
        }
    }
}

//��{�̃x�N�g���Ɨv�f������͂��ē��ς��o��
double InnerProduct(double a[],double b[],int N){
	double c=0;
	double sum=0;
	for(int i=0;i<N;i++){
		c=a[i]*b[i];
		sum=sum+c;
	}
	return sum;
}

// FIR�t�B���^
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
    printf("�f�[�^�T�C�Y����͂��Ă������� >> ");
    scanf("%d",&DATASIZE);
    double *h,*x,*y;
    h = (double *)malloc(sizeof(double) * DATASIZE);
    x = (double *)malloc(sizeof(double) * DATASIZE);
    y = (double *)malloc(sizeof(double) * (DATASIZE*2-1));
    
    char hfname[512];
    char xfname[512];
    // char xfname[512] = "ara11_s.txt";
    char yfname[512];

    printf("�t�B���^�W��(h)��ǂݍ��ރt�@�C��������͂��Ă������� >> ");
    scanf("%s",hfname);    
    FileRead(hfname,h);
    
    
    printf("���͐M��(x)��ǂݍ��ރt�@�C��������͂��ĉ������B>> ");
    scanf("%s",xfname);
    
    FileRead(xfname,x);
    // for(int i=0;i<DATASIZE;i++)printf("x[%d] %lf\n",i,x[i]);
    FIR_filter(h,x,y);

    
    printf("�o�͐M��(y)�������o���t�@�C��������͂��Ă��������B>> ");
    scanf("%s",yfname);    
    
    deleteExtension(xfname); // ���̓t�@�C����
    deleteExtension(hfname); // �t�B���^�t�@�C����
    //sprintf(yfname,"%s___%s.txt",xfname,hfname);
    FileWrite(yfname,y,(DATASIZE*2-1));
    free(y);
    free(h);
    free(x);
    return 0;
}