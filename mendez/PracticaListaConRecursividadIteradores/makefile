probar: compilar valgrind

compilar:
	gcc lista.c pruebas.c -g -o lista.out

valgrind:
	valgrind --leak-check=full ./lista.out
