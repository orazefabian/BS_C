#!/bin/bash
if [ 1 -gt "$#" ] 
then
    echo "Usage: $0 name [additional names]" 
else
    echo "" > hello.txt # make empty hello.txt

    echo "Total number of names is $#"
    echo ""
    for name
    do 
    echo "Hello $name"
    echo "Hello $name" >> hello.txt # add hello $name to hello.txt for every loop 
    done
    
fi

#to make file executable: chmod a+rx hello.sh