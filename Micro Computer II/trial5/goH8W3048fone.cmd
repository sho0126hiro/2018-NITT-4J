
rem カレントドライブ・カレントディレクトリへ移動
%~d1
cd %~p1

rem フラッシュメモリ書き込みに使用するプログラム
set downloader="C:\Program Files\h8v2\WRITER\H8W\h8w.exe" -GO .\myAutoPgm.ini
rem ★フラッシュメモリ書き込みのためのCOMポート番号を設定します
set ComPortNumber=1

echo [AutoPgm] >myAutoPgm.ini
echo AutoStart=1 >>myAutoPgm.ini
echo AutoExit=1 >>myAutoPgm.ini
echo CtrlProgam=3048B_F25M_P384.MOT >>myAutoPgm.ini
echo ComPortNo=%ComPortNumber% >>myAutoPgm.ini
echo UserMotPath=%1 >>myAutoPgm.ini
echo on
%downloader% 
@echo off
del myAutoPgm.ini
