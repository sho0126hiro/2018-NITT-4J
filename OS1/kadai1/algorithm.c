#include <stdio.h>

/* 1万以上の素数を表示し続けるタスク*/
void primeNumber(){
	int num=10000;
	int i;
	int check = 1;
	while(1){
        check = 1;
        if(num == 11000)break;
		if(num%2==0){
			num++;
            printf("[%d]waru2 \n",num-1);
			continue;
		}
		if(num%3==0){
			num++;
            printf("[%d]waru3 \n",num-1);
			continue;
		}
		for(i=4;i<=num/2;i++){
			if((num%i)==0){
				check=0;
                printf("[%d]waru%d \n",num,i);
				break;
			}
		}
		if(check){
			printf("primeNumber :%8d\n",num);
		}
		num++;
	}
}

int main(){
    primeNumber();
    return 0;
}