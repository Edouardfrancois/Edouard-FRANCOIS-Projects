#!/bin/bash

OK='\e[1;32m'
reset=`tput sgr0`

g++ -o step3_test -I $PWD/ $PWD/step3.cpp $PWD/graphic.cpp -std=c++2a -g3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
if [ $? -eq 0 ]; 
then 
    echo -e ${OK}
    echo "SUCCESS compilation"
    echo "${reset}"
else 
    echo "$CMD terminated unsuccessfully" 
fi
