#include <stdio.h>
#include <stdlib.h>

// i = 0
// 0 => n-1
// 1 => n-2
// 2 => n-3
//...
// n-3 => 2
// n-2 => 1
// n-1 => 0
//
// 0+1+2+3+...+n-3+n-2+n-1 = n(n-1)/2 = n²/2 - n/2 = O(n²)

void bubbleSort(int arr[], int n) {
  int i, j; // 1
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {    // 1
        swap(&arr[j], &arr[j + 1]); // 1
      }
    }
  }
}

// O(?)
// su(n) => 4 + su((n-1)/2)
// su((n-1)/2) => 4 + su(((n-1)/2-1)/2)
// su(((n-1)/2-1)/2) => 4 + su((((n-1)/2-1)/2-1)/2)
//...
// su(0) => 1
// 4 + 4 + 4 + 4 + 4 + 1 = 5n = O(n)
// n/2/2/2... = n/(2^k)
// log_2(n) = k
// n/(2^k) = 1 => n = 2^k => k = log_2(n)
// ejemplo queremos saber cuando sea =1
////n/2/2/2... = n/(2^k) = 1
// n = (2^k)
// log_2(n) = log_2(2^k)
// log_2(n) = k
// log_2(n)
// otra froma de escribir log_2(n)
// log(n)/log(2) => log(n)*c

void sift_up(int *vector, int posicion) {
  if (posicion == 0) // 1
    return;
  int pos_padre = (posicion - 1) / 2; // 1

  if (vector[pos_padre] < vector[posicion]) { // 1
    swap_int(vector, pos_padre, posicion);    // 1
    sift_up(vector, pos_padre);               //??
  }
}

// caso factorial
// f(n) = n*f(n-1)
// f(n-1) = (n-1)*f(n-2)
// f(n-2) = (n-2)*f(n-3)
//...
// f(1) = 1*f(0)
// f(0) = 1

int fact(n) {
  if (n == 0)             // 1
    return 1;             // 1
  return n * fact(n - 1); // 1
}

void quickSort(int *numeros, int tamanio) {
  if (tamanio <= 1)                                            // 1
    return;                                                    // 1
  int posiscion_final = ordenar_un_elemento(numeros, tamanio); // O(n)
  quickSort(numeros + 0, posiscion_final);                     // 1
  quickSort(numeros + posiscion_final + 1, tamanio - posiscion_final - 1); // 1
}

void msort(int *numeros, int tamanio) {
  if (tamanio <= 1) // 1
    return;
  int mitad = tamanio / 2; // 1

  int *v1 = numeros;                // 1
  int tamanio_v1 = mitad;           // 1
  int *v2 = numeros + mitad;        // 1
  int tamanio_v2 = tamanio - mitad; // 1
  int v3[tamanio];                  // 1

  msort(v1, tamanio_v1);                       //?
  msort(v2, tamanio_v2);                       //?
  mezclar(v1, tamanio_v1, v2, tamanio_v2, v3); // O(n)
  memcpy(numeros, v3, tamanio * sizeof(int));  // O(n)
}
// O(7)+2*O(n)+2*???
// M(n) = O(7) + 2*O(n) + 2M(n/2)
// M(n/2) = O(7) + 2*O(n/2) + 2M(n/4)
// M(n/4) = O(7) + 2*O(n/4) + 2M(n/8)
//...
// M(1) = O(7) + 2*O(1)
// M(1) = 1
//
// Teorema maestro
// T(n) = A*T(n/B) + O(f(n))
//
// A>=1 y B>1 y enteros
// f(n) polinomica creciente
// tenemos esta forma??
//
// M(n) = O(7) + 2*O(n) + 2M(n/2)
// si la reacomodamos ,parece q si
// M(n) = 2*M(n/2) + n
// si esto se cumple
//
// C = n^(log_B(A)) ==>formula general
// 1) si C > O(f(n)) => M(n) = C
// 2) si C < O(f(n)) => M(n) = O(f(n))
// 3) si C = O(f(n)) => M(n) = log(n)*C
//
// M(n) = 2*M(n/2) + n
// T(n) = A*T(n/B) + O(f(n))
// A=2 B=2
// C = n
// O(n*log(n))
int main(int argc, char *argv[]) {
  int numeros[] = {6, 8, 4, 2, 6, 9, 1, 0, 66, -1};

  int tamanio = sizeof(numeros) / sizeof(*numeros);

  quickSort(numeros, tamanio);

  for (int i = 0; i < tamanio; i++) {
    printf("%d ", numeros[i]);
  }
  return 0;
}