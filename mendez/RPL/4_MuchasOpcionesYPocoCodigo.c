#define ERROR -1
#include <stdlib.h>
#include <stdio.h>
/*
 * Se recibe una letra. Si ella se corresponde con alguna de las proveídas en el enunciado (A, R, L, G, F, O, T, C, R, B) se devuelve la cantidad de batallas ganadas por el pokemon respectivo.
 */
int batallas_ganadas(char letra){
    //tu código
    switch (letra) {
    case 'A':
        printf("Arbok");
        return 20;
    case 'R':
        printf("Rattata");
        return 17;

    case 'L':
        printf("Lapras");
        return 15;

    case 'G':
        printf("Golem");
        return 30;
    case 'F':
        printf("Flareon");
        return 8;

    case 'O':
        printf("Onix");
        return 27;

    case 'T':
        printf("Treecko");
        return 5;

    case 'C':
        printf("Charizard");
        return 39;

    case 'B':
        printf("Bulbassaur");
        return 10;

    default:
        printf("No se conoce la cantidad de batallas ganadas de dicho pokemon");
        return ERROR;
            }
}
