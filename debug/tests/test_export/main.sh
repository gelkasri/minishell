#!/bin/zsh

./minishell ${1}/cmd.sh &> "${1}/our.log"
bash        ${1}/cmd.sh &> "${1}/his.log"

myfile="${1}/our_tests.log"
hisfile="${1}/his_tests.log"

rm -f $myfile $hisfile

grep "HOME=\"$HOME\"" "${1}/our.log" >> $myfile
grep "HOME=\"$HOME\"" "${1}/his.log" | sed "s/declare -x //g" >> $hisfile

grep "test=\"\"" "${1}/our.log" >> $myfile
grep "test=\"\"" "${1}/his.log" | sed "s/declare -x //g" >> $hisfile

grep "a=\"a=a\"" "${1}/our.log" >> $myfile
grep "a=\"a=a\"" "${1}/his.log" | sed "s/declare -x //g" >> $hisfile

grep "OLDPWD=\"$OLDPWD\"" "${1}/our.log" >> $myfile
grep "OLDPWD=\"$OLDPWD\"" "${1}/his.log" | sed "s/declare -x //g" >> $hisfile

# grep "?=" "${1}/our.log" >> $myfile
# grep "?=" "${1}/his.log" | sed "s/declare -x //g" >> $hisfile

diff $myfile $hisfile
