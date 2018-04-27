@echo off

REM 4100: unreferenced parameter
REM 4189: initialized but not referenced
REM EHsc: unwind semantics for C++ exceptions


set PROJ=Kalm2D

set CommonCompilerFlags= -nologo -WX -O2 -Oi -Gm -GR -W4 -WX -Zi -Zo -EHsc -wd4100 -wd4189 -I:%PROJ%\include
set CommonCompilerFlags= -DKALM2D_WIN32=1 -DK_ASSERT=1 %CommonCompilerFlags%
set CommonLinkerFlags= /LIBPATH:%PROJ%\lib -incremental:no user32.lib gdi32.lib winmm.lib kernel32.lib /NoDEFAULTLIB:msvcrt.lib

set SRC= %PROJ%\src

REM IF NOT EXIST build\ mkdir build\

REM del *.pdb > NUL 2> NUL

cl %CommonCompilerFlags% %src%\kalm2d.cpp -FmKalm2D.map /LD /DLL /link %CommonLinkerFlags% opengl32.lib glfw3dll.lib -out:Game64.dll -EXPORT:GetGameAPI
cl %CommonCompilerFlags% %src%\win_main.cpp -Fmwin_main.map /link %CommonLinkerFlags% -out:Kalm2D.exe 

popd
