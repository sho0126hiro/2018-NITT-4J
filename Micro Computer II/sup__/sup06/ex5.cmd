rem カレントドライブ・カレントディレクトリへ移動
%~d1
cd %~p1

rem コンパイラのパスの設定など
path=%path%;%HOMEDRIVE%\Program Files\h8v2\bin
set h8inc=%HOMEDRIVE%\Progra~1\h8v2\include
set h8library=%HOMEDRIVE%\Progra~1\h8v2\lib\c38ha.lib

rem コンパイル＆アッセンブル
ch38 -cpu=300ha -include=%h8inc% -OUTCODE=SJIS -CODE=ASMCODE dumpMemoy.c
ren dumpMemoy.lst dumpMemoy_c.lst
asm38 dumpMemoy.src -so -cr -list
asm38 start01.src -so -cr -list

ren dumpMemoy.src dumpMemoy.src0
find /v ";***" dumpMemoy.src0 >dumpMemoy.src

rem リンク
lnk start01.OBJ dumpMemoy.OBJ -subcommand=ex4.sub -LIB=%h8library% -O=dumpMemoy -P=dumpMemoy

rem Sフォーマットに変換 ～.motの作成
cnvs dumpMemoy.abs

echo h8w.exe
echo [AutoPgm] >myAutoPgm.ini
echo AutoStart=1 >>myAutoPgm.ini
echo AutoExit=1 >>myAutoPgm.ini
echo CtrlProgam=3048B_F25M_P384.MOT >>myAutoPgm.ini
echo ComPortNo=1 >>myAutoPgm.ini
echo UserMotPath=dumpMemoy.mot >>myAutoPgm.ini
"C:\Program Files\h8v2\WRITER\H8W\h8w.exe" -GO .\myAutoPgm.ini
del myAutoPgm.ini
pause
