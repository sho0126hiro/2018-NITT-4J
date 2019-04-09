#include<3694.h>

void msecWait(unsigned long int length)
{
//時間待ちをする処理
  volatile unsigned long int i;
  //volatile unsigned long int j;
  
  for(i=0;i<length*568;i++){
  //	for(j=0;j<710;j++){
  //	}
  
  }

}

int main(void)
{
  //P86を出力ポートに設定
  IO.PCR8|=0x40;
  while(1){
    //P86の出力をセット
    IO.PDR8.BYTE|=0x40;
    msecWait(1);

    //P86の出力をクリア
    IO.PDR8.BYTE&=0xBF;
	msecWait(1);
  }
}
