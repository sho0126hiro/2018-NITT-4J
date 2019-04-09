#include "kernel.h"
#include "kernel_id.h"
#include "MinSys3069.h"
#include "sample.h"

ID tskID1;
ID tskID2;

/* スタートアップルーチンから最初に呼び出される初期化関数 */
/* OS起動前にすること（SCIの初期化など）を行っておく      */
/* この関数からスタートアップルーチンに戻った後に，       */
/* スタートアップルーチンはHOSを呼び出す                  */
void preStartHos()
{
	initSCI1();              /* SCIの初期化 */
	SCI1_printf("\npreStartHos: start!\n");  /* 開始メッセージ */
}

/* HOS下で最初に起動するハンドラ*/
/* system.cfg中で静的に起動される */
void OnHosStart(VP_INT exinf)
{
	const static T_CTSK pk_ctsk  = {TA_HLNG, 1,   printTime, 2, 128, NULL};
	const static T_CTSK pk_ctsk2 = {TA_HLNG, 1, primeNumber, 3, 256, NULL};
	ER_ID tskid;
	ER_ID tskid2;
	putStringSCI1("OnHosStart: starting!\n");
	tskid=acre_tsk(&pk_ctsk);
	tskid2=acre_tsk(&pk_ctsk2);
	if (E_OK<tskid) {
		tskID1=tskid;
		act_tsk(tskID1);
	} else {
		SCI1_printf("acre_tsk err %d\n",tskid);
	}
	if (E_OK<tskid2) {
		tskID2=tskid2;
		act_tsk(tskID2);
	} else {
		SCI1_printf("acre_tsk err %d\n",tskid2);
	}
}

/* 1secごとにタイマの時間を表示するタスク */
/* system.cfg中で静的に生成され，OnHosStart()中で起動されている */
void printTime(VP_INT exinf)
{
	SYSTIM time;
	PRI tskpri = 1;
	ER checker;
	while (1) { /*永久ループ*/
		/* タイマ値取得 */
		get_tim(&time);
		
		if((unsigned long int)time.ltime > 3000){
			/* 3秒経過時 */
			checker = chg_pri(tskID2,tskpri);
			if(checker != E_OK){
				SCI1_printf("ercd_tsk err %d\n",checker);
			}
		}
		
		/* タイマ値出力 */
		SCI1_printf("printTime:%8ld\n",(unsigned long int)time.ltime);
		
		/* 1000msec待つ(OSにCPU利用権を一時的に返し，時間になったら戻してもらう) */
		dly_tsk(1000);
	}
}

/* 1万以上の素数を表示し続けるタスク*/
void primeNumber(VP_INT exinf){
	int num=10000;
	int i;
	int check = 1;
	while(1){
		check = 1;
		if(num%2==0){
			num++;
			continue;
		}
		if(num%3==0){
			num++;
			continue;
		}
		for(i=4;i<=num/2;i++){
			if((num%i)==0){
				check=0;
				break;
			}
		}
		if(check){
			SCI1_printf("primeNumber :%8d\n",num);
		}
		if(num == 32767) num =10000;
		num++;
	}
}
/*
実行結果
preStartHos: start!
OnHosStart: starting!
printTime:       1
primeNumber :   10007
primeNumber :   10009
primeNumber :   10037
primeNumber :   10039
primeNumber :   10061
primeNumber :   10067
primeNumber :   10069
primeNumber :   10079
primeNumber :   10091
primeNumber :   10093
primeNumber :   10099
primeNumber :   10103
primeNumber :   10111
primeNumber :   10133
primeNumber :   10139
primeNumber :   10141
primeNumber :   10151
primeNumber :   10159
primeNumber :   10163
primeNumber :   10169
primeNumber :   10177
primeNumber :   10181
primeNumber :   10193
primeNumber :   10211
primeNumber :   10223
primeNumber :   10243
primeNumber :   10247
primeNumber :   10253
primeNumber :   10259
primeNumber :   10267
primeNumber :   10271
primeNumber :   10273
primeNumber :   10289
primeNumber :   10301
primeNumber :   10303
primeNumber :   10313
primeNumber :   10321
primeNumber :   10331
primeNumber :   10333
primeNumber :   10337
primeNumber :   10343
primeNumber :   10357
primeNumber :   10369
primeNumber :   10391
primeNumber :   10399
primeNumber :   10427
primeNumber :   10429
primeNumber :   10433
primeNumber :   10453
primeNumber :   10457
primeNumber :   10459
primeNumber :   10463
primeNumber :   10477
primeNumber :   10487
primeNumber :   10499
primeNumber :   printTime:    1006
10501
primeNumber :   10513
primeNumber :   10529
primeNumber :   10531
primeNumber :   10559
primeNumber :   10567
primeNumber :   10589
primeNumber :   10597
primeNumber :   10601
primeNumber :   10607
primeNumber :   10613
primeNumber :   10627
primeNumber :   10631
primeNumber :   10639
primeNumber :   10651
primeNumber :   10657
primeNumber :   10663
primeNumber :   10667
primeNumber :   10687
primeNumber :   10691
primeNumber :   10709
primeNumber :   10711
primeNumber :   10723
primeNumber :   10729
primeNumber :   10733
primeNumber :   10739
primeNumber :   10753
primeNumber :   10771
primeNumber :   10781
primeNumber :   10789
primeNumber :   10799
primeNumber :   10831
primeNumber :   10837
primeNumber :   10847
primeNumber :   10853
primeNumber :   10859
primeNumber :   10861
primeNumber :   10867
primeNumber :   10883
primeNumber :   10889
primeNumber :   10891
primeNumber :   10903
primeNumber :   10909
primeNumber :   10937
primeNumber :   10939
primeNumber :   10949
primeNumber :   10957
primeNumber :   10973
primeNumber :   10979
primeNumber :   10987
primeNumber :   10993
primeNumber :   11003
primeNumber :   11027
primeNumber :   11047
primeNumprintTime:    2011
ber :   11057
primeNumber :   11059
primeNumber :   11069
primeNumber :   11071
primeNumber :   11083
primeNumber :   11087
primeNumber :   11093
primeNumber :   11113
primeNumber :   11117
primeNumber :   11119
primeNumber :   11131
primeNumber :   11149
primeNumber :   11159
primeNumber :   11161
primeNumber :   11171
primeNumber :   11173
primeNumber :   11177
primeNumber :   11197
primeNumber :   11213
primeNumber :   11239
primeNumber :   11243
primeNumber :   11251
primeNumber :   11257
primeNumber :   11261
primeNumber :   11273
primeNumber :   11279
primeNumber :   11287
primeNumber :   11299
primeNumber :   11311
primeNumber :   11317
primeNumber :   11321
primeNumber :   11329
primeNumber :   11351
primeNumber :   11353
primeNumber :   11369
primeNumber :   11383
primeNumber :   11393
primeNumber :   11399
primeNumber :   11411
primeNumber :   11423
primeNumber :   11437
primeNumber :   11443
primeNumber :   11447
primeNumber :   11467
primeNumber :   11471
primeNumber :   11483
primeNumber :   11489
primeNumber :   11491
primeNumber :   11497
primeNumber :   11503
primeNumber :   11519
primeNumber :   11527
primeNumber :   11549
primeNumber :   11551
primeNumber :   11579
primeNumber :   11587
primeNumber :   11593
primeNumber :   11597
primeNumber :   11617
primeNumber :   11621
primeNumber :   11633
primeNumber :   11657
primeNumber :   11677
primeNumber :   11681
primeNumber :   11689
primeNumber :   11699
primeNumber :   11701
primeNumber :   11717
primeNumber :   11719
primeNumber :   11731
primeNumber :   11743
primeNumber :   11777
primeNumber :   11779
primeNumber :   11783
primeNumber :   11789
primeNumber :   11801
primeNumber :   11807
primeNumber :   11813
primeNumber :   11821
primeNumber :   11827
primeNumber :   11831
primeNumber :   11833
primeNumber :   11839
primeNumber :   11863
primeNumber :   11867
primeNumber :   11887
primeNumber :   11897
primeNumber :   11903
primeNumber :   11909
primeNumber :   11923
primeNumber :   11927
primeNumber :   11933
primeNumber :   11939
primeNumber :   11941
primeNumber :   11953
primeNumber :   11959
primeNumber :   11969
primeNumber :   11971
primeNumber :   11981
primeNumber :   11987
primeNumber :   12007
primeNumber :   12011
primeNumber :   12037
primeNumber :   12041
primeNumber :   12043
primeNumber :   12049
primeNumber :   12071
primeNumber :   12073
primeNumber :   12097
primeNumber :   12101
primeNumber :   12107
primeNumber :   12109
primeNumber :   12113
primeNumber :   12119
primeNumber :   12143
primeNumber :   12149
primeNumber :   12157
primeNumber :   12161
primeNumber :   12163
primeNumber :   12197
primeNumber :   12203
primeNumber :   12211
primeNumber :   12227
primeNumber :   12239
primeNumber :   12241
primeNumber :   12251
primeNumber :   12253
primeNumber :   12263
primeNumber :   12269
primeNumber :   12277
primeNumber :   12281
primeNumber :   12289
primeNumber :   12301
primeNumber :   12323
primeNumber :   12329
primeNumber :   12343
primeNumber :   12347
primeNumber :   12373
primeNumber :   12377
primeNumber :   12379
primeNumber :   12391
primeNumber :   12401
primeNumber :   12409
primeNumber :   12413
primeNumber :   12421
primeNumber :   12433
primeNumber :   12437
primeNumber :   12451
primeNumber :   12457
primeNumber :   12473
primeNumber :   12479
primeNumber :   12487
primeNumber :   12491
primeNumber :   12497
primeNumber :   12503
primeNumber :   12511
primeNumber :   12517
primeNumber :   12527
primeNumber :   12539
primeNumber :   12541
primeNumber :   12547
primeNumber :   12553
primeNumber :   12569
primeNumber :   12577
primeNumber :   12583
primeNumber :   12589
primeNumber :   12601
primeNumber :   12611
primeNumber :   12613
primeNumber :   12619
primeNumber :   12637
primeNumber :   12641
primeNumber :   12647
primeNumber :   12653
primeNumber :   12659
primeNumber :   12671
primeNumber :   12689
primeNumber :   12697
primeNumber :   12703
primeNumber :   12713
primeNumber :   12721
primeNumber :   12739
primeNumber :   12743
primeNumber :   12757
primeNumber :   12763
primeNumber :   12781
primeNumber :   12791
primeNumber :   12799
primeNumber :   12809
primeNumber :   12821
primeNumber :   12823
primeNumber :   12829
primeNumber :   12841
primeNumber :   12853
primeNumber :   12889
primeNumber :   12893
primeNumber :   12899
primeNumber :   12907
primeNumber :   12911
primeNumber :   12917

*/