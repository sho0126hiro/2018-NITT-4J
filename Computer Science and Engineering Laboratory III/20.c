#include<3694.h>

void msecWait(unsigned long int length)
{
//���ԑ҂������鏈��
  volatile unsigned long int i;
  //volatile unsigned long int j;
  
  for(i=0;i<length*568;i++){
  //	for(j=0;j<710;j++){
  //	}
  
  }

}

int main(void)
{
  //P86���o�̓|�[�g�ɐݒ�
  IO.PCR8|=0x40;
  while(1){
    //P86�̏o�͂��Z�b�g
    IO.PDR8.BYTE|=0x40;
    msecWait(1);

    //P86�̏o�͂��N���A
    IO.PDR8.BYTE&=0xBF;
	msecWait(1);
  }
}
