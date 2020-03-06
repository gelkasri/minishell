#!/bin/zsh

./minishell ${1}/cmd.sh &> "${1}/our.log"
bash        ${1}/cmd.sh &> "${1}/his.log"

myfile="${1}/our_tests.log"
hisfile="${1}/his_tests.log"

rm -f $myfile $hisfile

grep HOME=$HOME "${1}/our.log" >> $myfile
grep HOME=$HOME "${1}/his.log" >> $hisfile

grep "test=" "${1}/our.log" >> $myfile
grep "test=" "${1}/his.log" >> $hisfile

grep "a=a=a" "${1}/our.log" >> $myfile
grep "a=a=a" "${1}/his.log" >> $hisfile

grep "OLDPWD=$OLDPWD" "${1}/our.log" >> $myfile
grep "OLDPWD=$OLDPWD" "${1}/his.log" >> $hisfile

grep "?=" "${1}/our.log" >> $myfile
grep "?=" "${1}/his.log" >> $hisfile

./minishell ${1}/leaks.sh &> "${1}/leaks.log"
if [ $? != 0 ]
then
	echo "Leaks !! See ${1}/leaks.sh and ${1}/leaks.log for more details"
	exit 2
fi

diff $myfile $hisfile
