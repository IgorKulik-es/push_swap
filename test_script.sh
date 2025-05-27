#!/bin/bash
make

ARG="59 16 61 90 97 88 72 2 89 99 25 22 42 69 4 24 44 70 58 57 7 20 83 30 86 27 45 55 1 56 34 65 28 40 35 66 52 31 82 6 21 77 98 12 17 15 64 60 46 62 26 49 85 33 3 79 67 48 63 5 23 10 76 73 19 9 18 54 78 94 87 41 71 29 11 80 13 81 14 92 91 43 74 39 96 47 84 51 37 95 53 75 93 36 50 38 32 8 100 68 "
RESULT=$(./push_swap $ARG | ./checker_linux $ARG)
MOVES=$(./push_swap $ARG | wc -l)
echo "Test 1 $RESULT at $MOVES moves"

ARG="76 28 68 18 59 46 7 32 10 33 72 5 14 26 9 44 87 19 1 100 2 73 94 43 78 90 17 49 66 79 20 82 11 56 67 15 81 23 62 71 22 12 97 74 83 42 47 37 85 25 65 31 91 53 51 64 30 41 70 69 45 77 84 57 21 4 93 58 89 6 24 8 35 88 80 92 40 55 61 50 96 75 38 98 48 27 39 36 29 34 16 54 3 60 63 52 13 86 95 99"
RESULT=$(./push_swap $ARG | ./checker_linux $ARG)
MOVES=$(./push_swap $ARG | wc -l)
echo "Test 2 $RESULT at $MOVES moves"

i=0
j=0
error=0
min=1000
max=0
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

