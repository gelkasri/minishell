#!/bin/zsh

./minishell ${1}/cmd.sh &> "${1}/our.log"
bash        ${1}/cmd.sh &> "${1}/his.log"

diff "${1}/our.log" "${1}/his.log"