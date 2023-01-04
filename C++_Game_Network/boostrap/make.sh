#!/bin/bash

OK='\e[1;32m'
reset=`tput sgr0`

g++ -o ecs_TEST -I $PWD/ $PWD/bat_test.cpp -std=c++2a -g3
if [ $? -eq 0 ]; 
then 
    echo -e ${OK}
    echo "SUCCESS compilation"
    echo "${reset}"
else 
    echo "$CMD terminated unsuccessfully" 
fi
