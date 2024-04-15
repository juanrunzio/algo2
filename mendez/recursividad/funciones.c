#include "funciones.h"

unsigned strlen2() {
  if (*str == 0) {
    return 0;
  }
  return 1+strlen2(str+1);
}
