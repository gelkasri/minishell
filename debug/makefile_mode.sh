#!/bin/zsh

NORMAL=$(tput sgr0)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)

MODE="NORMAL"

cat Makefile > ok.txt 2> /dev/null
if [[ $(cat ok.txt) == "" ]]
then
	echo "❌ ${RED}Vous devez appeller ce script sur le dossier ou se site votre Makefile${NORMAL}"
	rm -f ok.txt
	exit
fi

cat Makefile > old.txt

if [[ $1 = 'debug' ]]
then
	MODE="DEBUG"
	sed -i '' "s/(CFLAGS)/(DEBUG)/g" Makefile
else
	sed -i '' "s/(DEBUG)/(CFLAGS)/g" Makefile
fi

cat Makefile > new.txt
diff old.txt new.txt > diff.txt

clear
echo "✅ ${GREEN} ${MODE} MODE SET${NORMAL}"

if [[ $(cat diff.txt) != "" ]]
then
	echo "${YELLOW}make re;"
	echo -n "\e[s${BLUE}"
	make re
	echo -n "\e[u\e[J"
	echo "✅  ${GREEN}DONE${NORMAL}"
fi

rm -f old.txt new.txt diff.txt ok.txt