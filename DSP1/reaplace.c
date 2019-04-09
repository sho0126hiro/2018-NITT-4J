#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int DATASIZE;
int RANGE;

// \t���O�̃f�[�^�����𒊏o����
void tsvColumn1(char *str){
    if(str == NULL) {
        printf("[%s] Error (str��NULL�ł�) ",__func__);
        exit(1);
    }
    for(int i=strlen(str);i>0;i--){
        if(str[i] == '\t'){
            str[i] = '\0';
            return;
        }
    }
}

//file�ǂݍ���
// Tab�ŕ������Ă��鎞�̈��ڂ�z��Ɋi�[����B
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


// ����ւ�
// arg�z�����ёւ��Aret�Ɋi�[����
void Replace(int *ret,int *arg,int range){
    int i;
    for(i=0;i<RANGE;i++)ret[i]=arg[DATASIZE-RANGE+i];
    for(i=RANGE;i<2*RANGE;i++)ret[i]=arg[i-RANGE];
}

int main(){
    printf("�f�[�^�T�C�Y����͂��Ă������� >> ");
    scanf("%d",&DATASIZE);
    printf("����ւ�����I�����Ă��������B >> ");
    scanf("%d",&RANGE);
    if(DATASIZE/2<=RANGE){
        printf("datasize��range�̒l���Ԉ���Ă���\��������܂��B\n");
        return 0;
    }
    double *input,*output;
    char infname[512];
    char outfname[512];
    input  = (double *)malloc(sizeof(double) * DATASIZE);
    output = (double *)malloc(sizeof(double) * 2*RANGE);
    printf("���ёւ��Ώۂ̃t�@�C��������͂��Ă��������B >> ");
    scanf("%s",infname);
    FileRead(infname,input);
    printf("���ёւ��f�[�^�̏o�̓t�@�C��������͂��Ă��������B >> ");
    FileRead(infname,input);
    scanf("%s",outfname);
    Replace(output,input,RANGE);
    FileWrite_complex(outfname,output,DATASIZE);
    return 0;
}