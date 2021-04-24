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

# check compiler
if test -f "/usr/bin/$COMPILE" 
then
  printf "Compiler: ${GREEN}${COMPILER}${NC} It's Exist\n"
else
  printf "Compiler It's not ${RED}exist${NC}\n"
  exit 1
fi