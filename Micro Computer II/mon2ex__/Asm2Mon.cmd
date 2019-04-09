rem ------------------------------------------------------------------------
rem H8のモニタ上で実行する実習用ソースファイルからMOTファイルを作ります
rem H8Cコンパイラver2のセットに対応しています。
rem ASMのソースファイルのドラッグ＆ドロップに対応
rem ------------------------------------------------------------------------

@echo off
echo Assemble, link and convert command for H8 ASM-programing with V2 ver1.00
echo Copyright(c) 29June2006 T.kosaka CS TNCT
REM Copyright(c) 9Dec2002 T.kosaka CS TNCT

rem カレントドライブ・カレントディレクトリへ移動
%~d1
cd %~p1

rem コンパイラのパスの設定
path=%path%;%HOMEDRIVE%\Program Files\h8v2\bin
set h8inc=%HOMEDRIVE%\Progra~1\h8v2\include
set h8lib=%HOMEDRIVE%\Progra~1\h8v2\lib

rem 誤ったファイルがドロップされたか，単なるダブルクリックで起動した場合は何もしない
if exist %~n1.src goto ASSEMBLE
if exist %~n1.mar goto ASSEMBLE
goto NO_SOURCE_ERROR

:ASSEMBLE
asm38 %~n1.src -so -cr -list
if not exist %~n1.obj goto ASM_ERROR

:LINK
rem ----------------------------------------------------------------------------
lnk %~n1 -PRINT=%~n1  >q9j2h5c4k6b1.txt
type q9j2h5c4k6b1.txt
find "**" q9j2h5c4k6b1.txt >nul
if errorlevel 1 goto CONVERT
del q9j2h5c4k6b1.txt
if exist %~n1.abs del %~n1.abs
goto LINK_ERROR

:CONVERT
del q9j2h5c4k6b1.txt
rem ----------------------------------------------------------------------------
rem Sフォーマットに変換 ～.motの作成
cnvs %~n1.abs
del %~n1.abs
del %~n1.obj
ren %~n1.MOT %~n11.MOT
rem echo on
%~d0%~p0two2neg.exe <%~n11.MOT >%~n1.MOT
del %~n11.MOT

goto TERMINAL

:NO_SOURCE_ERROR
echo *** error *** ASMのソースファイルが指定されていません。
goto TERMINAL

:ASM_ERROR
echo *** error *** コンパイルエラーがありました。
goto TERMINAL

:LINK_ERROR
echo *** error *** リンクエラーです。
goto TERMINAL

:TERMINAL
echo Pushing any key leads the exit.
pause >nul
exit
