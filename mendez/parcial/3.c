#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *data;
} rojo;

typedef struct azul {
  rojo *vectorRojo;
  struct azul *next;
} azul;

int main() {
  azul *azul1 = (azul *)malloc(sizeof(azul));
  azul *azul2 = (azul *)malloc(sizeof(azul));
  azul *azul3 = (azul *)malloc(sizeof(azul));
  azul *azul4 = (azul *)malloc(sizeof(azul));

  if (!azul1 || !azul2 || !azul3 || !azul4) {
    printf("error al reservar memoria para los bloques de Azul\n");
    return 1;
  }

  char contenidoDelRojo[][2] = {"A", "B", "C", "D", "E", "F",
                                "G", "H", "I", "J", "K", "L"};

  azul1->vectorRojo = (rojo *)malloc(3 * sizeof(rojo));
  azul2->vectorRojo = (rojo *)malloc(3 * sizeof(rojo));
  azul3->vectorRojo = (rojo *)malloc(3 * sizeof(rojo));
  azul4->vectorRojo = (rojo *)malloc(3 * sizeof(rojo));

  if (!azul1->vectorRojo || !azul2->vectorRojo || !azul3->vectorRojo ||
      !azul4->vectorRojo) {
    printf("error al reservar memoria para los bloques de Rojo\n");
    return 1;
  }

  for (int i = 0; i < 3; ++i) {
    azul1->vectorRojo[i].data = strdup(contenidoDelRojo[i]);
    azul2->vectorRojo[i].data = strdup(contenidoDelRojo[i + 3]);
    azul3->vectorRojo[i].data = strdup(contenidoDelRojo[i + 6]);
    azul4->vectorRojo[i].data = strdup(contenidoDelRojo[i + 9]);
  }

  azul1->next = azul2;
  azul2->next = azul3;
  azul3->next = azul4;
  azul4->next = NULL;

  azul *punteroHaciaElVec = azul1;

  azul *aux;
  while (punteroHaciaElVec != NULL) {
    aux = punteroHaciaElVec;
    punteroHaciaElVec = punteroHaciaElVec->next;

    for (int i = 0; i < 3; ++i) {
      free(aux->vectorRojo[i].data);
    }
    free(aux->vectorRojo);
    free(aux);
  }

  return 0;
}
