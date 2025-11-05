#include <vector>
#include <math.h>

class RopeInt {
  public:
    void update(int i, int val);
    int sum(int l, int r); // obtiene la suma de un intervalo [l, r)
    RopeInt(int tam, std::vector<int> vect);

  private:
    static int izq(int nodo) { return 2 * nodo + 1; }
    static int der(int nodo) { return 2 * nodo + 2; }

    std::vector<int> arr;
    int n; // secuencia de n elementos, 2n+1 nodos
    void update_impl(int nodo, int l_, int r_, int i, int val);
    int sum_impl(int nodo, int l_, int r_, int l, int r);
};

RopeInt::RopeInt(int tam, std::vector<int> vect) {
  n = pow(2, ceil(log(tam) / log(2)));
  arr = std::vector<int>(2 * n + 1);

  int i = 0;
  for (int elem : vect) {
    arr[i] = elem;
    i++;
  }
  
}

// nodo es el índice del nodo a actualizar
// l_ y r_ es el intervalo cubierto por el nodo
// i es el índice a actualizar
// val es el nuevo valor a asignar
void RopeInt::update_impl(int nodo, int l_, int r_, int i, int val) {
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

void RopeInt::update(int i, int val) {
  update_impl(0, 0, n, i, val);
}

int RopeInt::sum_impl(int nodo, int l_, int r_, int l, int r) {
  if (l <= l_ && r_ <= r) // [l_, r_) contenido en [l, r)
    return arr[nodo];
  if (l_ > r || r_ < l) // [l_, r_) intersección [l, r) es vacía
    return 0;
  int m_ = (l_ + r_) / 2;
  return sum_impl(izq(nodo), l_, m_, l, r) + sum_impl(der(nodo), m_, r_, l, r);
}

int RopeInt::sum(int l, int r) {
  // copilto callate un rato y dejame pensar oki uwu
  return sum_impl(0, 0, n, l, r);
}

// EJ 1b

/*
En los tres casos requerimos que las operaciones sean asociativas y que exista un elemento neutro. La primera puesto que es lo que nos va
a permitir poder partir los intervalos para realizar los cálculos y las actualizaciones. El elemento neutro es necesario para rellenar el
vector con el mismo y así alcanzar el tamaño deseado de 2n+1 nodos con n potencia de 2. En el caso de la suma se rellena con 0, en la 
concatenación de strings rellenaríamos con la cadena vacía y en la unión de conjuntos, con el conjunto vacío.
*/