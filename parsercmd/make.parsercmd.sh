#!/bin/sh
case `uname -s` in
	HP-UX) 
		OS="Unix";;
	SunOS)
		OS="Unix";;
	IRIX*) 
		OS="Unix";;
	Linux)
		OS="Unix";;

	*) 
		OS="Windows";;
esac
./make/${OS}/make.parsercmd.sh $*
#
# -- end:
#
