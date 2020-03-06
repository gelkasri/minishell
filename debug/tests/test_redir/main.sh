#!/bin/zsh

./minishell ${1}/cmd.sh &> "${1}/our.log"
bash        ${1}/cmd.sh &> "${1}/his.log"

./minishell ${1}/leaks.sh &> "${1}/leaks.log"
if [ $? != 0 ]
then
	echo "Leaks !! See ${1}/leaks.sh and ${1}/leaks.log for more details"
	exit 2
fi

diff "${1}/our.log" "${1}/his.log"