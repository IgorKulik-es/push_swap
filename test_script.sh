#!/bin/bash
make

RED='\033[0;31m'
GREEN='\033[0;32'
NC='\033[0m'

i=0
j=0
error=0
min=1000
max=0
printf "\nTesting for ${RED}100${NC} elements\n"
while [ "$i" -le 1000 ]
do
ARG=$(seq 1 100 | sort -R | tr '\n' ' ')
RESULT=$(./push_swap $ARG | ./checker_linux $ARG)
MOVES=$(./push_swap $ARG | wc -l)
if [ "$min" -ge "$MOVES" ]
then
min=$MOVES
fi
if [ "$max" -le "$MOVES" ]
then
max=$MOVES
fi
if [ "$MOVES" -ge 700 ]
then
j=$((j + 1))
echo $ARG
fi
if [ "$RESULT" != "OK" ]
then
error=$((error + 1))
echo $ARG
fi

i=$((i + 1))
done

error=$((1000 - $error))
echo "Success at $error tests out of 1000"
echo "Overshot at $j tests out of 1000"
echo "Maximal result at $max, minimal at $min."
echo ""

printf "Testing for ${RED}500${NC} elements\n"

i=0
j=0
error=0
min=10000
max=0
while [ "$i" -le 200 ]
do
ARG=$(seq 1 500 | sort -R | tr '\n' ' ')
RESULT=$(./push_swap $ARG | ./checker_linux $ARG)
MOVES=$(./push_swap $ARG | wc -l)
if [ "$min" -ge "$MOVES" ]
then
min=$MOVES
fi
if [ "$max" -le "$MOVES" ]
then
max=$MOVES
fi
if [ "$MOVES" -ge 5500 ]
then
j=$((j + 1))
echo $ARG
fi
if [ "$RESULT" != "OK" ]
then
error=$((error + 1))
echo $ARG
fi

i=$((i + 1))
done

error=$((200 - $error))
echo "Success at $error tests out of 200"
echo "Overshot at $j tests out of 200"
echo "Maximal result at $max, minimal at $min."
echo $test

