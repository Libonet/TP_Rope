#ifndef __ROPEINT_H__
#define __ROPEINT_H__

#include <vector>

class RopeInt {
  public:
    // obtiene la suma de un intervalo [l, r)
    RopeInt(int tam, std::vector<int> vect);

    void update(int i, int val) { update_impl(0, 0, n, i, val); }
    int sum(int l, int r) { return sum_impl(0, 0, n, l, r); }

  private:
    void update_impl(int nodo, int l_, int r_, int i, int val);
    int sum_impl(int nodo, int l_, int r_, int l, int r);

    static int izq(int nodo) { return 2 * nodo + 1; }
    static int der(int nodo) { return 2 * nodo + 2; }

    std::vector<int> arr;
    int n; // secuencia de n elementos, 2n+1 nodos, n potencia de 2
};

#endif // __ROPEINT_H__