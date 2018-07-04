<<<<<<< HEAD
//–––H30”N“xEDSP1-4E”Ô†42–––

#include <stdio.h>

#define DATASIZE 701 //‘ŠŒİ‘ŠŠÖŒW”@data size
#define DATASIZE_2 71 //©ŒÈ‘ŠŠÖŒW”@data size

//Signature
void Signature(){
	printf("//H30”N“x");
	printf("/dsp1-4");
	printf("/42 œA£@ãÄ");
	//how to use
	printf("\n1Da.txt‚Æb.txt‚ğ“Ç‚İ‚İA‘ŠŒİ‘ŠŠÖŒW”‚ğ‹‚ß‚éB\n");
	printf("@@‚Ü‚½Aw’è‚³‚ê‚½‘ŠŒİ‘ŠŠÖŒW”‚Ìˆê•”‚ğƒ^[ƒ~ƒiƒ‹‚Éo—Í‚·‚éB\n");
	printf("2D‹‚ß‚½‘ŠŒİ‘ŠŠÖŒW”‚ğRxy.txt‚Æ‚µ‚Äƒtƒ@ƒCƒ‹o—Í‚·‚éB\n");
	printf("3Dc.txt‚ğ“Ç‚İ‚İA©ŒÈ‘ŠŠÖŒW”‚ğ‹‚ß‚éB\n");
	printf("@@‚Ü‚½Aw’è‚³‚ê‚½©ŒÈ‘ŠŠÖŒW”‚Ìˆê•”‚ğƒ^[ƒ~ƒiƒ‹‚Éo—Í‚·‚éB\n");
	printf("4D‹‚ß‚½©ŒÈ‘ŠŠÖŒW”‚ğRxx.txt‚Æ‚µ‚Äƒtƒ@ƒCƒ‹o—Í‚·‚éB\n");
}
//file“Ç‚İ‚İ
=======
//ï¼Šï¼Šï¼ŠH30å¹´åº¦ãƒ»DSP1-4ãƒ»ç•ªå·42ï¼Šï¼Šï¼Š

#include <stdio.h>

#define DATASIZE 701 //ç›¸äº’ç›¸é–¢ä¿‚æ•°ã€€data size
#define DATASIZE_2 71 //è‡ªå·±ç›¸é–¢ä¿‚æ•°ã€€data size

//Signature
void Signature(){
	printf("//H30å¹´åº¦");
	printf("/dsp1-4");
	printf("/42 å»£ç€¬ã€€ç¿”");
	//how to use
	printf("\n1ï¼a.txtã¨b.txtã‚’èª­ã¿è¾¼ã¿ã€ç›¸äº’ç›¸é–¢ä¿‚æ•°ã‚’æ±‚ã‚ã‚‹ã€‚\n");
	printf("ã€€ã€€ã¾ãŸã€æŒ‡å®šã•ã‚ŒãŸç›¸äº’ç›¸é–¢ä¿‚æ•°ã®ä¸€éƒ¨ã‚’ã‚¿ãƒ¼ãƒŸãƒŠãƒ«ã«å‡ºåŠ›ã™ã‚‹ã€‚\n");
	printf("2ï¼æ±‚ã‚ãŸç›¸äº’ç›¸é–¢ä¿‚æ•°ã‚’Rxy.txtã¨ã—ã¦ãƒ•ã‚¡ã‚¤ãƒ«å‡ºåŠ›ã™ã‚‹ã€‚ã€‚\n");
	printf("3ï¼c.txtã‚’èª­ã¿è¾¼ã¿ã€è‡ªå·±ç›¸é–¢ä¿‚æ•°ã‚’æ±‚ã‚ã‚‹ã€‚\n");
	printf("ã€€ã€€ã¾ãŸã€æŒ‡å®šã•ã‚ŒãŸè‡ªå·±ç›¸é–¢ä¿‚æ•°ã®ä¸€éƒ¨ã‚’ã‚¿ãƒ¼ãƒŸãƒŠãƒ«ã«å‡ºåŠ›ã™ã‚‹ã€‚\n");
	printf("4ï¼æ±‚ã‚ãŸè‡ªå·±ç›¸é–¢ä¿‚æ•°ã‚’Rxx.txtã¨ã—ã¦ãƒ•ã‚¡ã‚¤ãƒ«å‡ºåŠ›ã™ã‚‹ã€‚\n");
}
//fileèª­ã¿è¾¼ã¿
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
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
<<<<<<< HEAD
//File‘‚«‚İ
=======
//Fileæ›¸ãè¾¼ã¿
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
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
<<<<<<< HEAD
//‘ŠŒİ‘ŠŠÖŒW”‚ÌZo
void CrossCorrelation(double data1[],double data2[],double Rxy[]){
	//Rxy:Xi,Yi+m‚Ì“àÏŒ‹‰ÊŠi”[”z—ñ
	/******Zoè‡*****************
	Rxy(m) = 1/N ƒ°(i:0 ~ N-1) X(i) ~ Y(i+m)
	N : datasize
	m : ŠÔ·
	1. Xi‚ÆYi+m‚Ì“àÏ‚ğ‚Æ‚èA”z—ñ‚ÉŠi”[‚·‚é
	2D”z—ñ‚Ì’†g‚ğ‘S•”‘«‚·
	3Dƒf[ƒ^ƒTƒCƒY‚ÅŠ„‚éB
=======
//ç›¸äº’ç›¸é–¢ä¿‚æ•°ã®ç®—å‡º
void CrossCorrelation(double data1[],double data2[],double Rxy[]){
	//Rxy:Xi,Yi+mã®å†…ç©çµæœæ ¼ç´é…åˆ—
	/******ç®—å‡ºæ‰‹é †*****************
	Rxy(m) = 1/N Î£(i:0 ~ N-1) X(i) Ã— Y(i+m)
	N : datasize
	m : æ™‚é–“å·®
	1. Xiã¨Yi+mã®å†…ç©ã‚’ã¨ã‚Šã€é…åˆ—ã«æ ¼ç´ã™ã‚‹
	2ï¼é…åˆ—ã®ä¸­èº«ã‚’å…¨éƒ¨è¶³ã™
	3ï¼ãƒ‡ãƒ¼ã‚¿ã‚µã‚¤ã‚ºã§å‰²ã‚‹ã€‚
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
	*******************************/
	int i,m,j;
	double sum;
	for(m=0;m<=DATASIZE-1;m++){
		sum=0;
		for(i=0;i<=DATASIZE-1-m;i++){
			sum+=data1[i]*data2[m+i];
		}
		sum/=DATASIZE;
        Rxy[m]=sum;
		//printf("Rxy[%d]=%f",m,Rxy[m]);
	}
<<<<<<< HEAD
	printf("\n===‘ŠŒİ‘ŠŠÖŒW”===\n");
	int x[10]={0,100,200,300,400,500,600,700};
	for(i=0;i<8;i++)printf("Rxy(%d)=%f\n",x[i],Rxy[x[i]]);
}
//©ŒÈ‘ŠŠÖŒW”‚ÌZo
void AutoCorrelation(double data1[],double Rxx[]){
	//Rxx:Xi,Xi+m‚Ì“àÏŒ‹‰ÊŠi”[”z—ñ
	/******Zoè‡*****************
	Rxx(m) = 1/N ƒ°(i:0 ~ N-1) X(i) ~ X(i+m)
	N : datasize
	m : ŠÔ·
	1. Xi‚ÆXi+m‚Ì“àÏ‚ğ‚Æ‚èA”z—ñ‚ÉŠi”[‚·‚é
	2D”z—ñ‚Ì’†g‚ğ‘S•”‘«‚·
	3Dƒf[ƒ^ƒTƒCƒY‚ÅŠ„‚éB
=======
	printf("\n===ç›¸äº’ç›¸é–¢ä¿‚æ•°===\n");
	int x[10]={0,100,200,300,400,500,600,700};
	for(i=0;i<8;i++)printf("Rxy(%d)=%f\n",x[i],Rxy[x[i]]);
}
//è‡ªå·±ç›¸é–¢ä¿‚æ•°ã®ç®—å‡º
void AutoCorrelation(double data1[],double Rxx[]){
	//Rxx:Xi,Xi+mã®å†…ç©çµæœæ ¼ç´é…åˆ—
	/******ç®—å‡ºæ‰‹é †*****************
	Rxx(m) = 1/N Î£(i:0 ~ N-1) X(i) Ã— X(i+m)
	N : datasize
	m : æ™‚é–“å·®
	1. Xiã¨Xi+mã®å†…ç©ã‚’ã¨ã‚Šã€é…åˆ—ã«æ ¼ç´ã™ã‚‹
	2ï¼é…åˆ—ã®ä¸­èº«ã‚’å…¨éƒ¨è¶³ã™
	3ï¼ãƒ‡ãƒ¼ã‚¿ã‚µã‚¤ã‚ºã§å‰²ã‚‹ã€‚
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
	*******************************/ 
	int i,m,j;
	double sum;
	for(m=0;m<=DATASIZE_2-1;m++){
		sum=0;
		for(i=0;i<=DATASIZE_2-1-m;i++){
			sum+=data1[i]*data1[m+i];
		}
		sum/=DATASIZE_2;
        Rxx[m]=sum;
		//printf("Rxy[%d]=%f",m,Rxy[m]);
	}
<<<<<<< HEAD
	printf("\n===©ŒÈ‘ŠŠÖŒW”===\n");
=======
	printf("\n===è‡ªå·±ç›¸é–¢ä¿‚æ•°===\n");
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
	int x[10]={0,10,20,30,40,50,60,70};
	for(i=0;i<8;i++)printf("Rxx(%d)=%f\n",x[i],Rxx[x[i]]);
}
//main
int main(){
<<<<<<< HEAD
	//–¼
	Signature();
	//lŒûƒf[ƒ^Ši”[”z—ñ
	double data1[DATASIZE]={0};//a.txt
	double data2[DATASIZE]={0};//b.txt
	double data3[DATASIZE_2]={0};//b.txt
	//ƒtƒ@ƒCƒ‹‚Ì’†g‚ğ“Ç‚İ‚İAdata‚ÉŠi”[‚·‚é
	FileRead("a.txt",data1);
	FileRead("b.txt",data2);
	//Ši”[I—¹
	double Rxy[DATASIZE-1]={0};//‘ŠŒİ‘ŠŠÖŒW”Ši”[—p”z—ñ
=======
	//ç½²å
	Signature();
	//äººå£ãƒ‡ãƒ¼ã‚¿æ ¼ç´é…åˆ—
	double data1[DATASIZE]={0};//a.txt
	double data2[DATASIZE]={0};//b.txt
	double data3[DATASIZE_2]={0};//b.txt
	//ãƒ•ã‚¡ã‚¤ãƒ«ã®ä¸­èº«ã‚’èª­ã¿è¾¼ã¿ã€dataã«æ ¼ç´ã™ã‚‹
	FileRead("a.txt",data1);
	FileRead("b.txt",data2);
	//æ ¼ç´çµ‚äº†
	double Rxy[DATASIZE-1]={0};//ç›¸äº’ç›¸é–¢ä¿‚æ•°æ ¼ç´ç”¨é…åˆ—
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
	CrossCorrelation(data1,data2,Rxy);
	FileWrite("Rxy.txt",Rxy,DATASIZE);

	FileRead("c.txt",data3);
<<<<<<< HEAD
	double Rxx[DATASIZE_2-1]={0};//©ŒÈ‘ŠŠÖŒW”Ši”[—p”z—ñ
=======
	double Rxx[DATASIZE_2-1]={0};//è‡ªå·±ç›¸é–¢ä¿‚æ•°æ ¼ç´ç”¨é…åˆ—
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
	AutoCorrelation(data3,Rxx);
	FileWrite("Rxx.txt",Rxx,DATASIZE_2);
	return 0;
}
<<<<<<< HEAD
/****ÀsŒ‹‰Ê*****
===‘ŠŒİ‘ŠŠÖŒW”===
=======
/****å®Ÿè¡Œçµæœ*****
===ç›¸äº’ç›¸é–¢ä¿‚æ•°===
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
Rxy(0)=0.025116
Rxy(100)=0.075794
Rxy(200)=0.029542
Rxy(300)=0.007626
Rxy(400)=0.007195
Rxy(500)=0.007679
Rxy(600)=0.001238
Rxy(700)=0.000000

<<<<<<< HEAD
===©ŒÈ‘ŠŠÖŒW”===
=======
===è‡ªå·±ç›¸é–¢ä¿‚æ•°===
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
Rxx(0)=0.180281
Rxx(10)=-0.027261
Rxx(20)=-0.056572
Rxx(30)=0.013220
Rxx(40)=0.002022
Rxx(50)=-0.012665
Rxx(60)=0.000095
Rxx(70)=0.010008
<<<<<<< HEAD
****************/
=======
****************/
>>>>>>> a3c39b6a5ff29ec0dfd6027159948244592dd0be
