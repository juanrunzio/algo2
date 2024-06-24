#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

struct menu {
    const char **opciones;
    int cantidad_opciones;
};

menu_t *menu_crear()
{
    menu_t *menu = malloc(sizeof(menu_t));
    if (!menu)
        return NULL;
    
    static const char *opciones[] = {
    "1. Seleccionar dificultad",
    "2. Seleccionar Pokemon",
    "3. Mostrar informacion de Pokemon",
    "4. Armar pista de obstaculos",
    "5. Ejecutar carrera",
    "6. Salir"
};
    
    menu->opciones = opciones;
    menu->cantidad_opciones = sizeof(opciones) / sizeof(opciones[0]);
    return menu;
}

void menu_destruir(menu_t *menu)
{
    free(menu);
}

void menu_mostrar(const menu_t *menu)
{
    printf("\nMenú principal:\n");
    for (int i = 0; i < menu->cantidad_opciones; ++i) {
        printf("%s\n", menu->opciones[i]);
    }
}

int menu_seleccionar_opcion(const menu_t *menu)
{
    int opcion;
    printf("Seleccione una opción: \n");
    scanf("%d", &opcion);
    if (opcion < 1 || opcion > menu->cantidad_opciones) {
        printf("Opción inválida\n");
        return -1;
    }
    return opcion;
}