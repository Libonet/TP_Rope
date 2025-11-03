#ifndef ROPE_H
#define ROPE_H

#include <concepts>
#include <vector>

template<typename T>
concept Group = requires(T::Value a, T::Value b, T::Value c) {
typename T::Value; // hay un tipo de valores
  { T::op(a, b) } -> std::same_as<typename T::Value>; // clausura de la operacion
  // T::op(a, T::op(b, c)) == T::op(T::op(a, b), c) // asociatividad de la operacion
  { T::neut() } -> std::same_as<typename T::Value>; // existencia del neutro
  // T::op(a, T::neut()) == a // neutro por derecha
  // T::op(T::neut(), a) == a // neutro por izquierda
  { T::inv(a) } -> std::same_as<typename T::Value>; // clausura del inverso
  // T::op(a, T::inv(a)) == T::neut() // inverso por derecha
  // T::op(T::inv(a), a) == T::neut() // inverso por izquierda
};

template<typename Op>
requires Group<Op>
class Rope {
public:
    Rope(int n) { /* COMPLETAR */ }
    typename Op::Value query(int l, int r) { /* COMPLETAR */ }
    void update(int i, typename Op::Value x) { /* COMPLETAR */ }

private:
    std::vector<typename Op::Value> data;
};

#endif // ROPE_H
