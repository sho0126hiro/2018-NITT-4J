/*
���2�̓���
	�T���v������ω������āC���ꂼ��50��C��1�̉𓚂��v������v���O������ʂɍ쐬�����D
	�����ŁC�T���v������ω��������Ƃ��̂΂���̒l�i���悻�j�̌��ʂ͈ȉ��̒ʂ�ł���D
	�΂���̒l�͏o�͂��ꂽ�ő�l - �ŏ��l �Ƃ��Ă���D
	
	 �T���v����  | �΂��(max - min)
	   5��       |       0.01200      
	   10��      |       0.02000
	   50��      |       0.00400
	   100��     |       0.00300
	   200��     |       0.00200
	   500��     |       0.00110
	   800��     |       0.00080
	   1000��    |       0.00080
	   2000��    |       0.00070
	   3000��    |       0.00030
	   5000��    |       0.00050
	   8000��    |       0.00030
	   1��       |       0.00028
	
	�i3000���T���v���ȏ�̏ꍇ�C�v���O�����̎��s���x�̖��Ŏ��s�񐔂�50�񂩂�30��ɗ��Ƃ��Ă���j
	
	�\���݂�ƁC�����_���ŗ^���Ă��邽�߁C�u�f�[�^���������Ă��΂�����L����v���Ƃ�����
	�Ƃ������Ƃ����������D
	
	�΂���������悻0.001�ł���Ƃ��C�\���Ȑ��x�Ƃ����邾�낤�ƍl�����D
	����ɑΉ�����T���v��������ԒႢ���̂�500���ł��邪�C���x���\���Ȓl�ɂ��邽�߂ɁC
	1000���T���v���Ƃ����D
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define SAMPLE_SIZE 10000000
// - �O���[�o���ϐ��錾�i�ϐ��� : g_ )�@-----------------------------------------------------
//-------------�������ʊi�[�p�\����-------------�@
typedef struct{
    int A;
    int B;
    int C;
    int D;
}RandomResult_t; // (�e�v�f��0,1��������Ȃ��B)
//-------------�������ʊi�[�p-------------
RandomResult_t g_result[SAMPLE_SIZE];

//-------------��`���ꂽ�m���f�[�^-------------
double g_probability[4][8]={
    {0.20,0,80},           // A=0,1;
    {0.85,0.15},           // B=0,1;
    {0.10,0.75,0.40,0.95,  // C=0 | A,B = 0,0 0,1 1,0 1,1
     0.90,0.25,0.70,0.05}, // C=1 | A,B = 0,0 0,1 1,0 1,1
    {0.95,0.80,            // D=0 | C = 0,1
     0.05,0.20}            // D=1 | C = 0,1
};

// - �\���̐錾 ���߂��������t�m��������
/* ��`���@
P(A=0 | B=0)�@    .probability="A0" , conditionSize=1,  .condition="B0" 
P(A=0 | B=0,C=1)�@.probability="A0" , conditionSize=2,  .condition="B0C1"
                        ���߂����m��,        �����̐�,  �����i�����ł��j
*/
typedef struct{
    char probability[2];
    int  conditionSize;
    char condition[];
}ConditionalProbability_t;
//���߂��������t���m���̒�`
ConditionalProbability_t g_calcData_1={"D1",1,"B1"};
ConditionalProbability_t g_calcData_2={"C0",2,"A0D1"};
ConditionalProbability_t g_calcData_3={"D0",1,"A1"};

//���݂̖��ԍ�
int g_Qnum=0;
// -----------------------------------------------------------------------------------------

//�i�ꌅ�̂݁j������̐�����int�^�ɕϊ�����}�N��
#define ConvertInt(num) ((int)num - '0')
/*  ���̕��������Ӗ��ɂȂ�
    printf("%d\n",(int)g_calcData.condition[1]-'0');
    printf("%d\n",ConvertInt(g_calcData.condition[1]));*/

// - �֐��錾 ------------------------------------------------------------------------------
void InitResult();// - �������ʊi�[�p�z��̏������֐�
void CalcResult();// - ���������@>>�@�i�[
int  GetRand(double p_zero);
int  Check(int i);
double Answer();
void DisplayResult();
// - main ------------------------------------------------------------------------------
int main(){
    //�����o�͌��̏�����
    srand((unsigned)time(NULL));
    //���1
    g_Qnum=1;
    InitResult(); //�������ʊi�[�p�z������ׂā\1�ɏ�����
    CalcResult(); //���������@>>�@0/1��g_result�Ɋi�[
    //DisplayResult();
    //�����܂łŗ����ɑΉ������f�[�^�͑S�Ă�����Ă���
    //��������
    double p1;
    p1 = Answer();

    //���2
    g_Qnum=2;
    InitResult(); //�������ʊi�[�p�z������ׂā\1�ɏ�����
    CalcResult(); //���������@>>�@0/1��g_result�Ɋi�[
    //DisplayResult();
    //�����܂łŗ����ɑΉ������f�[�^�͑S�Ă�����Ă���
    //��������
    double p2;
    p2 = Answer(); 

    //���3
    g_Qnum=3;
    InitResult(); //�������ʊi�[�p�z������ׂā\1�ɏ�����
    CalcResult(); //���������@>>�@0/1��g_result�Ɋi�[
    //DisplayResult();
    //�����܂łŗ����ɑΉ������f�[�^�͑S�Ă�����Ă���
    //��������

    double p3;
    p3 = Answer();
    printf("���̓���\n");
    printf("1: %1.4lf\n",p1);
    printf("2: %1.4lf\n",p2);
    printf("3: %1.4lf\n",p3);

    return 0;
}

// - �������ʊi�[�p�z��̏������֐� -----------------------------------------------------
void InitResult(){
    //�������ʊi�[�p�z������ׂā\1�ɏ�����
    for(int i=0;i<SAMPLE_SIZE;i++){
        g_result[i].A = -1;
        g_result[i].B = -1;
        g_result[i].C = -1;
        g_result[i].D = -1;
    }
}

// - ���������@>>�@�i�[ ---------------------------------------------------------------------
void CalcResult(){
    int i;
    
    for(i=0;i<SAMPLE_SIZE;i++){
        // A
        g_result[i].A = GetRand(g_probability[0][0]);
        if(Check(i)) continue;
        // B
        g_result[i].B = GetRand(g_probability[1][0]);
        if(Check(i)) continue;
        // C
        if(g_result[i].A == 0){
            if(g_result[i].B == 0) g_result[i].C = GetRand(g_probability[2][0]); // A-B : 0-0
            else                   g_result[i].C = GetRand(g_probability[2][1]); // A-B : 0-1
        }else{
            if(g_result[i].B == 0) g_result[i].C = GetRand(g_probability[2][2]); // A-B : 1-0
            else                   g_result[i].C = GetRand(g_probability[2][3]); // A-B : 1-1
        }
        if(Check(i)) continue;
        // D
        if(g_result[i].C == 0) g_result[i].D = GetRand(g_probability[3][0]); // C : 0
        else                   g_result[i].D = GetRand(g_probability[3][1]); // C : 1
    }
}

//p_zero�̊m����0��Ԃ��B����ȊO��1
int GetRand(double p_zero){
    double result;
    // �������o�͂��A�����̍ő�l�Ŋ��邱�Ƃ�0~1�̏������o�͂���
    result = (double)rand()/RAND_MAX; 
    //printf("p_zero : %lf result : %lf",p_zero,result);
    if(result < p_zero) {
        //printf(" 0 ");
        return 0;
    }else{
        //printf(" 1 ");
        return 1;
    }
}

// �i�[���ꂽ�f�[�^�������ɍ����Ă��Ȃ��ꍇreturn 1��Ԃ�
int Check(int i){
    //��x�ɑS�Ă̖����������Ƃ����Ƃ��ɂ��܂��ϐ��̎󂯓n�����ł��Ȃ��������߁A
    //switch/case�ł��艟�����B
    //printf("[%d]",g_Qnum);
    switch(g_Qnum){
        case 1:
            for(int j=0;j<g_calcData_1.conditionSize;j++){
                //printf("%c",g_calcData_1.condition[0]);
                //printf("(%d)",(int)g_calcData_1.condition[0]);
                switch((int)g_calcData_1.condition[2*j]){
                    // result.? �������O�̒l�Ȃ�return 0 (�֐��ɖ߂��Ă��炻�̌�̌v�Z�͏�������Ȃ��Ȃ�)
                    case 65: // A
                        if(!(g_result[i].A == ConvertInt(g_calcData_1.condition[2*j+1]))){
                           if(g_result[i].A == -1)return 0;//�������A-1�������Ă����瑱����
                            else return 1; 
                        }
                        break;
                    case 66: // B
                        //printf("g_result[i].B : %d / sahen : %c",g_result[i].B,g_calcData_1.condition[2*j+1]);
                        if(!(g_result[i].B == ConvertInt(g_calcData_1.condition[2*j+1]))){//�����O
                            if(g_result[i].B == -1)return 0;//�������A-1�������Ă����瑱����
                            else return 1;
                        } 
                        break;
                    case 67: // C
                        if(!(g_result[i].C == ConvertInt(g_calcData_1.condition[2*j+1]))){
                            if(g_result[i].C == -1)return 0;//�������A-1�������Ă����瑱����
                            else return 1;
                        }           
                        break;
                    case 68: // D
                        if(!(g_result[i].D == ConvertInt(g_calcData_1.condition[2*j+1]))){
                            if(g_result[i].D == -1)return 0;//�������A-1�������Ă����瑱����
                            else return 1;
                        }
                        break;
                    default :
                        printf("%d [error] Condition",__LINE__);
                }
            }
            break;
        case 2:
            for(int j=0;j<g_calcData_2.conditionSize;j++){
                //printf("%c",g_calcData_1.condition[0]);
                //printf("(%d)",(int)g_calcData_1.condition[0]);
                switch((int)g_calcData_2.condition[2*j]){
                    // result.? �������O�̒l�Ȃ�return 0 (�֐��ɖ߂��Ă��炻�̌�̌v�Z�͏�������Ȃ��Ȃ�)
                    case 65: // A
                        if(!(g_result[i].A == ConvertInt(g_calcData_2.condition[2*j+1]))){
                           if(g_result[i].A == -1)return 0;//�������A-1�������Ă����瑱����
                            else return 1; 
                        }
                        break;
                    case 66: // B
                        //printf("g_result[i].B : %d / sahen : %c",g_result[i].B,g_calcData_1.condition[2*j+1]);
                        if(!(g_result[i].B == ConvertInt(g_calcData_2.condition[2*j+1]))){//�����O
                            if(g_result[i].B == -1)return 0;//�������A-1�������Ă����瑱����
                            else return 1;
                        } 
                        break;
                    case 67: // C
                        if(!(g_result[i].C == ConvertInt(g_calcData_2.condition[2*j+1]))){
                            if(g_result[i].C == -1)return 0;//�������A-1�������Ă����瑱����
                            else return 1;
                        }           
                        break;
                    case 68: // D
                        if(!(g_result[i].D == ConvertInt(g_calcData_2.condition[2*j+1]))){
                            if(g_result[i].D == -1)return 0;//�������A-1�������Ă����瑱����
                            else return 1;
                        }
                        break;
                    default :
                        printf("%d [error] Condition",__LINE__);
                }
            }
            break;
            break;
        case 3:
            for(int j=0;j<g_calcData_3.conditionSize;j++){
                //printf("%c",g_calcData_1.condition[0]);
                //printf("(%d)",(int)g_calcData_1.condition[0]);
                switch((int)g_calcData_3.condition[2*j]){
                    // result.? �������O�̒l�Ȃ�return 0 (�֐��ɖ߂��Ă��炻�̌�̌v�Z�͏�������Ȃ��Ȃ�)
                    case 65: // A
                        if(!(g_result[i].A == ConvertInt(g_calcData_3.condition[2*j+1]))){
                           if(g_result[i].A == -1)return 0;//�������A-1�������Ă����瑱����
                            else return 1; 
                        }
                        break;
                    case 66: // B
                        //printf("g_result[i].B : %d / sahen : %c",g_result[i].B,g_calcData_1.condition[2*j+1]);
                        if(!(g_result[i].B == ConvertInt(g_calcData_3.condition[2*j+1]))){//�����O
                            if(g_result[i].B == -1)return 0;//�������A-1�������Ă����瑱����
                            else return 1;
                        } 
                        break;
                    case 67: // C
                        if(!(g_result[i].C == ConvertInt(g_calcData_3.condition[2*j+1]))){
                            if(g_result[i].C == -1)return 0;//�������A-1�������Ă����瑱����
                            else return 1;
                        }           
                        break;
                    case 68: // D
                        if(!(g_result[i].D == ConvertInt(g_calcData_3.condition[2*j+1]))){
                            if(g_result[i].D == -1)return 0;//�������A-1�������Ă����瑱����
                            else return 1;
                        }
                        break;
                    default :
                        printf("%d [error] Condition",__LINE__);
                }
            }
            break;
    }
    return 0;
}

double Answer(){
    int i,numerator=0,denominator=0;// counter / ���q�E����
    double result;
    switch(g_Qnum){
        case 1:
            for(i=0;i<SAMPLE_SIZE;i++){
                if(g_result[i].B==1){
                    denominator+=1;
                    if(g_result[i].D == 1) numerator+=1;
                }
            }
            
            break;
        case 2:
            for(i=0;i<SAMPLE_SIZE;i++){
                if(g_result[i].A==0 && g_result[i].D==1){
                    denominator+=1;
                    if(g_result[i].C == 0) numerator+=1;
                }
            }
            break;
        case 3:
            for(i=0;i<SAMPLE_SIZE;i++){
                if(g_result[i].A==1){
                    denominator+=1;
                    if(g_result[i].D == 0) numerator+=1;
                }
            }
            break;
    }
    printf("[Q%d] %d / %d \n",g_Qnum,numerator,denominator);
    if(numerator==0 || denominator ==0){
        printf("[Q%d] result : 0\n\n",g_Qnum);
        return 0;
    }
    result = (double)numerator/(double)denominator;
    printf("[Q%d] result : %lf\n\n",g_Qnum,result);
    return result;
}

//�f�o�b�O�p
void DisplayResult(){
    for(int i=0;i<SAMPLE_SIZE;i++){
        printf("[%d] : A : [%d]\n",i,g_result[i].A);
        printf("[%d] : B : [%d]\n",i,g_result[i].B);
        printf("[%d] : C : [%d]\n",i,g_result[i].C);
        printf("[%d] : D : [%d]\n",i,g_result[i].D);
    }
}