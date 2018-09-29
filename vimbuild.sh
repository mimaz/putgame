#!/bin/bash

case $1 in
	clean)
		make clean -j4
		;;
	
	build)
		make all -j4
		;;
	
	run)
		make run -j4
		;;
esac
