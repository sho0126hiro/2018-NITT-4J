rem *********************************************************
rem TeraTermPro.exeをCOM1に接続されたH8マイコン用に起動する
rem teratermproのディレクトリ名にはバージョン番号が含まれるが
rem それを自動的に探し出すようにしている。
rem またCOM1に接続されたH8マイコンへのteratermの設定はあらか
rem 作成されているものとする。設定ファイル名は以下に記述
rem *********************************************************

rem ------teratermの初期設定ファイル名の設定
set ini_fname=h8_monitor.INI

if exist "C:\Program Files (x86)" goto sys64
  set pfdir="C:\Program Files\
  goto sysok
:sys64
  set pfdir="C:\Program Files (x86)\
:sysok

rem dir %pfdir%teraterm*" /b

rem トリッキーだが，環境変数CURRENTTTERMを設定する

for /F %%i in ( 'dir %pfdir%teraterm*" /b ^| find "teraterm"' ) do (
	rem echo %%i
	set CURRENTTTERM=%%i
)
rem echo CURRENTTTERM
start "" %pfdir%%CURRENTTTERM%\ttermpro.exe" /F=%ini_fname%
