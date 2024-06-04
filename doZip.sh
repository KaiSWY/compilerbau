#!/bin/bash

if [[ $# -eq 1 ]]
then
	
	# Cleanup files
	cd "$1"
	make clean
	cd ..

	# create folder with correct name and zip it
	mv "$1" Schaefer-Raible-Schablowsky
	tar -czvf Schaefer-Raible-Schablowsky.tgz Schaefer-Raible-Schablowsky
	mv Schaefer-Raible-Schablowsky "$1"

fi

