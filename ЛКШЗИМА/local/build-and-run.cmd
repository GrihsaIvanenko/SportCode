SET DIR=%~dp0
set CPP=%1
set BASE=%~n1
set EXE=%BASE%.exe
set PARUNNER=parunner.exe

echo g++ -O2 -std=gnu++17 -lm -static  -I%DIR%\lib -I%DIR% %DIR%\lib\zeus_local.o %DIR%\lib\message_internal.o %CPP% -o %EXE%

echo %DIR%\parunner.exe --n 2 --stdout tagged --stderr tagged %EXE%

