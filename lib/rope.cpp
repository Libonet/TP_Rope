#include <concepts>
#include "rope.h"

#define N 8
int valor[2*N+1];
// argumentos:
// nodo - nodo a actualizar
// l_ y r_ - intervalo cubierto por nodo
// i - indice a actualizar
// x - nuevo valor a asignar
static void update_impl(int nodo, int l_, int r_, int i, int x) {
  int l = i, r = i+1;
  if (l <= l_ && r_ <= r) { valor[nodo] = x; return; }
  if (r <= l_ || r_ <= l) return;
  int m_ = (l_ + r_) / 2;
  // obs: una sola de estas dos llamadas hace algo, la otra cae en el caso base trivial inmediatamente
  update_impl(izq(nodo), l_, m_, i, x);
  update_impl(der(nodo), m_, r_, i, x);
  valor[nodo] = valor[izq(nodo)] + valor[der(nodo)]; // actualizo de abajo hacia arriba
}

void update(int i, int x) {
  update_impl(0, 0, N, i, x);
}

/* ??? */

// Implementa el concepto de grupo
struct int_suma {
using Value = int;
  static int op(int x, int y) { return x + y; } // una operacion asociativa
  static int neut() { return 0; } // elemento neutro para op
  static int inv(int x) { return -x; } // inverso para op respecto a neut()
};

template<typename G>
requires Group<G>
// sintaxis alternativa: template<Group G>
void invert_all(std::vector<typename G::Value>* arr) {
  for (int i = 0; i < arr->size(); ++i) {
    (*arr)[i] = G::inv((*arr)[i]);
  }
}

int main() {
  std::vector<int> v = {1, 2, 3};
  invert_all<int_suma>(&v);
}