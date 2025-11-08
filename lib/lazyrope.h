#ifndef LAZYROPE_H
#define LAZYROPE_H

#include <concepts>
#include <vector>

template <typename T>
concept LazyUpdate =
    requires { typename T::Value; } &&
    requires(T::Value a, T::Value b, T::Value c) {
      // typename T::Value; // hay un tipo de valores
        { T::query(a, b) } -> std::same_as<typename T::Value>; // clausura de la operacion
        // T::query(a, T::query(b, c)) == T::query(T::query(a, b), c) // asociatividad de la operacion
        { T::neutQry() } -> std::same_as<typename T::Value>; // existencia del neutro
        // T::query(a, T::neut()) == a // neutro por derecha
        // T::query(T::neut(), a) == a // neutro por izquierda
    } &&
    requires(T::Value a, T::Value b, T::Value c, int len) {
      // typename T::Value; // hay un tipo de valores
        { T::update(a, b) } -> std::same_as<typename T::Value>; // clausura de la operacion
        // T::update(a, T::update(b, c)) == T::update(T::update(a, b), c) // asociatividad de la operacion
        // T::update(a, b) == T::update(b, a) // conmutatividad de la operacion
        { T::neutUpd() } -> std::same_as<typename T::Value>; // existencia del neutro
        // T::update(a, T::neut()) == a // neutro por derecha
        // T::update(T::neut(), a) == a // neutro por izquierda
        { T::apply(a, b, len) } -> std::same_as<typename T::Value>; // aplica la actualizacion
    };
    

template<typename Op>
requires LazyUpdate<Op>
class LazyRope {
  public:
    LazyRope(int tam, std::vector<typename Op::Value> vect);
    void update(int l, int r, typename Op::Update upd) { update_impl(0, 0, n, l, r, upd); }
    Op::Value query(int l, int r) { return query_impl(0, 0, n, l, r);}
    void propagate(int nodo, int l_, int r_);

  private:
    void update_impl(int nodo, int l_, int r_, int l, int r, typename Op::Update upd);
    Op::Value query_impl(int nodo, int l_, int r_, int l, int r);
    
    static int izq(int nodo) { return 2 * nodo + 1; }
    static int der(int nodo) { return 2 * nodo + 2; }
    
    std::vector<typename Op::Value> arr;
    std::vector<typename Op::Update> lazy;
    int n; // secuencia de n elementos, 2n+1 nodos
};

template<typename Op>
requires LazyUpdate<Op>
LazyRope<Op>::LazyRope(int tam, std::vector<typename Op::Value> vect) {
  n = pow(2, ceil(log(tam) / log(2)));
  arr = std::vector<typename Op::Value>(2 * n + 1, Op::neutUpd());
  lazy = std::vector<typename Op::Value>(2 * n + 1, Op::neutUpd());

  int i = 0;
  for (int elem : vect) {
    update(i, i + 1, elem);
    i++;
  }

  for (; i < 2*n+1; i++) {
    update(i, i + 1, Op::neutQry());
  }

  
}

template<typename Op>
requires LazyUpdate<Op>
void LazyRope<Op>::propagate(int nodo, int l_, int r_) {
  int len = r_ - l_;
  if (len > 1) { // no es hoja, combino actualizaciones en los hijos
    lazy[izq(nodo)] = Op::update(lazy[izq(nodo)], lazy[nodo]);
    lazy[der(nodo)] = Op::update(lazy[der(nodo)], lazy[nodo]);
  }
  
  arr[nodo] = Op::apply(arr[nodo], lazy[nodo], len);
  lazy[nodo] = Op::neutUpd();
}

template<typename Op>
requires LazyUpdate<Op>
void LazyRope<Op>::update_impl(int nodo, int l_, int r_, int l, int r, typename Op::Update upd) {
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
  arr[nodo] = Op::query(arr[izq(nodo)], arr[der(nodo)]);
}

template<typename Op>
requires LazyUpdate<Op>
Op::Value LazyRope<Op>::query_impl(int nodo, int l_, int r_, int l, int r) {
  if (l <= l_ && r_ <= r) // [l_, r_) contenido en [l, r)
    return Op::update(arr[nodo], lazy[nodo]);
  if (r <= l_ || r_ <= l) // [l_, r_) intersección [l, r) es vacía
    return Op::neutQry();
  propagate(nodo, l_, r_);
  int m_ = (l_ + r_) / 2;
  return Op::query(query_impl(izq(nodo), l_, m_, l, r), query_impl(der(nodo), m_, r_, l, r));
  
}
#endif // LAZYROPE_H
