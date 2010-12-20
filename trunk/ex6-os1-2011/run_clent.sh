#! /bin/bash

# 		############################################################################
# 		lolnik@gmail.com	########################################################
#		############################################################################
#
clear

echo "###################################################"

gcc -Wall ex6server.c -o server
gcc -Wall ex6client.c -o client
#./server 55 30 & 
COUNTER=20
LOL=4
     until [  $COUNTER -lt 10 ]; do
		valgrind ./client 12 4
		let LOL-=1
        echo COUNTER $COUNTER
        let COUNTER-=1

		    if [ "$LOL" = "0" ] ; then
		    	let LOL=4
		    fi

     done
     
