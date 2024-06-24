#ifndef MENU_H
#define MENU_H

typedef struct menu menu_t;

menu_t *menu_crear();
void menu_destruir(menu_t *menu);
void menu_mostrar(const menu_t *menu);
int menu_seleccionar_opcion(const menu_t *menu);

#endif // MENU_H