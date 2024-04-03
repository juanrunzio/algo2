#!/bin/sh

CANT_PALABRAS=$(ls | wc -l)

echo "Esta carpeta tiene $CANT_PALABRAS palabras" > mensaje.txt

cat mensaje.txt
