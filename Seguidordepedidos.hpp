#include <cstdlib>
#include <iostream>
#include <sstream>
#define MAX 500

using namespace std;
// almacena MAX-1 elementos
// cola circular
template <class T> class Cola {
private:
    T Q[MAX];
    int pi, pf;
public:
    Cola(void) { pi = 0; pf = MAX - 1; };
    ~Cola(void);
    T tope() { return Q[pi]; };
    bool colavacia() { return pi == (pf + 1) % MAX; };
    bool colallena() { return pi == (pf + 2) % MAX; };
    void encolar(T a);
    void desencolar();
    T ultimo();
    string imprimir(string s);
};
//-------- Metodos de Cola --------------------
template <class T> void Cola<T>::encolar(T a)
{
    if (!colallena()) {
        //if (pf == MAX - 2) pf = MAX - 1;
        pf = (pf + 1) % MAX;
        Q[pf] = a;
    }
    else cout << "Cola llena" << endl;
}
template <class T> void Cola<T>::desencolar(void)
{
    if (!colavacia())pi = (pi + 1) % MAX;
    else cout << "Cola vacia" << endl;
}
template <class T> T Cola<T>::ultimo(void)
{
    return Q[pf];
}
template <class T> string Cola<T>::imprimir(string s)
{
    if (!colavacia()) {
       for (int i = pi; i != (pf + 1) % MAX; i = (i + 1) % MAX)
            cout << Q[i] << "--";
    }

    return " <<< Q";
};