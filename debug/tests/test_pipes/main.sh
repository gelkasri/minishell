#!/bin/zsh

rm -f "${1}/our.log" "${1}/his.log" "${1}/leaks.log" "${1}/error_bash.log" "${1}/error_minishell.log"

./minishell ${1}/cmd.sh &> "${1}/our.log"
bash        ${1}/cmd.sh &> "${1}/his.log"

diff "${1}/our.log" "${1}/his.log"
if [ $? != 0 ]
then
	echo "Some diffs found in ${1}"
	exit 1
fi

./minishell ${1}/leaks.sh &> "${1}/leaks.log"
if [ $? != 0 ]
then
	echo "Leaks !! See ${1}/leaks.sh and ${1}/leaks.log for more details"
	exit 2
fi

echo "lls | wc" | ./minishell &> "${1}/error_minishell.log"
m_err=$?
echo "lls | wc" | ./minishell &> "${1}/error_bash.log"
b_err=$?
if [ $b_err != $m_err ]
then
	echo "Diffs on exit codes $b_err <> $m_err"
	exit 3
fi

echo "ls | wcc" | ./minishell	&> "${1}/error_minishell.log"
m_err=$?
echo "ls | wcc" | bash			&> "${1}/error_bash.log"
b_err=$?
if [ $b_err != $m_err ]
then
	echo "Diffs on exit codes $b_err <> $m_err"
	exit 3
fi

exit 0