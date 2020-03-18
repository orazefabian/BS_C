#!/bin/bash
if [ 1 -gt "$#" ] 
then
    echo "Usage: $0 name [additional names]" 
else
    echo "Total number of names is $#"
    echo ""
    echo "Hello $1"
done
fi

#to make file executable: chmod a+rx hello.sh