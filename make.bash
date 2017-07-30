#!/bin/bash

gp='g++ -O -Wall -std=c++11'
$gp hi.cpp -o hi
$gp v.cpp -o v_tmp && cat v_tmp hi >v && chmod +x v

cp /bin/ls .
cp hi newhi
cp hi other

ls -l