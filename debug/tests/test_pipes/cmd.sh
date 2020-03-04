
echo test1
ls | wc
echo test2
ls -la | wc
echo test3
ls -la | wc -c
echo test4
ls -la | wc -c | bc
echo test5
ls -la | wc -c | bc | wc
echo test6
ls -la | wc -c | bc | wc -w | bc

echo test7
cat Makefile | grep srcs
echo test8
cat Makefile | grep TOTO
echo test9
cat includes/minishell.h | grep define
echo test10
cat includes/minishell.h | grep define | wc
echo test11
cat includes/minishell.h | grep define | wc | wc | wc | wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc| wc

echo test12
/bin/ls|wc
echo test13
/bin/ls|          wc
echo test14
           /bin/ls          |        /usr/bin/wc               -c  |bc
echo test15
           /bin/ls          |        /usr/bin/wc               -c  |bc | bc|bc|bc|bc|wc -w|bc

echo test16
echo "ls | ls | ls | ls"
echo test17
echo ""ls | ls | ls | ls""
echo test18
echo 'ls | ls | ls | ls'
echo test19
echo 'ls | ls | ls | ls'
echo test20
echo '''ls | ls |' ls '| ls'
echo test21
ls | """wc""" -c | bc

echo end



