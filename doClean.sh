#!/bin/bash

for name in Schaefer-Raible-Schablowsky*
do
	if [[ $name != *"."* ]] 
	then
		echo Entering \' $name \'
		cd $name
		make clean >/dev/null
		cd ..
	fi	
done
