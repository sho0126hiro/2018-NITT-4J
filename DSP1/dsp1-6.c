#include <stdio.h>
#include <stdlib.h>

// RIFF�`�����N wave�t�H�[���^�C�v�\����
typedef struct{
    char *waveFileName; // filename
    char id[4];         // "RIFF"
    unsigned long size; // filesize
    char form[4];       // "WAVE"
} riff_chunk;

// fmt�`�����N�\����
typedef struct{
    char id[4];                 // "fmt " (space������)
    unsigned long size;         // fmt chunk size
    unsigned short format_id;   // format id (pcm:1)
    unsigned short channel;     // channel (monaural:1 stereo:2))
    unsigned long fs;           // �T���v�����O���g��
    unsigned long byte_sec;     // 1�b������̃o�C�g��(fs * byte_samp)
    unsigned short byte_samp;   // 1�v�f�̃o�C�g�� (channel * bit/8)
    unsigned short bit;         // �ʎq���r�b�g��(8 or 16)
} fmt_chunk;

typedef struct{
    char id[4];                 // "data " (space������)
    unsigned long size;         // data chunk size    
} data_chunk;

// �O���[�o���\���̐錾
riff_chunk _riff;
fmt_chunk  _fmt;
data_chunk _data;

//����
void Signature(){
	//�g����
	printf("\nWAVE <---> TEXT �o���ϊ��Ή��v���O����\n");
	printf("�ǂݍ��݁E�������݃t�@�C�����ɂ͊g���q���L�����Ă��������B\n");
}

void ReadWave(char *waveFile){
    FILE *fp,*fp2;
    int i;
    short pcm_data;
    fp = fopen(waveFile,"rb");
    if(fp==NULL){
        printf("[%s] can't open a file\n",waveFile);
        exit(-1);
		return;
    }
    _riff.waveFileName = waveFile;
    /* ---------------- RIFF CHUNK ---------------- */
    // �t�@�C���ǂݍ��݈ʒu���t�@�C���̐擪�o�C�g��
    fseek(fp,0,SEEK_SET); 
    // "RIFF"
    for(i=0;i<4;i++)fread(&_riff.id[i],sizeof(char),1,fp);
    // FileSize
    fread(&_riff.size,sizeof(unsigned long),1,fp);
    // "WAVE"
    for(i=0;i<4;i++)fread(&_riff.form[i],sizeof(char),1,fp);
    
    /* ---------------- FMT CHUNK ---------------- */
    // "FMT"
    for(i=0;i<4;i++)fread(&_fmt.id[i],sizeof(char),1,fp);
    // Size
    fread(&_fmt.size,sizeof(unsigned long),1,fp);
    // formatID
    fread(&_fmt.format_id,sizeof(unsigned short),1,fp);
    // channel
    fread(&_fmt.channel,sizeof(unsigned short),1,fp);
    // fs
    fread(&_fmt.fs,sizeof(unsigned long),1,fp);
    // byte_sec
    fread(&_fmt.byte_sec,sizeof(unsigned long),1,fp);
    // byte_samp
    fread(&_fmt.byte_samp,sizeof(unsigned short),1,fp);
    // bit
    fread(&_fmt.bit,sizeof(unsigned short),1,fp);

    /* ---------------- DATA CHUNK ---------------- */
    // "DATA"
    for(i=0;i<4;i++)fread(&_data.id[i],sizeof(char),1,fp);
    // Size
    fread(&_data.size,sizeof(unsigned long),1,fp);
    fclose(fp);
}

// WAVE -> TEXT
// @param {char *} waveFile  waveFile
// @param {char *} txtFile   textFile
void WaveConverttoText(char *waveFile,char *txtFile){
    FILE *fp,*fp2;
    int i;
    short pcm_data;
    fp = fopen(waveFile,"rb");
    if(fp==NULL){
        printf("[%s] can't open a file\n",waveFile);
        exit(-1);
		return;
    }
    fp2 = fopen(txtFile,"w");
    if(fp2==NULL){
       printf("[%s] can't oepn a file\n",txtFile);
        exit(1);
        return;
    }
    _riff.waveFileName = waveFile;
    /* ---------------- RIFF CHUNK ---------------- */
    // �t�@�C���ǂݍ��݈ʒu���t�@�C���̐擪�o�C�g��
    fseek(fp,0,SEEK_SET); 
    // "RIFF"
    for(i=0;i<4;i++)fread(&_riff.id[i],sizeof(char),1,fp);
    // FileSize
    fread(&_riff.size,sizeof(unsigned long),1,fp);
    // "WAVE"
    for(i=0;i<4;i++)fread(&_riff.form[i],sizeof(char),1,fp);
    
    /* ---------------- FMT CHUNK ---------------- */
    // "FMT"
    for(i=0;i<4;i++)fread(&_fmt.id[i],sizeof(char),1,fp);
    // Size
    fread(&_fmt.size,sizeof(unsigned long),1,fp);
    // formatID
    fread(&_fmt.format_id,sizeof(unsigned short),1,fp);
    // channel
    fread(&_fmt.channel,sizeof(unsigned short),1,fp);
    // fs
    fread(&_fmt.fs,sizeof(unsigned long),1,fp);
    // byte_sec
    fread(&_fmt.byte_sec,sizeof(unsigned long),1,fp);
    // byte_samp
    fread(&_fmt.byte_samp,sizeof(unsigned short),1,fp);
    // bit
    fread(&_fmt.bit,sizeof(unsigned short),1,fp);

    /* ---------------- DATA CHUNK ---------------- */
    // "DATA"
    for(i=0;i<4;i++)fread(&_data.id[i],sizeof(char),1,fp);
    // Size
    fread(&_data.size,sizeof(unsigned long),1,fp);
    // data >> read and write
    for(i=0;i<_data.size/2;i++){
        fread(&pcm_data,sizeof(unsigned short),1,fp);
        fprintf(fp2,"%d\n",pcm_data);
    }
    fclose(fp);
    fclose(fp2);
}

// Text -> WAVE
// @param {char *} txtFile   textFile
// @param {char *} waveFile  waveFile
// @param {int}    txtlength �e�L�X�g�t�@�C���̒���
void TextConverttoWave(char *txtFile, char *waveFile, int txtlength){
    FILE *fp,*fp2;
    int i;
    fp = fopen(txtFile,"r");
    if(fp==NULL){
        printf("[%s] can't open a file\n",txtFile);
        exit(-1);
		return;
    }
    fp2 = fopen(waveFile,"wb");
    if(fp2==NULL){
       printf("[%s] can't oepn a file\n",waveFile);
        exit(-1);
        return;
    }
    /* ---------------- �e�L�X�g�t�@�C���ǂݍ��� ---------------- */
    
    short *ReadData;
    i=0;
    ReadData = (short *) malloc(sizeof(short) * txtlength);
    fseek(fp,0,SEEK_SET);
    char line[512];
    while(fgets(line,512,fp)!=NULL){
        ReadData[i]=atoi(line);
        i++;
    }
    /* ---------------- RIFF CHUNK ---------------- */
    char riff_id[4] = "RIFF";
    for(i=0;i<4;i++)fwrite(&riff_id[i],sizeof(char),1,fp2);
    unsigned long filesize = 36 + txtlength;
    fwrite(&filesize,sizeof(unsigned long),1,fp2);
    char riff_from[4] = "WAVE";
    for(i=0;i<4;i++)fwrite(&riff_from[i],sizeof(char),1,fp2);
    /* ---------------- FMT CHUNK ---------------- */
    char fmt_id[4] = "fmt ";
    for(i=0;i<4;i++)fwrite(&fmt_id[i],sizeof(char),1,fp2);
    unsigned long fmt_size = 16;
    fwrite(&fmt_size,sizeof(unsigned long),1,fp2);
    unsigned short format_id = 1;
    fwrite(&format_id,sizeof(unsigned short),1,fp2);
    unsigned short channel = 1;
    fwrite(&channel,sizeof(unsigned short),1,fp2);
    unsigned long fs = 11025;
    fwrite(&fs,sizeof(unsigned long),1,fp2);
    unsigned long byte_sec = 22050;
    fwrite(&byte_sec,sizeof(unsigned long),1,fp2);
    unsigned short byte_samp = 2;
    fwrite(&byte_samp,sizeof(unsigned short),1,fp2);
    unsigned short bit = 16;
    fwrite(&bit,sizeof(unsigned short),1,fp2);
    /* ---------------- DATA CHUNK ---------------- */
    char data_id[4] = "data";
    for(i=0;i<4;i++)fwrite(&data_id[i],sizeof(char),1,fp2);
    unsigned long data_size = txtlength*2;
    fwrite(&data_size,sizeof(unsigned long),1,fp2);
    for(i=0;i<txtlength;i++){
        fwrite(&ReadData[i],sizeof(unsigned short),1,fp2);
    }
    free(ReadData);
    fclose(fp);
    fclose(fp2);
}

// File�̒���(�e�L�X�g�j���擾����
// @param {char *} file filename
// @return {int} datasize datasize
// @return {int} -1 (Exception) [can't open a file]
int getFileSize(char *file){
    FILE *fp;
    fp = fopen(file,"rb");
    if(fp==NULL){
        printf("[%s] can't open a file\n",file);
        exit(-1);
		return -1;
    }
    char line[512];
    int datasize = 0;
    while(fgets(line,512,fp)!=NULL){
        datasize++;
    }
    fclose(fp);
    return datasize;
}

// ��v�f�[�^�\��
void Display(){
    printf("----- ���� ----- \n");
    printf("�t�@�C���� �@�@    : %s \n",_riff.waveFileName);
    printf("�t�@�C���T�C�Y �@�@: %lu \n",_riff.size);
    printf("�`���l�����@�@ �@�@: %u  \n",_fmt.channel);
    printf("�T���v�����O���g�� : %lu[Hz]\n",_fmt.fs);
    printf("�ʎq���r�b�g�� �@�@: %u [bit]\n",_fmt.bit);
    printf("�T���v����         : %u [sample]\n",_data.size/2);
    double fs = (double)_fmt.fs;
    printf("�^������           : %f [s]\n",1/fs*_data.size/2);
}
// �S�Ẵf�[�^��\������
void Display_all(){
    printf("----- ���� ----- \n");
    printf("�t�@�C���� �@�@    : %s \n",_riff.waveFileName);
    printf("riff\n");
    printf("id                 : %s\n",_riff.id);
    printf("�t�@�C���T�C�Y �@�@: %lu \n",_riff.size);
    printf("form               : %s\n",_riff.form);
    printf("fmt\n");
    printf("id                 : %s\n",_fmt.id);
    printf("size               : %lu\n",_fmt.size);
    printf("format_id          : %u\n",_fmt.format_id);
    printf("�`���l�����@�@ �@�@: %u  \n",_fmt.channel);
    printf("�T���v�����O���g�� : %lu[Hz]\n",_fmt.fs);
    printf("byte sec           : %lu\n",_fmt.byte_sec);
    printf("byte samp          : %u\n",_fmt.byte_samp);
    printf("�ʎq���r�b�g�� �@�@: %u [bit]\n",_fmt.bit);
    printf("data\n");
    printf("id                 : %s\n",_data.id);
    printf("size               : %lu\n",_data.size);
    printf("�T���v����         : %u [sample]\n",_data.size/2);
    double fs = (double)_fmt.fs;
    printf("�^������           : %f [s]\n",1/fs*_data.size/2);
}

int menu(){
    static int c = 0;
    if(c!=0)printf("********************\n");
    c++;
    int num;
    char in[512];
    char out[512];
    printf("1 : wave -> text\n");
    printf("2 : text -> wave\n");
    printf("3 : print wavefiledata\n");
    printf("4 : �I��\n");
    printf("�p�r(�����j��I�����Ă������� >> ");
scanNum:
    scanf("%d",&num);
    switch(num){
        case 1:
            // wave -> text
            printf("WAVE -> TEXT\n");
            printf("wave�t�@�C��������͂��Ă������� >> ");
            scanf("%s",in);
            printf("�o�͂���text�t�@�C��������͂��Ă������� >> ");
            scanf("%s",out);
            WaveConverttoText(in,out);
            break;
        case 2:
            // text -> wave
            printf("TEXT -> WAVE\n");
            printf("text�t�@�C��������͂��Ă������� >> ");
            scanf("%s",in);
            printf("�o�͂���wave�t�@�C��������͂��Ă������� >> ");
            scanf("%s",out);
            TextConverttoWave(in,out,getFileSize(in));
            break;
        case 3:
            // print wavefiledata
            printf("print wavefiledata\n");
            printf("wave�t�@�C��������͂��Ă������� >> ");
            scanf("%s",in);
            ReadWave(in);
            Display();
            // Display_all();
            break;
        case 4:
            printf("�I��");
            return 0;
        default:
            printf("�L���Ȑ����ł͂���܂���B�ēx���͂��Ă��������B>> ");
            goto scanNum;
    }
    return 1;
}

int main(){
    Signature();
    while(menu());
    return 0;
}