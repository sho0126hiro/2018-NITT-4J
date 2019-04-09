#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define SAMPLE_SIZE 5000000
#define TRY 30
// - グローバル変数宣言（変数名 : g_ )　-----------------------------------------------------
//-------------乱数結果格納用構造体-------------　
typedef struct{
    int A;
    int B;
    int C;
    int D;
}RandomResult_t; // (各要素に0,1しか入らない。)
//-------------乱数結果格納用-------------
RandomResult_t g_result[SAMPLE_SIZE];

//-------------定義された確率データ-------------
double g_probability[4][8]={
    {0.20,0,80},           // A=0,1;
    {0.85,0.15},           // B=0,1;
    {0.10,0.75,0.40,0.95,  // C=0 | A,B = 0,0 0,1 1,0 1,1
     0.90,0.25,0.70,0.05}, // C=1 | A,B = 0,0 0,1 1,0 1,1
    {0.95,0.80,            // D=0 | C = 0,1
     0.05,0.20}            // D=1 | C = 0,1
};

// - 構造体宣言 求めたい条件付確率が入る
/* 定義方法
P(A=0 | B=0)　    .probability="A0" , conditionSize=1,  .condition="B0" 
P(A=0 | B=0,C=1)　.probability="A0" , conditionSize=2,  .condition="B0C1"
                        求めたい確率,        条件の数,  条件（いくつでも）
*/
typedef struct{
    char probability[2];
    int  conditionSize;
    char condition[];
}ConditionalProbability_t;
//求めたい条件付き確率の定義
ConditionalProbability_t g_calcData_1={"D1",1,"B1"};
ConditionalProbability_t g_calcData_2={"C0",2,"A0D1"};
ConditionalProbability_t g_calcData_3={"D0",1,"A1"};

//現在の問題番号
int g_Qnum=0;
// -----------------------------------------------------------------------------------------

//（一桁のみ）文字列の数字をint型に変換するマクロ
#define ConvertInt(num) ((int)num - '0')
/*  次の文が同じ意味になる
    printf("%d\n",(int)g_calcData.condition[1]-'0');
    printf("%d\n",ConvertInt(g_calcData.condition[1]));*/

// - 関数宣言 ------------------------------------------------------------------------------
void InitResult();// - 乱数結果格納用配列の初期化関数
void CalcResult();// - 乱数生成　>>　格納
int  GetRand(double p_zero);
int  Check(int i);
double Answer();
void DisplayResult();
void FileWrite(char *filename,double q1[],double q2[],double q3[],int length);
// - main ------------------------------------------------------------------------------
int main(){
    //乱数出力元の初期化
    srand((unsigned)time(NULL));
    int i;
    double p1[TRY];
    double p2[TRY];
    double p3[TRY];
    for(i=0;i<TRY;i++){
        //問題1
        g_Qnum=1;
        InitResult(); //乱数結果格納用配列をすべて―1に初期化
        CalcResult(); //乱数生成　>>　0/1をg_resultに格納
        //DisplayResult();
        //ここまでで乱数に対応したデータは全てそろっている
        //問題を解く
        p1[i] = Answer();
        //問題2
        //g_Qnum=2;
        //InitResult(); //乱数結果格納用配列をすべて―1に初期化
        //CalcResult(); //乱数生成　>>　0/1をg_resultに格納
        //DisplayResult();
        //ここまでで乱数に対応したデータは全てそろっている
        //問題を解く
        //p2[i] = Answer();
        //問題3
        //g_Qnum=3;
        //InitResult(); //乱数結果格納用配列をすべて―1に初期化
        //CalcResult(); //乱数生成　>>　0/1をg_resultに格納
        //DisplayResult();
        //ここまでで乱数に対応したデータは全てそろっている
        //問題を解く
        //p3[i] = Answer();
        // printf("1: %lf\n",p1[i]);
        // printf("2: %lf\n",p2[i]);
        // printf("3: %lf\n",p3[i]);
    }

    FileWrite("try.txt",p1,p2,p3,TRY);
    return 0;
}

// - 乱数結果格納用配列の初期化関数 -----------------------------------------------------
void InitResult(){
    //乱数結果格納用配列をすべて―1に初期化
    for(int i=0;i<SAMPLE_SIZE;i++){
        g_result[i].A = -1;
        g_result[i].B = -1;
        g_result[i].C = -1;
        g_result[i].D = -1;
    }
}

// - 乱数生成　>>　格納 ---------------------------------------------------------------------
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

//p_zeroの確率で0を返す。それ以外は1
int GetRand(double p_zero){
    double result;
    // 乱数を出力し、乱数の最大値で割ることで0~1の小数を出力する
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

// 格納されたデータが条件に合っていない場合return 1を返す
int Check(int i){
    //一度に全ての問題を解こうとしたときにうまく変数の受け渡しができなかったため、
    //switch/caseでごり押した。
    //printf("[%d]",g_Qnum);
    switch(g_Qnum){
        case 1:
            for(int j=0;j<g_calcData_1.conditionSize;j++){
                //printf("%c",g_calcData_1.condition[0]);
                //printf("(%d)",(int)g_calcData_1.condition[0]);
                switch((int)g_calcData_1.condition[2*j]){
                    // result.? が条件外の値ならreturn 0 (関数に戻ってからその後の計算は処理されなくなる)
                    case 65: // A
                        if(!(g_result[i].A == ConvertInt(g_calcData_1.condition[2*j+1]))){
                           if(g_result[i].A == -1)return 0;//ただし、-1が入っていたら続ける
                            else return 1; 
                        }
                        break;
                    case 66: // B
                        //printf("g_result[i].B : %d / sahen : %c",g_result[i].B,g_calcData_1.condition[2*j+1]);
                        if(!(g_result[i].B == ConvertInt(g_calcData_1.condition[2*j+1]))){//条件外
                            if(g_result[i].B == -1)return 0;//ただし、-1が入っていたら続ける
                            else return 1;
                        } 
                        break;
                    case 67: // C
                        if(!(g_result[i].C == ConvertInt(g_calcData_1.condition[2*j+1]))){
                            if(g_result[i].C == -1)return 0;//ただし、-1が入っていたら続ける
                            else return 1;
                        }           
                        break;
                    case 68: // D
                        if(!(g_result[i].D == ConvertInt(g_calcData_1.condition[2*j+1]))){
                            if(g_result[i].D == -1)return 0;//ただし、-1が入っていたら続ける
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
                    // result.? が条件外の値ならreturn 0 (関数に戻ってからその後の計算は処理されなくなる)
                    case 65: // A
                        if(!(g_result[i].A == ConvertInt(g_calcData_2.condition[2*j+1]))){
                           if(g_result[i].A == -1)return 0;//ただし、-1が入っていたら続ける
                            else return 1; 
                        }
                        break;
                    case 66: // B
                        //printf("g_result[i].B : %d / sahen : %c",g_result[i].B,g_calcData_1.condition[2*j+1]);
                        if(!(g_result[i].B == ConvertInt(g_calcData_2.condition[2*j+1]))){//条件外
                            if(g_result[i].B == -1)return 0;//ただし、-1が入っていたら続ける
                            else return 1;
                        } 
                        break;
                    case 67: // C
                        if(!(g_result[i].C == ConvertInt(g_calcData_2.condition[2*j+1]))){
                            if(g_result[i].C == -1)return 0;//ただし、-1が入っていたら続ける
                            else return 1;
                        }           
                        break;
                    case 68: // D
                        if(!(g_result[i].D == ConvertInt(g_calcData_2.condition[2*j+1]))){
                            if(g_result[i].D == -1)return 0;//ただし、-1が入っていたら続ける
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
                    // result.? が条件外の値ならreturn 0 (関数に戻ってからその後の計算は処理されなくなる)
                    case 65: // A
                        if(!(g_result[i].A == ConvertInt(g_calcData_3.condition[2*j+1]))){
                           if(g_result[i].A == -1)return 0;//ただし、-1が入っていたら続ける
                            else return 1; 
                        }
                        break;
                    case 66: // B
                        //printf("g_result[i].B : %d / sahen : %c",g_result[i].B,g_calcData_1.condition[2*j+1]);
                        if(!(g_result[i].B == ConvertInt(g_calcData_3.condition[2*j+1]))){//条件外
                            if(g_result[i].B == -1)return 0;//ただし、-1が入っていたら続ける
                            else return 1;
                        } 
                        break;
                    case 67: // C
                        if(!(g_result[i].C == ConvertInt(g_calcData_3.condition[2*j+1]))){
                            if(g_result[i].C == -1)return 0;//ただし、-1が入っていたら続ける
                            else return 1;
                        }           
                        break;
                    case 68: // D
                        if(!(g_result[i].D == ConvertInt(g_calcData_3.condition[2*j+1]))){
                            if(g_result[i].D == -1)return 0;//ただし、-1が入っていたら続ける
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
    int i,numerator=0,denominator=0;// counter / 分子・分母
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
    //printf("[Q%d] %d / %d \n",g_Qnum,numerator,denominator);
    if(numerator==0 || denominator ==0){
        //printf("[Q%d] result : 0 calc : 0\n\n",g_Qnum);
        return 0;
    }
    result = (double)numerator/(double)denominator;
    //printf("[Q%d] result : %lf calc : %lf\n\n",g_Qnum,result,(double)numerator/(double)denominator);
    return result;
}

//デバッグ用
void DisplayResult(){
    for(int i=0;i<SAMPLE_SIZE;i++){
        printf("[%d] : A : [%d]\n",i,g_result[i].A);
        printf("[%d] : B : [%d]\n",i,g_result[i].B);
        printf("[%d] : C : [%d]\n",i,g_result[i].C);
        printf("[%d] : D : [%d]\n",i,g_result[i].D);
    }
}

//File書き込み
void FileWrite(char *filename,double q1[],double q2[],double q3[],int length){
	FILE *fp;
	//printf("| function : %s | filename:%s |\n",__FUNCTION__,filename);
	fp=fopen(filename,"w");
	if(fp==NULL){
		printf("[%d] can't open a file\n",__LINE__);
		//exit(1);
		return;
	}
	for(int i=0;i<length;i++){
		fprintf(fp,"%f\n",q1[i]);
	}
	fclose(fp);
}