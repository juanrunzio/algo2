#ifndef ABB_H_
#define ABB_H_
#include <stdbool.h>

struct abb {
  int dato;
  struct abb* izq;
  struct abb* der;
};

//un enum , es un tipo de dato enumerado
enum abb_recorrido {ABB_RECORRIDO_INORDEN,ABB_RECORRIDO_PREORDEN,ABB_RECORRIDO_POSTORDEN};

struct abb* abb_crear();
struct abb* abb_insertar(struct abb *, int n);
bool abb_existe(struct abb*, int n);
void abb_con_cada_elemento(struct abb*, enum abb_recorrido, void (*f)(int, void*), void* aux);
void abb_destruir(struct abb*);





#endif // ABB_H_
