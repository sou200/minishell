#!/bin/bash

# echo $1

# test=$(ps  | awk '/\.\/minishel/ { print $1 }')

# if [ "$test" == "" ] ; then
# 	exit
# fi
while true
do
	leaks minishell

	# if [ "$?" -ne "0" ] ; then
	# exit
	# fi
	sleep 1
done 