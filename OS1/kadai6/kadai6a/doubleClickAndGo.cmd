@echo off
%~d0
cd %~p0
rem *************** カスタマイズ領域 begin *******************
rem ★作業結果ファイルを残すかどうかを設定します。
rem どちらか片方をremにします
 set leaveFiles=YES
 rem set leaveFiles=NO
rem ★フラッシュメモリ書き込みのためのCOMポート番号を設定します
 set ComPortNumber=1
rem *************** カスタマイズ領域  end  *******************

rem フラッシュメモリ書き込みに使用するプログラム
set downloader="C:\Program Files\h8v2\WRITER\H8W\h8w.exe"

del *.mot
echo on
set doit=YES
\hos_v4\tool\make -f akih8.mak
@echo off
if ERRORLEVEL 1 set doit=NO
if %doit%==NO goto TERMINAL

:SEARCHMOT
set doit=NO
set motfile=
for %%f in (*.mot) do set doit=YES && set motfile=%%f
if %doit%==YES goto DOWNLOAD
goto TERMINAL

:DOWNLOAD
echo [AutoPgm] >myAutoPgm.ini
echo AutoStart=1 >>myAutoPgm.ini
echo AutoExit=1 >>myAutoPgm.ini
echo BaudB=19200 >>myAutoPgm.ini
echo BaudP=38400 >>myAutoPgm.ini
echo CtrlProgam=3069_F20M_P576.INF >>myAutoPgm.ini
echo ComPortNo=%ComPortNumber% >>myAutoPgm.ini
echo UserMotPath=%motfile% >>myAutoPgm.ini
echo on
%downloader% -GO .\myAutoPgm.ini
@echo off
if %ERRORLEVEL%==0 echo succeeded in MOT file writing
if not %ERRORLEVEL%==0 echo failed in writing
del myAutoPgm.ini

:TERMINAL
@echo off
if exist *.lst del *.lst
if exist *.i del *.i
if exist *.abs del *.abs
if exist *.obj del *.obj
if %leaveFiles%==YES goto SKIPPOINT
if exist kernel*.* del kernel*.*
if exist *.map del *.map
if exist *.mot del *.mot
:SKIPPOINT
echo Pushing any key leads the exit.
pause >nul
exit

