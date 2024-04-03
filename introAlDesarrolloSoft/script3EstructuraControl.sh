#!/bin/sh

if [ "$NOMBRE" == "juan" ]; then
	echo "Bienvenido juanchi"
elif [ "$NOMBRE" == "manu" ]; then
	echo "hola manu"
else 
	echo "You shall not pass"
fi

#ya que los operadores <, >, << , >> , estan reservados para el input o output, input concatenado o output concatenado , se usa lo siguiente:

# -lt ,lower than seria => "<"
# -gt ,greater than seria => ">"
# -le ,lower equal seria => "<="
# -ge ,greater equal seria => ">="

#lo mismo pasa con los and "&&"
#se usa el -a
#o para el or => -o
