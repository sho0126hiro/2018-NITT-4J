@echo off
echo Compile, link and convert command for H8 C-programing with V2 ver1.00
echo Copyright(c) 23Jan2004 T.kosaka CS TNCT
echo Copyright(c) 28Jun2002 T.kosaka CS TNCT

rem H8Cコンパイラver2のセットに対応しています。
rem Cのソースファイルおよびobjファイルは最大で5個までドラッグ＆ドロップに対応
rem 複数ファイルのドロップの場合は次のことに気をつけること
rem 選択されているファイルのうちフォルダ表示で最も上の列（この列に複数のファイルがある場合は左端）
rem にあるファイル名でフラッシュメモリ書き込み形式ファイルの名前が決まる。そのためmain()を持つファイルをその
rem 位置に置くと良い。
rem MOTファイルをドラッグ＆ドロップするとすぐフラッシュメモリ書き込みが始まる。

rem *************** カスタマイズ領域 begin *******************
rem ★コンパイル作業に必要なパスの追加を行います。
 set mypath=%HOMEDRIVE%\Program Files\h8v2\bin
rem ★スタートアップルーチンを記述します。
 set startuproutine=%HOMEDRIVE%\Progra~1\h8v2\lib\start3048.obj
rem ★H8のライブラリを指定します。
 set h8library=%HOMEDRIVE%\Progra~1\h8v2\lib\c38ha.lib
rem ★フラッシュメモリ書き込み直前にポーズしてそのままフラッシュメモリ書き込みするかどうか問い合わせします
rem YES:問い合わせる　NO:問い合わせない
 set downloadready=NO
rem ★フラッシュメモリ書き込みのためのCOMポート番号を設定します
 set ComPortNumber=1
rem ★正常にフラッシュメモリ書き込みが終了した場合はそのまま終了する
rem YES:そのまま終了する　NO:そのまま終了せず停止
 set downloadquit=NO
rem *************** カスタマイズ領域  end  *******************

rem ----------------------------------------------------------------------------
rem カレントドライブ・カレントディレクトリへ移動
%~d1
cd %~p1

rem コンパイラのパスの設定
path=%path%;%mypath%
set h8inc=%HOMEDRIVE%\Progra~1\h8v2\include
set h8lib=%HOMEDRIVE%\Progra~1\h8v2\lib

rem もしMOTファイルがドラッグ＆ドロップされたら，フラッシュメモリ書き込みだけ行なう
if %~x1==.mot goto DOWNLOAD
if %~x1==.MOT goto DOWNLOAD

rem 誤ったファイルがドロップされたか，単なるダブルクリックで起動した場合は何もしない
if exist %~n1.obj goto COMPILE
if not exist %~n1.c goto NO_SOURCE_ERROR

:COMPILE
rem ----------------------------------------------------------------------------
rem コンパイル　～.objの作成 5個のファイル入力に対応
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if exist %%p.obj del %%p.obj
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c ch38 -cpu=300ha -include=%h8inc% -OUTCODE=SJIS -CODE=ASMCODE %%p 
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if exist %%p.src del %%p.lst
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if not exist %%p.src goto COMPILE_ERROR
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c asm38 %%p 
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if not exist %%p.obj goto COMPILE_ERROR
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if exist %%p.src del %%p.src

:LINK

rem リンク　～.absの作成
lnk %startuproutine% %~n1 %~n2 %~n3 %~n4 %~n5 -subcommand=h8_3048.sub -LIB=%h8library% -O=%~n1 -P=%~n1 >q9j2h5c4k6b1.txt
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if exist %%p.obj del %%p.obj
type q9j2h5c4k6b1.txt
find "**" q9j2h5c4k6b1.txt >nul
echo;
if errorlevel 1 goto CONVERT
del q9j2h5c4k6b1.txt
del %~n1.abs
goto LINK_ERROR

:CONVERT
del q9j2h5c4k6b1.txt
rem ----------------------------------------------------------------------------
rem Sフォーマットに変換 ～.motの作成
cnvs %~n1.abs
del %~n1.abs
echo;

rem motファイルの転送
if %downloadready%==NO goto DOWNLOAD
echo Please set AKI-H8 ready and hit any key / push 'Ctrl+C' if you want
pause >nul
:DOWNLOAD
echo h8w.exe
echo [AutoPgm] >myAutoPgm.ini
echo AutoStart=1 >>myAutoPgm.ini
echo AutoExit=1 >>myAutoPgm.ini
echo CtrlProgam=3048B_F25M_P384.MOT >>myAutoPgm.ini
echo ComPortNo=%ComPortNumber% >>myAutoPgm.ini
echo UserMotPath=%~n1.mot >>myAutoPgm.ini
"C:\Program Files\h8v2\WRITER\H8W\h8w.exe" -GO .\myAutoPgm.ini
if %ERRORLEVEL%==0 echo succeeded in MOT file writing
if not %ERRORLEVEL%==0 echo failed in writing
del myAutoPgm.ini
rem if exist %~n1.map del %~n1.map
if %downloadquit%==YES exit
goto TERMINAL

:NO_SOURCE_ERROR
echo *** error *** Ｃのソースファイルが指定されていません。
goto TERMINAL

:COMPILE_ERROR
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if exist %%p.obj del %%p.obj
echo *** error *** コンパイルエラーがありました。
goto TERMINAL

:LINK_ERROR
echo *** error *** リンクエラーです。
goto TERMINAL

:TERMINAL
echo Pushing any key leads the exit.
pause >nul
exit
