@echo off

REM -WX: treat warnings as errors
REM 4100: unreferenced parameter
REM 4189: initialized but not referenced
REM EHsc: unwind semantics for C++ exceptions


set PROJ=Kalm2D

set CommonCompilerFlags= -nologo -WX -Oi -Gm -GR -W4 -Zi -Zo -EHsc -wd4100 -wd4189 -I:%PROJ%\include
set CommonCompilerFlags= -DKALM2D_WIN32=1 -DK_ASSERT=1 %CommonCompilerFlags%
set CommonLinkerFlags= /nologo /LIBPATH:%PROJ%\lib -incremental:no user32.lib gdi32.lib winmm.lib kernel32.lib /NODEFAULTLIB:msvcrt.lib -MACHINE:x64

set SRC= %PROJ%\src

REM IF NOT EXIST build\ mkdir build\

REM del *.pdb > NUL 2> NUL

cl %CommonCompilerFlags% %src%\win_Kalm2D.cpp -Fm /link %CommonLinkerFlags% -out:Kalm2D.exe
REM lib -nologo win_Kalm2D.obj /DEF
cl %CommonCompilerFlags% %src%\kGame2D.cpp -Fm /LD /DLL /link %CommonLinkerFlags% opengl32.lib glfw3dll.lib -EXPORT:GetGameAPI -out:Game64.dll 
REM link %CommonLinkerFlags% kGame2D.obj opengl32.lib glfw3dll.lib win_Kalm2D.lib win_Kalm2D.obj win_Kalm2D.exp

popd
