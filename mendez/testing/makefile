probar: compilar correr_valgrind

compilar:
	gcc pila_estatica.c pruebas.c -g -o pruebas.out

correr_valgrind:
	valgrind --leak-check=full ./pruebas.out
