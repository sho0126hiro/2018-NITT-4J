# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  �T���v���v���O����                              
#    ���C�N�t�@�C���i���� H8300H  �H��C�R���p�C���Łj                         
#                                                                             
#                                   Copyright (C) 1998-2002 by Project HOS    
#                                   http://sourceforge.jp/projects/hos/       
# --------------------------------------------------------------------------- 



# Borland-C++ Ver 5.5 �t�� make �ɂē���m�F���Ă��܂��B
# system.cfg �̃v���v���Z�b�T�����ɂ� Borland-C++ Ver 5.5 �𗘗p���Ă��܂��B

#���[�U�v���O�����̃\�[�X�t�@�C����
USRSRC = sample.c


# �p�X
INCH8DIR = \Progra~1\h8v2\include			# C�R���p�C���̐ݒ�ɂ��킹�ď��������Ă�������
H8CC     = \Progra~1\h8v2\bin
HOSROOT  = \hos_v4
INCDIR   = $(HOSROOT)\include
LIBDIR   = $(HOSROOT)\lib\h83\akih8


# �c�[��
CC     = $(H8CC)\ch38
CPP    = \hos_v4\tool\cpp32.exe				# BC55 �̃v���v���Z�b�T�𗘗p
ASM    = $(H8CC)\asm38
LINK   = $(H8CC)\lnk
OBJCNV = $(H8CC)\cnvs
CFG    = \hos_v4\config\hos4cfg.exe


# �I�v�V����
CFLAGS   = -CPU=300HA -INCLUDE=$(INCH8DIR),$(INCDIR)
CPPFLAGS = -P-
AFLAGS   = 
LFLAGS   = 

# �^�[�Q�b�g
TARGET = $(USRSRC:.c=.mot)

#�C���N���[�h�t�@�C��
INCS = kernel_id.h $(USRSRC:.c=.h) MinSys3069.h

# �I�u�W�F�N�g�t�@�C��
OBJS = vector.obj crt0.obj MinSys3069.obj kernel_cfg.obj $(USRSRC:.c=.obj)


# ���C�u��������
$(TARGET): $(OBJS) link.sub
	$(LINK) /SUB=link.sub
	$(OBJCNV) $(USRSRC:.c=.abs) $(TARGET)


# �I�u�W�F�N�g����
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


# �N���[���i�b�v
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
