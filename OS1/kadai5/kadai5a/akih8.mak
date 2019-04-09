# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  サンプルプログラム                              
#    メイクファイル（日立 H8300H  秋月Cコンパイラ版）                         
#                                                                             
#                                   Copyright (C) 1998-2002 by Project HOS    
#                                   http://sourceforge.jp/projects/hos/       
# --------------------------------------------------------------------------- 



# Borland-C++ Ver 5.5 付属 make にて動作確認しています。
# system.cfg のプリプロセッサ処理にも Borland-C++ Ver 5.5 を利用しています。

#ユーザプログラムのソースファイル名
USRSRC = sample.c


# パス
INCH8DIR = \Progra~1\h8v2\include			# Cコンパイラの設定にあわせて書き換えてください
H8CC     = \Progra~1\h8v2\bin
HOSROOT  = \hos_v4
INCDIR   = $(HOSROOT)\include
LIBDIR   = $(HOSROOT)\lib\h83\akih8


# ツール
CC     = $(H8CC)\ch38
CPP    = \hos_v4\tool\cpp32.exe				# BC55 のプリプロセッサを利用
ASM    = $(H8CC)\asm38
LINK   = $(H8CC)\lnk
OBJCNV = $(H8CC)\cnvs
CFG    = \hos_v4\config\hos4cfg.exe


# オプション
CFLAGS   = -CPU=300HA -INCLUDE=$(INCH8DIR),$(INCDIR)
CPPFLAGS = -P-
AFLAGS   = 
LFLAGS   = 

# ターゲット
TARGET = $(USRSRC:.c=.mot)

#インクルードファイル
INCS = kernel_id.h $(USRSRC:.c=.h) MinSys3069.h

# オブジェクトファイル
OBJS = vector.obj crt0.obj MinSys3069.obj kernel_cfg.obj $(USRSRC:.c=.obj)


# ライブラリ生成
$(TARGET): $(OBJS) link.sub
	$(LINK) /SUB=link.sub
	$(OBJCNV) $(USRSRC:.c=.abs) $(TARGET)


# オブジェクト生成
kernel_cfg.obj: kernel_cfg.c $(INCS)
	$(CC) $(CFLAGS) kernel_cfg.c

vector.obj: vector.src
	$(ASM) $(AFLAGS) vector.src

crt0.obj: crt0.src
	$(ASM) $(AFLAGS) crt0.src

$(USRSRC:.c=.obj): sample.c $(INCS)
	$(CC) $(CFLAGS) $(USRSRC)

MinSys3069.obj: MinSys3069.c $(INCS)
	$(CC) $(CFLAGS) MinSys3069.c

kernel_cfg.c kernel_id.h: system.cfg
	$(CPP) $(CPPFLAGS) -osystem.i system.cfg
	$(CFG) system.i


# クリーンナップ
clean:
	-del *.i
	-del *.abs
	-del *.obj
	-del kernel_cfg.c
	-del kernel_id.h
	-del $(TARGET)



# --------------------------------------------------------------------------- 
#  Copyright (C) 1998-2002 by Project HOS                                     
# --------------------------------------------------------------------------- 
