@echo off

REM 4100: unreferenced parameter
REM 4189: initialized but not referenced


set PROJ=Kalm2D

set CommonCompilerFlags= -nologo -WX -O2 -Oi -Gm -GR -W4 -WX -Zi -Zo -wd4100 -wd4189 -I:%PROJ%\include
set CommonCompilerFlags= -DGLEW_STATIC -DKALM2D_WIN32=1 %CommonCompilerFlags%
set CommonLinkerFlags= /LIBPATH:%PROJ%\lib -incremental:no user32.lib gdi32.lib winmm.lib kernel32.lib opengl32.lib glfw3dll.lib /NoDEFAULTLIB:msvcrt.lib

set SRC= %PROJ%\src

REM IF NOT EXIST build\ mkdir build\

REM del *.pdb > NUL 2> NUL

cl %CommonCompilerFlags% %src%\win_main.cpp %src%\kalm2d.cpp %src%\glad.c /link %CommonLinkerFlags% -out:Kalm2D.exe

popd
