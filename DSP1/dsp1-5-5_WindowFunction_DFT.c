#include <stdio.h>
#define _USE_MATH_DEFINES //M_PI��L���ɂ���
#include <math.h>

#define DATASIZE 500 //sampling data size

//�\���̐錾
typedef struct{
    double re;//real number
    double im;//imagination number   
}complex;

//file�ǂݍ���
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
//complex >> double >> File Write : complex X[] >> double re[],im[]
void FwriteArrayConvert(complex X[],double re[], double im[]){
    for(int i=0;i<DATASIZE;i++){
        re[i]=X[i].re;
        im[i]=X[i].im;
    }
}
//File��������
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

//complex������
void init_complex(complex X[DATASIZE] ,double re[DATASIZE], double im[DATASIZE]){
    int i;
    for(i=0;i<DATASIZE;i++){
        X[i].re=re[i];
        X[i].im=im[i];
    }
}

//DFT or IDFT
int DiscreteFourieTransform(complex Y[DATASIZE],complex X[DATASIZE],int mode){
    //mode=1 : DFT mode=-1 : IDFT
    //X��DFTorIDFT�������ʂ�Y�ɑ�������
    int a,b,n,k;
    if(mode==1){
        a=1;
        b=1;
    }else if (mode==-1){
        a=-1;
        b=DATASIZE;
    }else{
        printf("error");
        return -1;
    }
    complex Z[DATASIZE];
    complex Y_sum;
    //DFT or IDFT
    for(k=0;k<DATASIZE;k++){
        Y_sum.re = 0;
        Y_sum.im = 0;
        for(n=0;n<DATASIZE;n++){
            Z[n].re = X[n].re * cos((2*M_PI*n*k)/DATASIZE) + a*X[n].im * sin((2*M_PI*n*k)/DATASIZE);
            Z[n].im = X[n].im * cos((2*M_PI*n*k)/DATASIZE) - a*X[n].re * sin((2*M_PI*n*k)/DATASIZE);
            Y_sum.re += Z[n].re;
            Y_sum.im += Z[n].im;
        }
        Y[k].re=Y_sum.re / b;
        Y[k].im=Y_sum.im / b;
    }
    return 0;
}

//���f���̑傫�������߂�B
void Magnitude(double Y[DATASIZE],complex X[DATASIZE]){
    //���f���ŗ^������X�̐U���X�y�N�g���i���f���̑傫���j��Y�Ɋi�[����
    for(int i=0;i<DATASIZE;i++){
        Y[i]=sqrt(pow(X[i].re,2.0) + pow(X[i].im,2.0));
    }
}

//���f���̕\��
void DisplayComplex(complex X[DATASIZE]){
    int i;
    for(i=0;i<DATASIZE;i++)printf("X[%d] = %lf + j(%lf)\n",i,X[i].re,X[i].im);
}

//�U���X�y�N�g���̕\��
void DisplayMagnitude(double X[DATASIZE]){
    int i;
    printf("|Xk|=(");
    for(i=0;i<DATASIZE-1;i++)printf("%lf,",X[i]);
    printf("%lf)\n",X[i]);
}

//���`�� : X�ɕ��`�����������f�[�^��Y�Ɋi�[����
void Rectanglar_Window(double Y[],double X[]){
    for(int n=0;n<DATASIZE;n++)Y[n]=X[n]*1;
}

//�n�j���O�� : X�Ƀn�j���O�����������f�[�^��Y�Ɋi�[����
void Hanning_Window(double Y[],double X[]){
    for(int n=0;n<DATASIZE;n++)Y[n]=X[n]*(0.5-0.5*cos((2*M_PI*n)/DATASIZE));
}

//�n�~���O�� : X�Ƀn�~���O�����������f�[�^��Y�Ɋi�[����
void Hamming_Window(double Y[],double X[]){
    for(int n=0;n<DATASIZE;n++)Y[n]=X[n]*(0.54-0.46*cos((2*M_PI*n)/DATASIZE));
}

//�u���b�N�}���� : X�Ƀu���b�N�}�������������f�[�^��Y�Ɋi�[����
void Blackman_Window(double Y[],double X[]){
    for(int n=0;n<DATASIZE;n++)Y[n]=X[n]*(0.42-0.5*cos((2*M_PI*n)/DATASIZE)+0.08*cos((4*M_PI*n)/DATASIZE));
}

void Flattop_Window(double Y[],double X[]){
    for(int n=0;n<DATASIZE;n++)Y[n]=X[n] * (1-1.93*cos((2*M_PI*n)/DATASIZE)+1.29*cos((4*M_PI*n)/DATASIZE)-0.388*cos((6*M_PI)/DATASIZE)+0.032*cos((8*M_PI*n)/DATASIZE));
}

int main(){
    //����
    double Xn_re[DATASIZE];             // ���f�[�^�̎����i�[�p
    double Xn_re_Flattop[DATASIZE]; //flattop�������������f�[�^�����i�[�p
    //����
    double Xn_im[DATASIZE]={0};         // ���f�[�^�����i�[�p
    //���f��(���f�[�^)
    complex Xn[DATASIZE];               // ���f�[�^�i�[�p
    complex Xn_Flattop[DATASIZE];    // �t���b�g�g�b�v�����������f�[�^�i�[�p
    //DFT���ʊi�[�p
    complex Xk_Flattop[DATASIZE];
    //�U���X�y�N�g���i�[�p
    double Xk_Flattop_Mag[DATASIZE];
    int r=0;
    //File read >> init
    FileRead("sampledata.txt",Xn_re);
    //Window Function
    Flattop_Window(Xn_re_Flattop,Xn_re);
    //sample data >> Winddow Function >> file Write
    FileWrite("sampledata_Flattop.txt",Xn_re_Flattop,DATASIZE);
    //init complex
    init_complex(Xn_Flattop,Xn_re_Flattop,Xn_im);
    //DFT
    r = DiscreteFourieTransform(Xk_Flattop,Xn_Flattop,1);
    if(r==-1)return 0;
    //File Write
    double Xk_re_w[DATASIZE]; //�t�@�C���������ݗp�z��
    double Xk_im_w[DATASIZE]; //�t�@�C���������ݗp�z��
    FwriteArrayConvert(Xk_Flattop,Xk_re_w,Xk_im_w);
    FileWrite("sampledata_Flattop_DFT_re.txt",Xk_re_w,DATASIZE);
    FileWrite("sampledata_Flattop_DFT_im.txt",Xk_im_w,DATASIZE);
    //Amplitude Spectrum
    Magnitude(Xk_Flattop_Mag,Xk_Flattop);
    FileWrite("sampledata_Rectanglar_AmpSpectrum.txt",Xk_Flattop_Mag,DATASIZE);
    return 0;
}