rem *********************************************************
rem TeraTermPro.exe��COM1�ɐڑ����ꂽH8�}�C�R���p�ɋN������
rem teratermpro�̃f�B���N�g�����ɂ̓o�[�W�����ԍ����܂܂�邪
rem ����������I�ɒT���o���悤�ɂ��Ă���B
rem �܂�COM1�ɐڑ����ꂽH8�}�C�R���ւ�teraterm�̐ݒ�͂��炩
rem �쐬����Ă�����̂Ƃ���B�ݒ�t�@�C�����͈ȉ��ɋL�q
rem *********************************************************

rem ------teraterm�̏����ݒ�t�@�C�����̐ݒ�
set ini_fname=h8_monitor.INI

if exist "C:\Program Files (x86)" goto sys64
  set pfdir="C:\Program Files\
  goto sysok
:sys64
  set pfdir="C:\Program Files (x86)\
:sysok

rem dir %pfdir%teraterm*" /b

rem �g���b�L�[�����C���ϐ�CURRENTTTERM��ݒ肷��

for /F %%i in ( 'dir %pfdir%teraterm*" /b ^| find "teraterm"' ) do (
	rem echo %%i
	set CURRENTTTERM=%%i
)
rem echo CURRENTTTERM
start "" %pfdir%%CURRENTTTERM%\ttermpro.exe" /F=%ini_fname%
