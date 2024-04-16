#include <stdio.h>
#include "lista.h"
#include <stdbool.h>
bool funcion(void* elemento, int i, void* contexto) {
  //iterador interno
  printf("(Entro al loop)\n");
  lista_t* lista = contexto;
  printf("Elemento %i: %p\n",i, elemento);

  return i+1 < lista_tamanio(lista)/2;
}

int main(int argc, char *argv[]) {

  void *e1=(void*)1, *e2=(void*)2;
  lista_t* lista = lista_crear();
  lista_insertar(lista, e1);
  lista_insertar(lista, e2);

  for(unsigned long i=3; i<20; i++){
    lista_insertar(lista, (void*)i);
  }

  printf("Recorro la lista con una iteracion normal: \n");
  //esto es O(n²)
  for (int i=0;i<lista_tamanio(lista)/2; i++){
    printf("(Entro al loop)\n");//con esto comprobe que el iteradir sigue de largo, pero si cambiamos la funcion a bool y no void
    void* elemento = lista_obtener(lista, i); //O(n)
    printf("Elemento %i: %p\n",i, elemento);
  }
  //hay alguna forma de mejorar esto?
  //iterador externo
  printf("\n\nRecorro la lista con un iterador externo: \n");
  lista_iterador_t* it;

  //la idea es reducir la complejidad a O(n)
  //iterador externo
  for(it=lista_iterador_crear(lista); lista_iterador_hay_mas_elementos_por_recorrer(it); iterador_siguiente_interacion(it)) {
    //puedo agregar de cortar la lista a la mitad aca , porque estoy controlando la iteracion yo
    void* elemento = lista_iterador_devolveme_un_elemento(it); //lograr que sea -> O(1)
    printf("Elemento: %p\n", elemento);

  }

  //la diferencia entre iterador externo y interno , principalmente con los interadores externos, nosotros somos los encargados de hacer la iteracion,
  //iteramos desde afuera, controlamos nostros la iteracion, si hay que corta la iteracion, la cortas
  //en los internos se encarga la lista misma y es con una funcion


  //que ventaja me da esto? -> la primer ventaja es,puedo aplicar una operacion a cada elemento de la lista sin tener que explicitamente plantear el recorrido de decir un for(cada elemento)
  //otra ventaja es que esto pasa a ser O(n), al conocer la implementacion, lista es una estructura "opaca", nose lo que pasa dentro (nose el "como?" lo hace), no puedo acceder
  printf("\n\nRecorro la lista con un iterador interno: \n");
  //un ejemplo de como seria con internos es
  lista_iterar_todos_los_elementos(lista, funcion, lista);
  //tambien la idea es , al trabajar con la interfaz y respetando el import .h , es que si el dia dia mañana viene alguien y quiere cambiar la implementacion y hacerlo con listas enlazadas , lo pueda hacer sin que se rompa todo el codigo

  lista_destruir(lista);
  //para destruir todo tanto los bloques reservados por malloc , el primer puntero y el vector de punteros(a los bloques de memoria)
  //lista_destruir_todo(lista, destruir_elemento);
  return 0;
}
