#ifndef __LAZYROPEINT_H__
#define __LAZYROPEINT_H__

#include <vector>

class LazyRopeInt {
  public:
    // obtiene la suma de un intervalo [l, r)
    LazyRopeInt(int tam, std::vector<int> vect);

    void update(int l, int r, int upd) { update_impl(0, 0, n, l, r, upd); }
    int sum(int l, int r) { return sum_impl(0, 0, n, l, r); }

  private:
    void update_impl(int nodo, int l_, int r_, int l, int r, int upd);
    int sum_impl(int nodo, int l_, int r_, int l, int r);

    static int izq(int nodo) { return 2 * nodo + 1; }
    static int der(int nodo) { return 2 * nodo + 2; }

    void propagate(int nodo, int l_, int r_);

    std::vector<int> arr;
    std::vector<int> lazy;
    int n; // secuencia de n elementos, 2n+1 nodos, n potencia de 2
};

#endif // __LAZYROPEINT_H__