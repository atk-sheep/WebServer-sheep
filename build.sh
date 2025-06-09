#!/bin/sh

WEBSERVER=ON
ASIOTEST=OFF

print_help(){
    echo "-h option, get help"
    echo "-c option, start compile"
}

while getopts h:c:t opt
do
   case $opt in
       h) print_help; exit 0;;
       c) WEBSERVER=${opt};;
       t) ASIOTEST=ON;WEBSERVER=OFF;;
       *) print_help; exit 1;;  # 选项无效时
   esac
done

if [ ${WEBSERVER} = "ON" ]; then

    rm -rf ./out

    [ -d out ] || { mkdir out; }

    { cd out; cmake -DWEBSERVER=ON -DASIOTEST=OFF ..; 
        cmake --build .; cmake --install .;}
fi

if [ ${ASIOTEST} = "ON" ]; then

    rm -rf ./out

    [ -d out ] || { mkdir out; }

    { cd out; cmake -DWEBSERVER=OFF -DASIOTEST=ON ..; 
        cmake --build .; cmake --install .;}
fi

