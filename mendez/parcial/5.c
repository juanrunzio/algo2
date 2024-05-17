#include <stdio.h>

void intercambio(int *punteroX, int *punteroY) {
  int aux = *punteroX;
  *punteroX = *punteroY;
  *punteroY = aux;
}

void muevoAlSiguiente(int vector[], int n, int i) {
  if (i == n - 1)
    return;
  if (vector[i] > vector[i + 1]) {
    intercambio(&vector[i], &vector[i + 1]);
  }
  muevoAlSiguiente(vector, n, i + 1);
}

void bubbleSort(int vector[], int n) {
  if (n == 1)
    return;

  muevoAlSiguiente(vector, n, 0);

  bubbleSort(vector, n - 1);
}

// Función para imprimir un vectoreglo
void printvectoray(int vector[], int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", vector[i]);
  printf("\n");
}

int main() {
  int vector[] = {64, 34, 25, 12, 22, 11, 90};
  int n = sizeof(vector) / sizeof(vector[0]);
  printf("vectoreglo original:\n");
  printvectoray(vector, n);
  bubbleSortRecursive(vector, n);
  printf("vectoreglo ordenado:\n");
  printvectoray(vector, n);
  return 0;
}