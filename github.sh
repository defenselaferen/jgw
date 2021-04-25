# !IMPORTANT
# This file for Linux in (Debian Or Ubuntu)

# color in compile
GREEN="\033[0;32m" # color green
RED="\033[0;31m" # color red
NC="\033[0m" # color reset

# check dependencis
if [ -d "/usr/include/SDL2/" ] 
then
    # if dependencis for linux user it's already.
    printf "${GREEN} Dependencis already${NC}\n"
else
    # check connection of user
    wget -q --tries=10 --timeout=20 --spider http://google.com
    if [[ $? -eq 0 ]]; then  
        sudo apt install libsdl2-dev -y # installing automatically lib dependencis
    else
        printf "${RED}Please Using: ${GREEN}Internet${NC}\n" # If user not using connection in user computer.
        exit 1
    fi
fi

# settings all variable in this
COMPILE="g++" # default compile: g++, support for clang (clang+)

# check compiler
if [ -d "/usr/bin/$COMPILE" ] 
then
  printf "Compiler: ${GREEN}${COMPILER}${NC} It's Exist\n"
else
  # check connection of user
  wget -q --tries=10 --timeout=20 --spider http://google.com
  if [[ $? -eq 0 ]]; then  
      sudo apt install g++ gcc -y # installing automatically lib dependencis
  else
      printf "${RED}Please Using: ${GREEN}Internet${NC}\n" # If user not using connection in user computer.
      exit 1
  fi
fi

FILES=("app/worker/util.cpp" "app/worker/helper.cpp" \
    "src/jgw_controller.cpp" "app/worker/frequency.cpp" \
    "system/linux/sound.cpp" "src/jgw_play.cpp" \
    "app/worker/fileshelp.cpp" "src/jgw_compile.cpp" \
    "src/jgw_compile_wav.cpp" "system/linux/jgw_compile_exec.cpp")

# settings all variable in this
COMPILE="g++" # default compile: g++, support for clang (clang+)
NAME_OUTPUT="jgw"

FILES_NAME=("*") # get all file object (*.o)
# if you won't in release in mode remove -D_DEV in variable FLAGS_COMPILE_OUT
FLAGS_COMPILE_OUT="-O3 -D_DEV" # Flags in compile out into object file (.o)
FLAGS_COMPILE_FINISH="-O3 `sdl2-config --cflags --libs`" # Flags in compile out to binary file or executable file
OUT_BINARY_SRC="out_src" # out src object (.o) directory
OUT_BINARY_FINISH="out" # out executable file directory

# check its exist folder out_src
if [ -d "$OUT_BINARY_SRC" ] 
then
    # removing directory in out src directory
    rm -rf $OUT_BINARY_SRC # removing directory and all file in directory
    mkdir $OUT_BINARY_SRC # make again directory
else
    # if directory it's undefined this will make a new directory
    mkdir $OUT_BINARY_SRC
fi

# check its exist folder out
if [ -d "$OUT_BINARY_FINISH" ] 
then
    # if directory output it's already
    printf "Exist Folder: ${OUT_BINARY_FINISH}\n"
else
    # if undefined make new directory output of executable file
    mkdir $OUT_BINARY_FINISH
fi

# compile all files
for i in ${!FILES[@]}; do
	printf "[$i] ${GREEN}Compile: ${FILES[$i]}${NC}\n"
	${COMPILE} -c $FLAGS_COMPILE_OUT ${FILES[$i]}
done

# compile to binary
ALL_LIST_FILE=""
for i in ${!FILES_NAME[@]}; do
  ALL_LIST_FILE="${ALL_LIST_FILE} ${FILES_NAME[$i]}.o"
done

# end compile to executable file
printf "[FINISH] ${GREEN}Compile: ${ALL_LIST_FILE}${NC} to: ${NAME_OUTPUT} Binary\n"
${COMPILE} -O3 -o $OUT_BINARY_FINISH/$NAME_OUTPUT $ALL_LIST_FILE $FLAGS_COMPILE_FINISH

# move all file to out_src
mv *.o $OUT_BINARY_SRC
