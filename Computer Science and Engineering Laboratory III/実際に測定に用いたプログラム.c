#include <3694.h>
#include "ltrc_lib.h"

/*-----------------------------------------WAIT-----------------------------------------*/
void msecWait(unsigned long int length)
{
    //���ԑ҂������鏈��
    volatile unsigned long int i;
    for(i=0;i<length*568;i++){ 
  }
}
/*-----------------------------------------DUTY-----------------------------------------*/
//�E�̂݃f���[�e�B���ω����������ꍇ
unsigned int GRBset(int duty){
    IO.PDR1.BYTE&=0xf9; // 1111 1001
    unsigned int b=0.01*duty*625; //GRA=625�ɑ΂���duty�̊������o��
    if(b==625)b--; //duty=100
    else if(b==0)b++; //duty=0
    TW.GRB=b;
}
//���̂݃f���[�e�B���ω����������ꍇ
unsigned int GRCset(int duty){
    IO.PDR1.BYTE&=0xf9; // 1111 1001
    unsigned int c=0.01*duty*625; //GRA=625�ɑ΂���duty�̊������o��
    if(c==625)c--; //duty=100
    else if(c==0)c++; //duty=0
    TW.GRC=c;
}
//���������Ƀf���[�e�B���ω����������ꍇ
void GRset(int dutyL,int dutyR){
    GRBset(dutyL);
    GRCset(dutyR);
}
/*-----------------------------------------BRAKE-----------------------------------------*/
//���������u���[�L���������ꍇ
void Brake(){
    GRset(100,100);
    IO.PDR1.BYTE|=0x06; // 0000 0110
}
//���̂݃u���[�L���������ꍇ�FP11
void Brake_L(){
    GRBset(100);
    IO.PDR1.BYTE|=0x02; //0000 0010
}
//�E�̂݃u���[�L���������ꍇ�FP12
void Brake_R(){
    GRCset(100);
    IO.PDR1.BYTE|=0x04; // 0000 0100
}
/*-----------------------------------------OPERATE-----------------------------------------*/
void setOperation(int B_duty,int C_duty){
    if(B_duty==-1 && C_duty==-1) Brake();
    else if(B_duty==-1)          Brake_L();
    else if(C_duty==-1)          Brake_R();
    else                         GRset(B_duty,C_duty);
}
/*-----------------------------------------MAIN-----------------------------------------*/
int main(void)
{
    //P86,P87���o�̓|�[�g�ɐݒ�i����m�F�pLED�j
    IO.PCR8|=0xc0;
    //P11,P12���o�̓|�[�g�ɐݒ�i���[�^�j
    IO.PCR1|=0x06;
    initSCI3();
    // ad
    AD.CSR.BYTE = 0x39; //AD�ϊ������ݒ�
                          //0011 1001
                          //AD�ϊ��J�n
                          //Scan mode
                          //(70�X�e�[�g)
                          //AN0-AN1
    //�o�̓��W�X�^�̏�����
    AD.DRA=0x0000;
    AD.DRB=0x0000;
    
    TW.TMRW.BYTE=0x03; //(0000 0011) : FTIOB FTIOC >> pwm mode
    TW.TCRW.BYTE=0xB6; //(1011 0110) : �R���y�A�}�b�`A��TNCT���N���A
                                     //�N���b�N��/8
                                     //FTIOB FTIOC �o�͒[�q�̏o�͒l�̐ݒ�(1)
    TW.TCNT=0x0000;    // TCNT�̏����� 
    TW.GRA=625;       // 0.25ms (4kHz)
    TW.TMRW.BIT.CTS=1; // TCNT�J�E���^�X�^�[�g
    while(1){
        unsigned int left,right;
        while(AD.CSR.BIT.ADF!=1);  /* �ϊ����ʂ��ł�܂ő҂�  */
        //A-D�ϊ��I��
        left = AD.DRA >> 6;//left
        right = AD.DRB >> 6;//right
        //LED
        //SCI3printf("left= %b (%d)[%x]  right = %b (%d)[%x]\n",left,left,left,right,right,right);
        IO.PDR8.BYTE &=0x3f;  //LED1��LED2������
        if(left > 0x3ed && right > 0x3ed){
            //SCI3printf("all very white\n");
            //�ǂ�����m���ɔ�
            setOperation(70,70);
            //msecWait(100);
        }else if(left > 0x1c2 && right > 0x1c2){
            //�ǂ����������
           // SCI3printf("all white\n");
            setOperation(70,70);
            //msecWait(100);
        }else if(left > 0x1c2 && right <0x1c2){
            //�E�����E�ɓ�������
            if( right < 0x78){
                //�E�߂����ፕ
                //SCI3printf("left white , right very black\n");
                // ��������
                setOperation(85,40);
            }else{
                // ���Ƃ���
                //SCI3printf("left white,right  tyoi black\n");
                setOperation(65,35);
            }
        }else if(left < 0x1c2 && right > 0x1c2){
            //�������E�ɓ�������
            if(left < 0x87){
                //mettya kuro
                // ��������
                //SCI3printf("left very black right white\n");
                setOperation(40,85);
            }else{
                //SCI3printf("left tyoi black,right white\n");
                // ���Ƃ���
                setOperation(35,65);
            }
        }else{
            //SCI3printf("soreigai\n");
        }
        AD.CSR.BIT.ADF =0; //�ꉞ
    }
}