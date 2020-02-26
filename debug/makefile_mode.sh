#!/bin/zsh

NORMAL=$(tput sgr0)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)

MODE="NORMAL"

function change_mode () {
	REPLACE=$(cat Makefile | grep "CURRENT_FLAGS = ")
	sed -i "s/$REPLACE/$1/g" Makefile
	REPLACE=$(cat libft/Makefile | grep "CURRENT_FLAGS = ")
	sed -i "s/$REPLACE/$1/g" libft/Makefile
}

cat Makefile > ok.txt 2> /dev/null
if [[ $(cat ok.txt) == "" ]]
then
	echo "❌ ${RED}Vous devez appeller ce script sur le dossier ou se site votre Makefile${NORMAL}"
	rm -f ok.txt
	exit
fi

cat Makefile > old.txt

if [ $1 = "debug" ]
then
	MODE="DEBUG"
	FLAGS='CURRENT_FLAGS = $(DEBUG)'
	change_mode $FLAGS
elif [ $1 = "linux" ]
then
	MODE="LINUX"
	FLAGS='CURRENT_FLAGS = $(LINUX)'
	change_mode $FLAGS
else
	MODE="NORMAL"
	FLAGS='CURRENT_FLAGS = $(CFLAGS)'
	change_mode $FLAGS
fi

cat Makefile > new.txt
diff old.txt new.txt > diff.txt

clear
echo "✅ ${GREEN} ${MODE} MODE SET${NORMAL}"

ERROR="0"

if [[ $(cat diff.txt) != "" ]]
then
	echo -n "\e[s"
	echo "${YELLOW}Compiling ..."
	make re &> compilation.log
	if [ $? = "0" ]
	then
		echo -n "\e[u\e[J"
		echo "✅  ${GREEN}DONE${NORMAL}"
	else
		echo -n "\e[u\e[J"
		echo "❌ ${RED} Compilation error${NORMAL}"
		echo "${BLUE}logs are here: ./compilation.log${NORMAL}"
		ERROR="1"
	fi
fi

if [ $ERROR = "0" ]
then
	rm -f compilation.log
fi

rm -f old.txt new.txt diff.txt ok.txt