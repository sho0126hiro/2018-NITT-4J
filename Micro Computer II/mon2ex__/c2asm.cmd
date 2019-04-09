path=%path%;c:\Progra~1\h8v2\bin
set h8inc=c:\Progra~1\h8v2\include
set h8lib=c:\Progra~1\h8v2\lib
%~d1
cd %~p1
ch38 -cpu=300ha -include=%h8inc% -CODE=ASMCODE -OUTCODE=SJIS %~n1.c
findstr /V ";***"  %~n1.src > %~n1_1.src
pause
