@echo off
REM Compile Default it's g++, support for clang (clang+)
set COMPILER=g++
set NAME_OUTPUT=jgw
set OUTPUT_FOLDER=out
set OUTPUT_SRC=out_src
REM if you won't in release mode remove -D_DEV
set FLAGS_COMPILE_OUT=-D_DEV
set LIST_FILE=app/worker/util.cpp app/worker/helper.cpp src/jgw_controller.cpp app/worker/frequency.cpp system/windows/sound.cpp src/jgw_play.cpp app/worker/fileshelp.cpp src/jgw_compile.cpp src/jgw_compile_wav.cpp system/windows/jgw_compile_exec.cpp system/windows/jgw_compile_cpp.cpp app/worker/ccm.cpp app/worker/ls.cpp app/worker/pwd.cpp app/worker/color.cpp app/worker/exec1.cpp app/worker/exec2.cpp app/worker/exit.cpp app/worker/cd.cpp app/worker/clear.cpp
set LIST_SRC=*.o

if exist %OUTPUT_FOLDER%\ (
  echo Folder %OUTPUT_FOLDER% it's exist
) else (
  mkdir %OUTPUT_FOLDER%
)

if exist %OUTPUT_SRC%\ (
  echo Folder %OUTPUT_SRC% it's exist
) else (
  mkdir %OUTPUT_SRC%
)

(for %%a in (%LIST_FILE%) do (
   echo Compile File: %%a
   %COMPILER% -O1 -g -c %FLAGS_COMPILE_OUT% %%a
))

echo Compile1 to binary name %OUTPUT_FOLDER%/%NAME_OUTPUT%.exe
%COMPILER% -g -O2 %LIST_SRC% -o %NAME_OUTPUT%.exe

echo Compile2 to shared library name lib/libjgw.dll
%COMPILER% -DBUILD_LIBRARY_JGW -g -O2 -Wall -fPIC -shared -ffast-math src/jgw_library.cpp -o lib/libjgw.dll -Wl,--out-implib,lib/libjgw.a

move %NAME_OUTPUT%.exe %OUTPUT_FOLDER%
move *.o %OUTPUT_SRC%
