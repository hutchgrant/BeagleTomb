#!/bin/bash
exit=0

step=1
step1='16q'
step2='33q'
step3='50q'
step4='80q'
file='instructions'
choice=0
while [ $choice != "x" ]
do
	case $step in
	1)
	sed $step1 $file 
	read choice	
	step="2"
	;;
	2)
	sed $step2 $file 
	read choice
	if [ choice != "x" ]; then
		step="3"
	else
	exit=1
	fi;;
	3)
	sed $step3 $file 
	read choice
	if [ choice != "x" ]; then
		step="4"
	else
	exit=1
	fi;;
	4)
	sed $step4 $file 
	read choice
	if [ choice != "x" ]; then
		exit=1
	else
	exit=1
	fi;;
	esac	
	
done
