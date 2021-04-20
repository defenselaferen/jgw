@echo off
REM command in this script will be hidden

REM Compile Default it's g++, support for clang (clang+)
set COMPILER=g++

REM Variable For output file executable
set NAME_OUTPUT=jgw

REM Variable For output file executable in this variable directory
set OUTPUT_FOLDER=out

REM Variable For output file object (.o) in this variable directory
set OUTPUT_SRC=out_src

REM This variable for flags in compile to out into file object
REM if you won't in release mode remove -D_DEV
set FLAGS_COMPILE_OUT=-O3 -D_DEV

REM Array Files In C++ (array<String>)
set LIST_FILE=app/worker/util.cpp app/worker/helper.cpp src/jgw_controller.cpp app/worker/frequency.cpp system/windows/sound.cpp src/jgw_play.cpp app/worker/fileshelp.cpp src/jgw_compile.cpp src/jgw_compile_wav.cpp

REM Automatically All File Object Into Executable File
set LIST_SRC=*.o

REM Check OUTPUT FILE
if exist %OUTPUT_FOLDER%\ (
  echo Folder %OUTPUT_FOLDER% it's exist
) else (
  mkdir %OUTPUT_FOLDER%
)

REM Check OUTPUT FILE SRC
if exist %OUTPUT_SRC%\ (
  echo Folder %OUTPUT_SRC% it's exist
) else (
  mkdir %OUTPUT_SRC%
)

REM Compile All Source Into Object File
(for %%a in (%LIST_FILE%) do (
   echo Compile File: %%a
   %COMPILER% -c %FLAGS_COMPILE_OUT% %%a
))

REM End Compile Compile Into file executable
echo Compile to binary name %OUTPUT_FOLDER%/%NAME_OUTPUT%.exe
%COMPILER% -O3 %LIST_SRC% -o %NAME_OUTPUT%.exe

REM Move all file into directory
move %NAME_OUTPUT%.exe %OUTPUT_FOLDER%
move *.o %OUTPUT_SRC%
