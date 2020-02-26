#!/bin/zsh

NORMAL=$(tput sgr0)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)

cat Makefile > ok.txt 2> /dev/null
if [[ $(cat ok.txt) == "" ]]
then
	echo "❌ ${RED} Vous devez appeller ce script sur le dossier ou se site votre Makefile${NORMAL}"
	rm -f ok.txt
	exit
fi

rm -f ok.txt

echo -n "\e[s"
echo "${YELLOW}Building minishell ..."
make re > /dev/null
echo -n "\e[u\e[J"
echo "✅  ${GREEN}Build ok${NORMAL}"

for file in debug/tests/test_*
do
	bash "$file"/main.sh $file
	if [[ $? != "0" ]]
	then
		echo -n "❌ ${RED} "
		echo $file | sed "s/debug\/tests\///g"
		echo -n $NORMAL
		echo "${BLUE}Additionnal logs:"
		for log_file in $file/*.log
		do
			echo "${log_file}"
		done
	else
		echo -n "✅  ${GREEN}"
		echo $file | sed "s/debug\/tests\///g"
		echo -n $NORMAL
	fi
done