@echo off

set WindowsLib=opengl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib

:: to add a library include append /I ../libs/<library include folder> to the following line: 
set IncludeDirs=/I ../lib/raylib_64_msvc/include
:: to add a library, just append the location of the .lib file you need onto this line:
set Libraries=../lib/raylib_64_msvc/lib/raylib_static.lib %WindowsLib% 

mkdir ./bin/
cd ./bin
:: /MD is IMPORTANT, wont use GLFW without it.
cl ../src/build.c /Zi /Fe%cd%/Oven /MD %IncludeDirs% %Libraries% /link
cd ..
