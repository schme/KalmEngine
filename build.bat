@echo off

REM -WX: treat warnings as errors
REM 4100: unreferenced parameter
REM 4189: initialized but not referenced
REM 4458: declaration hides class member
REM 4201: anonymous structs
REM 4505: unreferenced local function removed
REM EHsc: unwind semantics for C++ exceptions

set PROJ=KalmEngine

REM Compiling tinyply 
set CommonCompilerFlags= -nologo -WX -Oi -Gm -GR -W4 -Zi -Zo -EHsc -wd4100 -wd4189 -wd4458 -wd4201 -wd4505 /I\%PROJ%\include\
set CommonCompilerFlags= -DKALM2D_WIN32=1 -DK_ASSERT=1 %CommonCompilerFlags%
set CommonLinkerFlags= /nologo /LIBPATH:%PROJ%\lib\ -incremental:no user32.lib gdi32.lib winmm.lib kernel32.lib /NODEFAULTLIB:msvcrt.lib -MACHINE:x64

REM 4267: type conversion, possible loss of data
REM TODO(Kasper): Don't just ignore C4267, fix the source instead
set TinyPlyFlags= -nologo -WX -Oi -Gm -GR -W3 -Zi -Zo -EHsc -wd4267

set SRC= %PROJ%\src

rem TINYPLY -- Heavy as heck to compile, avoid when possible
rem cl -c %TinyPlyFlags% tinyply\tinyply.cpp -Fm
rem GLAD
rem cl -c %CommonCompilerFlags% glad\glad.c -Fm

rem EXE
cl %CommonCompilerFlags% %src%\Sys_Kalm.cpp -Fm /link %CommonLinkerFlags% opengl32.lib glfw3dll.lib glad.obj tinyply.obj -out:Kalm.exe

rem GAME DLL
cl %CommonCompilerFlags% %src%\KalmGame.cpp -Fm /LD /link %CommonLinkerFlags% -EXPORT:GetGameAPI -out:Game64.dll
