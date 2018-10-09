#!/bin/bash

MAKE="make --file glfw.mk -j12"

case $1 in
	clean)
		$MAKE clean
		;;
	
	build)
		$MAKE all
		;;

    debug)
        $MAKE debug
        ;;
	
	run)
		$MAKE run
		;;
esac
