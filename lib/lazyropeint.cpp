#include "lazyropeint.h"
#include <math.h>

LazyRopeInt::LazyRopeInt(int tam, std::vector<int> vect) {
  n = pow(2, ceil(log(tam) / log(2)));
  arr = std::vector<int>(2 * n + 1);
  lazy = std::vector<int>(2 * n + 1);

  int i = 0;
  for (int elem : vect) {
    update(i, i + 1, elem);
    i++;
  }
  
}

// nodo es el índice del nodo a actualizar
// l_ y r_ es el intervalo cubierto por el nodo
// i es el índice a actualizar
// val es el nuevo valor a asignar
void LazyRopeInt::update_impl(int nodo, int l_, int r_, int l, int r, int upd) {
  propagate(nodo, l_, r_);
  if (l <= l_ && r_ <= r) {
    lazy[nodo] = upd;
    propagate(nodo, l_, r_);
    return;
  }
  if (r <= l_ || r_ <= l)
    return;
  int m_ = (l_ + r_) / 2;
  update_impl(izq(nodo), l_, m_, l, r, upd);
  update_impl(der(nodo), m_, r_, l, r, upd);
  arr[nodo] = arr[izq(nodo)] + arr[der(nodo)];
}

int LazyRopeInt::sum_impl(int nodo, int l_, int r_, int l, int r) {
  if (l <= l_ && r_ <= r) // [l_, r_) contenido en [l, r)
    return arr[nodo] + lazy[nodo];
  if (r <= l_ || r_ <= l) // [l_, r_) intersección [l, r) es vacía
    return 0;
  propagate(nodo, l_, r_);
  int m_ = (l_ + r_) / 2;
  return sum_impl(izq(nodo), l_, m_, l, r) + sum_impl(der(nodo), m_, r_, l, r);
}

void LazyRopeInt::propagate(int nodo, int l_, int r_) {
  int len = r_ - l_;
  if (len > 1) { // no es hoja, combino actualizaciones en los hijos
    lazy[izq(nodo)] = lazy[izq(nodo)] + lazy[nodo];
    lazy[der(nodo)] = lazy[der(nodo)] + lazy[nodo];
  }
  arr[nodo] = arr[nodo] + lazy[nodo] * len;
  lazy[nodo] = 0;
}

// EJ 2b

/*
Para poder actualizar los resultados de las operaciones perezosamente, además de la propiedad asociativa y la existencia del elemento neutro
por las mismas razones que en el ejercicio 1, se requiere que la operación sea conmutativa para la operación de
update, puesto que debemos poder reordenar la forma en que actualizamos los valores de los nodos, esto es, debe 
ser lo mismo actualizar en el nodo padre que actualizar individualmente a cada uno de sus hijos.

Por ejemplo, si tenemos una operación de suma y queremos actualizar un nodo c con hijos a y b con un valor u, 
tiene que darse la siguiente igualdad: c + 2u = (a + u) + (b + u), donde c = a + b. Luego, necesitamos poder 
conmutar u y b en la expresión a + b + u + u para que la igualdad se cumpla.
*/