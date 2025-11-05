#ifndef ROPE_H
#define ROPE_H

#include <concepts>
#include <vector>
#include <math.h>

template<typename T>
concept Monoid = requires(T::Value a, T::Value b, T::Value c) {
typename T::Value; // hay un tipo de valores
  { T::op(a, b) } -> std::same_as<typename T::Value>; // clausura de la operacion
  // T::op(a, T::op(b, c)) == T::op(T::op(a, b), c) // asociatividad de la operacion
  { T::neut() } -> std::same_as<typename T::Value>; // existencia del neutro
  // T::op(a, T::neut()) == a // neutro por derecha
  // T::op(T::neut(), a) == a // neutro por izquierda
};

template<typename Op>
requires Monoid<Op>
class Rope {
  public:
    // obtiene la suma de un intervalo [l, r)
    Rope(int tam, std::vector<typename Op::Value> vect);

    void update(int i, Op::Value val) { update_impl(0, 0, n, i, val); }
    Op::Value sum(int l, int r) { return sum_impl(0, 0, n, l, r); }

  private:
    void update_impl(int nodo, int l_, int r_, int i, Op::Value val);
    Op::Value sum_impl(int nodo, int l_, int r_, int l, int r);

    static int izq(int nodo) { return 2 * nodo + 1; }
    static int der(int nodo) { return 2 * nodo + 2; }

    std::vector<typename Op::Value> arr;
    int n; // secuencia de n elementos, 2n+1 nodos
};

template<typename Op>
requires Monoid<Op>
Rope<Op>::Rope(int tam, std::vector<typename Op::Value> vect) {
  n = pow(2, ceil(log(tam) / log(2)));
  arr = std::vector<int>(2 * n + 1);

  int i = 0;
  for (typename Op::Value elem : vect) {
    update(i, elem);
    i++;
  }
}

// nodo es el índice del nodo a actualizar
// l_ y r_ es el intervalo cubierto por el nodo
// i es el índice a actualizar
// val es el nuevo valor a asignar
template<typename Op>
requires Monoid<Op>
void Rope<Op>::update_impl(int nodo, int l_, int r_, int i, Op::Value val) {
  int l = i, r = i + 1;
  if (l <= l_ && r_ <= r) {
    arr[nodo] = val;
    return;
  }
  if (r <= l_ || r_ <= l)
    return;
  int m_ = (l_ + r_) / 2;
  update_impl(izq(nodo), l_, m_, i, val);
  update_impl(der(nodo), m_, r_, i, val);
  arr[nodo] = arr[izq(nodo)] + arr[der(nodo)];
}

template<typename Op>
requires Monoid<Op>
Op::Value Rope<Op>::sum_impl(int nodo, int l_, int r_, int l, int r) {
  if (l <= l_ && r_ <= r) // [l_, r_) contenido en [l, r)
    return arr[nodo];
  if (r <= l_ || r_ <= l) // [l_, r_) intersección [l, r) es vacía
    return 0;
  int m_ = (l_ + r_) / 2;
  return sum_impl(izq(nodo), l_, m_, l, r) + sum_impl(der(nodo), m_, r_, l, r);
}

#endif // ROPE_H
