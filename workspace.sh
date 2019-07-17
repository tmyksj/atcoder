#!/bin/bash

root=$(dirname $0)
contest=$1
task=$2

if [ -z "$contest" -o -z "$task" ]; then
    exit 1
fi

mkdir -p "$root/$contest/$task"
cd "$root/$contest/$task"

if [ ! -f "main.cpp" ]; then
    cat << EOF > "main.cpp"
#include <iostream>

using namespace std;

int main() {
}
EOF
fi

while true; do
    echo -e -n "\e[32;1m$contest\e[m : \e[34;1m$task\e[m > "
    read cmd

    case "$cmd" in
        "h")
            echo
            echo -e "    \e[30;1mworkspace\e[m   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ."
            echo "    .                                                                    ."
            echo "    .       h ........... show help                                      ."
            echo "    .                                                                    ."
            echo "    .       ac .......... commit & exit                                  ."
            echo "    .       e ........... exit                                           ."
            echo "    .                                                                    ."
            echo "    .       [enter] ..... compile & run                                  ."
            echo "    .       c ........... compile                                        ."
            echo "    .                                                                    ."
            echo "    .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ."
            echo
            ;;
        "ac")
            git reset HEAD .
            git add main.cpp
            git commit -m "$task"
            exit
            ;;
        "e")
            exit
            ;;
        "")
            g++ -Wall -o main.out main.cpp
            if [ $? -eq 0 ]; then
                ./main.out
            fi
            ;;
        "c")
            g++ -Wall -o main.out main.cpp
            ;;
    esac
done
