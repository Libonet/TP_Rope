#ifndef LAZYROPE_H
#define LAZYROPE_H

#include <concepts>
#include <vector>
#include <math.h>

#include <iostream>

template <typename T>
concept LazyUpdate = 
  requires { typename T::Value; typename T::Update; } &&
  requires ( typename T::Value a, T::Value b ) {
    { T::query(a, b) } -> std::same_as<typename T::Value>; // clausura de la operacion
    // T::query(a, T::query(b, c)) == T::query(T::query(a, b), c) // asociatividad de la operacion
    { T::neutQ() } -> std::same_as<typename T::Value>; // existencia del neutro
    // T::query(a, T::neutQ()) == a // neutro por derecha
    // T::query(T::neutQ(), a) == a // neutro por izquierda
  } &&
  requires ( typename T::Update a, T::Update b ) {
    { T::update(a, b) } -> std::same_as<typename T::Update>; // clausura de la operacion
    // T::query(a, T::query(b, c)) == T::query(T::query(a, b), c) // asociatividad de la operacion
    // T::query(a, b) == T::query(b, a) // conmutatividad de la operacion
    { T::neutU() } -> std::same_as<typename T::Update>; // existencia del neutro
    // T::update(a, T::neutU()) == a // neutro por derecha
    // T::update(T::neutU(), a) == a // neutro por izquierda
  } &&
  requires (typename T::Update up, typename T::Value val, int len) {
    { T::apply(up, val, len) } -> std::same_as<typename T::Value>;
  };

template<typename Op>
requires LazyUpdate<Op>
class LazyRope {
public:
    LazyRope(int n, std::vector<typename Op::Update> vect);
    typename Op::Value query(int l, int r) { return query_impl(0, 0, n, l, r); };
    void update(int l, int r, typename Op::Update x) { update_impl(0, 0, n, l, r, x); };

private:
    std::vector<typename Op::Value> data;
    std::vector<typename Op::Update> lazy;
    int n; // tamaño real del arbol subyacente

    void update_impl(int nodo, int l_, int r_, int l, int r, Op::Update val);
    typename Op::Value query_impl(int nodo, int l_, int r_, int l, int r);
    void propagate(int nodo, int l_, int r_);

    void setNeutQ(int nodo, int l_, int r_, int l, int r);

    static int izq(int nodo) { return 2 * nodo + 1; }
    static int der(int nodo) { return 2 * nodo + 2; }
};

template<typename Op>
requires LazyUpdate<Op>
LazyRope<Op>::LazyRope(int tam, std::vector<typename Op::Update> vect) {
  n = pow(2, ceil(log(tam) / log(2)));
  data = std::vector<typename Op::Value>(2 * n + 1);
  lazy = std::vector<typename Op::Update>(2 * n + 1, Op::neutU());

  int i = 0;
  for (typename Op::Update elem : vect) {
    update(i, i+1, elem);
    i++;
  }

  setNeutQ(0, 0, n, i, n);
}

// nodo es el índice del nodo a actualizar
// l_ y r_ es el intervalo cubierto por el nodo
// l y r son el intervalo que actualizar
// val es el nuevo valor a asignar
template<typename Op>
requires LazyUpdate<Op>
void LazyRope<Op>::setNeutQ(int nodo, int l_, int r_, int l, int r) {
  if (l <= l_ && r_ <= r) {
    data[nodo] = Op::neutQ();
    return;
  }
  if (r <= l_ || r_ <= l)
    return;

  int m_ = (l_ + r_) / 2;
  setNeutQ(izq(nodo), l_, m_, l, r);
  setNeutQ(der(nodo), m_, r_, l, r);
  data[nodo] = Op::neutQ();
}

template<typename Op>
requires LazyUpdate<Op>
void LazyRope<Op>::propagate(int nodo, int l_, int r_) {
  int len = r_ - l_;
  if (len > 1) { // No es hoja, combino actualizaciones en los hijos
    lazy[izq(nodo)] = Op::update(lazy[nodo], lazy[izq(nodo)]);
    lazy[der(nodo)] = Op::update(lazy[nodo], lazy[der(nodo)]);
  }
  data[nodo] = Op::apply(lazy[nodo], data[nodo], len);
  lazy[nodo] = Op::neutU();
}

// nodo es el índice del nodo a actualizar
// l_ y r_ es el intervalo cubierto por el nodo
// l y r son el intervalo que actualizar
// val es el nuevo valor a asignar
template<typename Op>
requires LazyUpdate<Op>
void LazyRope<Op>::update_impl(int nodo, int l_, int r_, int l, int r, Op::Update val) {
  propagate(nodo, l_, r_);
  if (l <= l_ && r_ <= r) {
    lazy[nodo] = val;
    propagate(nodo, l_, r_);
    return;
  }
  if (r <= l_ || r_ <= l)
    return;

  int m_ = (l_ + r_) / 2;
  update_impl(izq(nodo), l_, m_, l, r, val);
  update_impl(der(nodo), m_, r_, l, r, val);
  data[nodo] = Op::query(data[izq(nodo)], data[der(nodo)]);
}

template<typename Op>
requires LazyUpdate<Op>
Op::Value LazyRope<Op>::query_impl(int nodo, int l_, int r_, int l, int r) {
  propagate(nodo, l_, r_);
  if (l <= l_ && r_ <= r) // [l_, r_) contenido en [l, r)
    return data[nodo];
  if (r <= l_ || r_ <= l) // [l_, r_) intersección [l, r) es vacía
    return Op::neutQ();
  int m_ = (l_ + r_) / 2;
  return Op::query(query_impl(izq(nodo), l_, m_, l, r), query_impl(der(nodo), m_, r_, l, r));
}

#endif // LAZYROPE_H
