#include <stdio.h>
#define _USE_MATH_DEFINES //M_PI��L���ɂ���
#include <math.h>

#define DATASIZE 4//sampling data size

//�\���̐錾
typedef struct{
    double re; //real number
    double im; //imagination number   
}complex;

//file�ǂݍ���
void FileRead(char *filename,double data[]){
	FILE *fp;
    fp = fopen(filename,"r");
	if(fp==NULL){
		printf("can't open a file\n");
		exit(1);
		return;
	}
	int i=0;
	for(i=0;i<DATASIZE;i++)fscanf(fp,"%lf",&data[i]);
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

// re[],im[] >> complex[]
complex setComplex(double x,double y){
    complex result;
    result.re = x;
    result.im = y;
    return result;
}
// complex[] >> re[] , im[]
void complex_reim(complex z[DATASIZE] ,double re[DATASIZE],double im[DATASIZE]){
    for(int i=0;i<DATASIZE;i++){
        re[i] = z[i].re;
        im[i] = z[i].im;
    }
}

// --------------------------------------------------------//
// ���f���̘a(x + y)��Ԃ�
complex ComplexAddition(complex x,complex y){
    complex result;
    result.re = x.re + y.re;
    result.im = x.im + y.im;
    return result;
}
// ���f���̍�(x - y)��Ԃ�
complex ComplexSubstraction(complex x,complex y){
    complex result;
    result.re = x.re - y.re;
    result.im = x.im - y.im;
    return result;
}
// ���f���̐�(x * y)��Ԃ�
complex ComplexMultiplication(complex x,complex y){
    complex result;
    result.re = x.re * y.re - x.im * y.im;
    result.im = x.re * y.im + x.im * y.re;
    return result;
}
// ���f���̏�(x / y)��Ԃ�
complex ComplexDivision(complex x,complex y){
    complex result;
    result.re = (x.re * y.re + x.im * y.im)/(pow(y.re,2.0)+(pow(y.im,2.0)));
    result.im = (x.im * y.re - x.re * y.im)/(pow(y.re,2.0)+(pow(y.im,2.0)));
    return result;
}
// ���𕡑f����Ԃ�
complex ComplexConjugate(complex x){
    complex result;
    result.re =      x.re;
    result.im = -1 * x.im;
    return result;
}
// ���f���̕\��
void DisplayComplex(complex X[DATASIZE]){
    int i;
    for(i=0;i<DATASIZE;i++)printf("X[%d] = %lf + j(%lf)\n",i,X[i].re,X[i].im);
}
// --------------------------------------------------------//

// N�̉�]�qW���v�Z����
void Rotor(complex w[],int N){
    for(int i=0;i<N/2;i++){
            w[i].re =      cos((2*M_PI/DATASIZE) * i);
            w[i].im = -1 * sin((2*M_PI/DATASIZE) * i);
    }
}
void DisplayRotor(complex X[]){
    int i;
    for(i=0;i<DATASIZE/2;i++)printf("X[%d] = %lf + j(%lf)\n",i,X[i].re,X[i].im);
}
// ���f���̑傫�������߂�B
// X {complex[]}�̐U���X�y�N�g����Y{double[]}�ɑ������
void Magnitude(double Y[DATASIZE],complex X[DATASIZE]){
    for(int i=0;i<DATASIZE;i++){
        Y[i]=sqrt(pow(X[i].re,2.0) + pow(X[i].im,2.0));
    }
}

// �U���X�y�N�g���̕\���p
void DisplayMagnitude(double X[]){
    int i;
    printf("|Xk|=(");
    for(i=0;i<DATASIZE-1;i++){
        printf("%lf,",X[i]);
    }
    printf("%lf)\n",X[i]);
}

// =========== �r�b�g���o�[�T���p ===================
void initDeal(int deal[DATASIZE],int N){
    for(int i=0;i<N;i++)deal[i]=i;
}

void displayDeal(int deal[DATASIZE],int N){
    for (int i=0;i<DATASIZE;i++)printf("%d\n",deal[i]);
}

// ���]���������āA���Ԃ����߂�
void BitReversal(int *deal,int N){
    int i,j,tmp,result;
    for(i=0;i<N;i++){
        result = 0;
        for(j=0;j<log2f(N);j++){
            tmp = (deal[i] >> j) & 1;
            tmp <<= (int)log2(N) - 1-j;
            result += (tmp);
        }
        deal[i] = result;
    }
}
// deal�Ɏ����ꂽ�ԍ�����result�̒��g�����ւ���
void rearrangeArray(double result[DATASIZE],int deal[DATASIZE]){
    double tmp[DATASIZE];
    int i;
    for(i=0;i<DATASIZE;i++) tmp[i] = result[deal[i]];
    for(i=0;i<DATASIZE;i++) result[i] = tmp[i];
}
// ==================================================

//FFT or IFFT
void FastFourieTransform(complex Y[DATASIZE],complex X[DATASIZE]){
    // X�� FFTorIFFT �������ʂ�Y�ɑ�������
    // x >> y (input >> output)
    int i,j,k;
    complex c_W[DATASIZE/2] = {0};
    Rotor(c_W,DATASIZE);
    // DisplayRotor(c_W);
    for(k=0;k<(int)log2(DATASIZE);k++){
        if(k==0){
            for(j=0;j<DATASIZE;j+=2){
                // in[j] in[j+1]
                Y[j] = ComplexAddition(X[j],ComplexMultiplication(c_W[0],X[j+1]));
                Y[j+1] = ComplexSubstraction(X[j],ComplexMultiplication(c_W[0],X[j+1]));
            }
        }else{
            for(j=0;j<DATASIZE;j+=(int)pow(2,k+1)){
                int d = 0; // ��]�q�z��ɗ^����ԍ�
                for(i=0;i<pow(2,k);i++,d+= DATASIZE / ((int)pow(2,k+1))){
                    if(d >= DATASIZE/2) d = 0;
                    // in[j+i] in[j+i+2^k]
                    complex tmp[2];
                    tmp[0] = ComplexAddition(Y[j+i],ComplexMultiplication(c_W[d],Y[j+i+(int)pow(2,k)]));
                    tmp[1] = ComplexSubstraction(Y[j+i],ComplexMultiplication(c_W[d],Y[j+i+(int)pow(2,k)]));
                    Y[j+i]  = tmp[0];
                    Y[j+i+(int)pow(2,k)]  = tmp[1];
                }
            }
        }
    }
}
int main(){
    double input[DATASIZE] = {3,3,-1,-1}; // ���̓f�[�^
    complex c_input[DATASIZE];    // ���̓f�[�^ >> ���f��
    complex c_output[DATASIZE];   // �o�̓f�[�^ >> ���f��
    double amp[DATASIZE];         // �U���X�y�N�g���i�[�p
    // fileRead >> input{double} >> c_input{complex}
    // FileRead("in.txt",input);
    // �r�b�g���o�[�T��
    int deal[DATASIZE] = {0};     // ���я�
    initDeal(deal,DATASIZE); 
    BitReversal(deal,DATASIZE);
    rearrangeArray(input,deal);
    
    for(int i=0;i<DATASIZE;i++){
        c_input[i] = setComplex(input[i],0);
        // printf("deal = [%d] input = %lf\n",deal[i],input[i]);
    }
    
    // fft
    FastFourieTransform(c_output,c_input);
    DisplayComplex(c_output);
    // amplitude spectrum
    // Magnitude(amp,c_output);
    // DisplayMagnitude(amp);
    // FileWrite("out.txt",amp,DATASIZE);
    return 0;
}