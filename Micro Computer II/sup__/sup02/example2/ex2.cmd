rem カレントドライブ・カレントディレクトリへ移動
%~d1
cd %~p1

rem コンパイラのパスの設定など
path=%path%;%HOMEDRIVE%\Program Files\h8v2\bin
set h8inc=%HOMEDRIVE%\Progra~1\h8v2\include
set h8library=%HOMEDRIVE%\Progra~1\h8v2\lib\c38ha.lib

rem コンパイル＆アッセンブル
ch38 -cpu=300ha -include=%h8inc% -OUTCODE=SJIS -CODE=ASMCODE ex2.c
asm38 ex2.src
asm38 start00.src

ren ex2.src ex2.src0
find /v ";***" ex2.src0 >ex2.src

rem リンク
lnk start00.OBJ ex2.OBJ -subcommand=ex2.sub -LIB=%h8library% -O=ex2 -P=ex2

rem Sフォーマットに変換 ～.motの作成
cnvs ex2.abs

echo h8w.exe
echo [AutoPgm] >myAutoPgm.ini
echo AutoStart=1 >>myAutoPgm.ini
echo AutoExit=1 >>myAutoPgm.ini
echo CtrlProgam=3048B_F25M_P384.MOT >>myAutoPgm.ini
echo ComPortNo=1 >>myAutoPgm.ini
echo UserMotPath=ex2.mot >>myAutoPgm.ini
"C:\Program Files\h8v2\WRITER\H8W\h8w.exe" -GO .\myAutoPgm.ini
del myAutoPgm.ini
pause
