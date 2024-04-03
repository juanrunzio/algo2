#!/bin/sh

NUMERO=10
while [ $NUMERO -gt 0 ]; do
	echo $NUMERO
	NUMERO=$((NUMERO-1))
done


for NUMERO2 in {1..10}; do
	echo $NUMERO2

done

#hay mas formas para hacer el for , por ejemplo una forma mas C
#for (( i=1; i<5 ; i++)); do
#	echo $i
#done


# cuando usamos la sitaxis $(prompt) se ejecuta un comando
# otra forma del for seria 
# for i in $(seq 1 2 20); do
# 	echo $i
# done
