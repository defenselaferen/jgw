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
    printf "${RED}Doesn't${NC} exist dependencis\n"
    exit 1
fi

# settings all variable in this
COMPILE="g++" # default compile: g++, support for clang (clang+)
FILES=("app/worker/util.cpp" "app/worker/helper.cpp" \
    "src/jgw_controller.cpp" "app/worker/frequency.cpp" \
    "system/linux/sound.cpp" "src/jgw_play.cpp" \
    "app/worker/fileshelp.cpp" "src/jgw_compile.cpp" \
    "src/jgw_compile_wav.cpp")

# check compiler
if [ -d "/usr/bin/$COMPILE" ] 
then
  printf "Compiler: ${GREEN}${COMPILER}${NC} It's Exist\n"
else
  printf "Compiler It's not ${RED}exist${NC}\n"
  exit 1
fi

# Check all files
for i in ${!FILES[@]}; do
	printf "[$i] ${GREEN}Compile: ${FILES[$i]}${NC}\n"
	${COMPILE} -c $FLAGS_COMPILE_OUT ${FILES[$i]}
  # check its exist folder out
  if [ -d "$FILES[$i]" ] 
  then
      # if directory output it's already
      printf "Exist Folder: ${FILES[$i]}\n"
  else
      # if undefined give error code
      printf "File doesn't exist: ${RED}FILES[$i]${NC}\n"
      exit 1
  fi
done
