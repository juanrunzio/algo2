#!/bin/sh

#para que agarre todos los numero que se le pasan como parametros (cuando invocas el script)
#echo $@
#
#echo $(($@))

echo $(( $1 + $2 ))
