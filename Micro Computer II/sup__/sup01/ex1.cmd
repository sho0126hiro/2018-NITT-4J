rem �J�����g�h���C�u�E�J�����g�f�B���N�g���ֈړ�
%~d1
cd %~p1

rem �R���p�C���̃p�X�̐ݒ�Ȃ�
path=%path%;%HOMEDRIVE%\Program Files\h8v2\bin;
set h8inc=%HOMEDRIVE%\Progra~1\h8v2\include
set h8library=%HOMEDRIVE%\Progra~1\h8v2\lib\c38ha.lib

rem �R���p�C�����A�b�Z���u��
ch38 -cpu=300ha -include=%h8inc% -OUTCODE=SJIS -CODE=ASMCODE ex1.c
asm38 ex1.src
asm38 start00.src

ren ex1.src ex1.src0
find /v ";***" ex1.src0 >ex1.src

rem �����N
lnk start00.OBJ ex1.OBJ -subcommand=ex1.sub -LIB=%h8library% -O=ex1 -P=ex1

rem S�t�H�[�}�b�g�ɕϊ� �`.mot�̍쐬
cnvs ex1.abs

echo h8w.exe
echo [AutoPgm] >myAutoPgm.ini
echo AutoStart=1 >>myAutoPgm.ini
echo AutoExit=1 >>myAutoPgm.ini
echo CtrlProgam=3048B_F25M_P384.MOT >>myAutoPgm.ini
echo ComPortNo=1 >>myAutoPgm.ini
echo UserMotPath=ex1.mot >>myAutoPgm.ini
"C:\Program Files\h8v2\WRITER\H8W\h8w.exe" -GO .\myAutoPgm.ini
del myAutoPgm.ini
pause
