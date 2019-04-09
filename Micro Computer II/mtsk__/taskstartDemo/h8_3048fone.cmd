@echo off
echo Compile, link and convert command for H8 C-programing with V2 ver1.00
echo Copyright(c) 23Jan2004 T.kosaka CS TNCT
echo Copyright(c) 28Jun2002 T.kosaka CS TNCT

rem H8C�R���p�C��ver2�̃Z�b�g�ɑΉ����Ă��܂��B
rem C�̃\�[�X�t�@�C�������obj�t�@�C���͍ő��5�܂Ńh���b�O���h���b�v�ɑΉ�
rem �����t�@�C���̃h���b�v�̏ꍇ�͎��̂��ƂɋC�����邱��
rem �I������Ă���t�@�C���̂����t�H���_�\���ōł���̗�i���̗�ɕ����̃t�@�C��������ꍇ�͍��[�j
rem �ɂ���t�@�C�����Ńt���b�V���������������݌`���t�@�C���̖��O�����܂�B���̂���main()�����t�@�C��������
rem �ʒu�ɒu���Ɨǂ��B
rem MOT�t�@�C�����h���b�O���h���b�v����Ƃ����t���b�V���������������݂��n�܂�B

rem *************** �J�X�^�}�C�Y�̈� begin *******************
rem ���R���p�C����ƂɕK�v�ȃp�X�̒ǉ����s���܂��B
 set mypath=%HOMEDRIVE%\Program Files\h8v2\bin
rem ���X�^�[�g�A�b�v���[�`�����L�q���܂��B
 set startuproutine=%HOMEDRIVE%\Progra~1\h8v2\lib\start3048.obj
rem ��H8�̃��C�u�������w�肵�܂��B
 set h8library=%HOMEDRIVE%\Progra~1\h8v2\lib\c38ha.lib
rem ���t���b�V���������������ݒ��O�Ƀ|�[�Y���Ă��̂܂܃t���b�V���������������݂��邩�ǂ����₢���킹���܂�
rem YES:�₢���킹��@NO:�₢���킹�Ȃ�
 set downloadready=NO
rem ���t���b�V���������������݂̂��߂�COM�|�[�g�ԍ���ݒ肵�܂�
 set ComPortNumber=1
rem ������Ƀt���b�V���������������݂��I�������ꍇ�͂��̂܂܏I������
rem YES:���̂܂܏I������@NO:���̂܂܏I��������~
 set downloadquit=NO
rem *************** �J�X�^�}�C�Y�̈�  end  *******************

rem ----------------------------------------------------------------------------
rem �J�����g�h���C�u�E�J�����g�f�B���N�g���ֈړ�
%~d1
cd %~p1

rem �R���p�C���̃p�X�̐ݒ�
path=%path%;%mypath%
set h8inc=%HOMEDRIVE%\Progra~1\h8v2\include
set h8lib=%HOMEDRIVE%\Progra~1\h8v2\lib

rem ����MOT�t�@�C�����h���b�O���h���b�v���ꂽ��C�t���b�V���������������݂����s�Ȃ�
if %~x1==.mot goto DOWNLOAD
if %~x1==.MOT goto DOWNLOAD

rem ������t�@�C�����h���b�v���ꂽ���C�P�Ȃ�_�u���N���b�N�ŋN�������ꍇ�͉������Ȃ�
if exist %~n1.obj goto COMPILE
if not exist %~n1.c goto NO_SOURCE_ERROR

:COMPILE
rem ----------------------------------------------------------------------------
rem �R���p�C���@�`.obj�̍쐬 5�̃t�@�C�����͂ɑΉ�
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if exist %%p.obj del %%p.obj
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c ch38 -cpu=300ha -include=%h8inc% -OUTCODE=SJIS -CODE=ASMCODE %%p 
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if exist %%p.src del %%p.lst
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if not exist %%p.src goto COMPILE_ERROR
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c asm38 %%p 
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if not exist %%p.obj goto COMPILE_ERROR
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if exist %%p.src del %%p.src

:LINK

rem �����N�@�`.abs�̍쐬
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
rem S�t�H�[�}�b�g�ɕϊ� �`.mot�̍쐬
cnvs %~n1.abs
del %~n1.abs
echo;

rem mot�t�@�C���̓]��
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
echo *** error *** �b�̃\�[�X�t�@�C�����w�肳��Ă��܂���B
goto TERMINAL

:COMPILE_ERROR
for %%p in (%~n1 %~n2 %~n3 %~n4 %~n5 ) do if exist %%p.c if exist %%p.obj del %%p.obj
echo *** error *** �R���p�C���G���[������܂����B
goto TERMINAL

:LINK_ERROR
echo *** error *** �����N�G���[�ł��B
goto TERMINAL

:TERMINAL
echo Pushing any key leads the exit.
pause >nul
exit
