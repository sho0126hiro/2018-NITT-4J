//4J42 廣瀬　翔
#include <stdio.h>
#include <math.h>

double InnerProduct(double a[],double b[],int N){
	//二本のベクトルと要素数を入力して内積を出力
	double c=0;
	double sum=0;
	for(int i=0;i<N;i++){
		c=a[i]*b[i];
		//printf("c=%f a[i]=%f b[i]=%f\n",c,a[i],b[i]);
		sum=sum+c;
		//printf("sum=%f\n",sum);
	}
	return sum;
}

void OB_check(double u1[],double u2[],double u3[]){
	//正規直交基底の確認(orthonormal basis)の確認
	printf("=====正規直交基底の確認=====\n");
	int i,j;
	printf("u1=[");
	for(i=0;i<3;i++)printf("%10f",u1[i]);
	printf(" ]T \n");
	printf("u2=[");
	for(i=0;i<3;i++)printf("%10f",u2[i]);
	printf(" ]T \n");
	printf("u3=[");
	for(i=0;i<3;i++)printf("%10f",u3[i]);
	printf(" ]T \n");
	//内積計算と表示
	printf("<u1・u1> = %f\n",InnerProduct(u1,u1,3));
	printf("<u1・u2> = %f\n",InnerProduct(u1,u2,3));
	printf("<u1・u3> = %f\n",InnerProduct(u1,u3,3));
	printf("<u2・u2> = %f\n",InnerProduct(u2,u2,3));
	printf("<u2・u3> = %f\n",InnerProduct(u2,u3,3));
	printf("<u3・u3> = %f\n",InnerProduct(u3,u3,3));

}

int main(){
	printf("4J 42 廣瀬　翔\n");
	int i,j;
	
	//vector
	double u1[3]={1,0,0};
	double u2[3]={0,1/sqrt(2),-1/sqrt(2)};
	double u3[3]={0,1/sqrt(2),1/sqrt(2)};
	//Xn
	double g[3]={2,-1,1};
	
	printf("=====正規直交基底=====\n");
	
	for(i=0;i<3;i++){
		printf("%9f ",u1[i]);
		printf("%9f ",u2[i]);
		printf("%9f ",u3[i]);
		printf("\n");
	}
	//正規直交基底
	OB_check(u1,u2,u3);
	//元のベクトル
	printf("=====あるベクトルGn=====\n");
	printf("g=[");
	for(i=0;i<3;i++)printf("%10f",g[i]);
	printf(" ]T \n");

	//aを求める。
	//a = <g・u>
	//aは単位ベクトルの各
	double a[3]={0};
	double g_check[3]={0};
	double g_sum[3]={0};
	a[0]=InnerProduct(g,u1,3);
	a[1]=InnerProduct(g,u2,3);
	a[2]=InnerProduct(g,u3,3);
	printf("=====a=====\n");
	for(i=0;i<3;i++)printf("a%d=%f\n",i,a[i]);
	//gの検算
	//g=a1*u1+a2*u2+a3*u3
	for(i=0;i<3;i++){
		u1[i]*=a[0];
		u2[i]*=a[1];
		u3[i]*=a[2];
	}
	//u1 to u3 print (debug)
	/*
	for(i=0;i<3;i++){
		printf("%10f",u1[i]);
		printf("%10f",u2[i]);
		printf("%10f",u3[i]);
		printf("\n");
	}*/
	for(i=0;i<3;i++){
		g_sum[i]+=u1[i];
		g_sum[i]+=u2[i];
		g_sum[i]+=u3[i];
	}
	printf("=====Xn=====\n");
	printf("Xn=[");
	for(i=0;i<3;i++)printf("%10f",g_sum[i]);
	printf(" ]T \n");
}

/***************実行結果******************
4J 42 廣瀬　翔
=====正規直交基底=====
 1.000000  0.000000  0.000000
 0.000000  0.707107  0.707107
 0.000000 -0.707107  0.707107
=====正規直交基底の確認=====
u1=[  1.000000  0.000000  0.000000 ]T
u2=[  0.000000  0.707107 -0.707107 ]T
u3=[  0.000000  0.707107  0.707107 ]T
<u1・u1> = 1.000000
<u1・u2> = 0.000000
<u1・u3> = 0.000000
<u2・u2> = 1.000000
<u2・u3> = 0.000000
<u3・u3> = 1.000000
=====あるベクトルGn=====
g=[  2.000000 -1.000000  1.000000 ]T
=====a=====
a0=2.000000
a1=-1.414214
a2=0.000000
=====Xn=====
Xn=[  2.000000 -1.000000  1.000000 ]T
*****************************************/