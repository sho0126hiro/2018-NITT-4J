rem ------------------------------------------------------------------------
rem H8�̃��j�^��Ŏ��s������K�p�\�[�X�t�@�C������MOT�t�@�C�������܂�
rem H8C�R���p�C��ver2�̃Z�b�g�ɑΉ����Ă��܂��B
rem ASM�̃\�[�X�t�@�C���̃h���b�O���h���b�v�ɑΉ�
rem ------------------------------------------------------------------------

@echo off
echo Assemble, link and convert command for H8 ASM-programing with V2 ver1.00
echo Copyright(c) 29June2006 T.kosaka CS TNCT
REM Copyright(c) 9Dec2002 T.kosaka CS TNCT

rem �J�����g�h���C�u�E�J�����g�f�B���N�g���ֈړ�
%~d1
cd %~p1

rem �R���p�C���̃p�X�̐ݒ�
path=%path%;%HOMEDRIVE%\Program Files\h8v2\bin
set h8inc=%HOMEDRIVE%\Progra~1\h8v2\include
set h8lib=%HOMEDRIVE%\Progra~1\h8v2\lib

rem ������t�@�C�����h���b�v���ꂽ���C�P�Ȃ�_�u���N���b�N�ŋN�������ꍇ�͉������Ȃ�
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
rem S�t�H�[�}�b�g�ɕϊ� �`.mot�̍쐬
cnvs %~n1.abs
del %~n1.abs
del %~n1.obj
ren %~n1.MOT %~n11.MOT
rem echo on
%~d0%~p0two2neg.exe <%~n11.MOT >%~n1.MOT
del %~n11.MOT

goto TERMINAL

:NO_SOURCE_ERROR
echo *** error *** ASM�̃\�[�X�t�@�C�����w�肳��Ă��܂���B
goto TERMINAL

:ASM_ERROR
echo *** error *** �R���p�C���G���[������܂����B
goto TERMINAL

:LINK_ERROR
echo *** error *** �����N�G���[�ł��B
goto TERMINAL

:TERMINAL
echo Pushing any key leads the exit.
pause >nul
exit
