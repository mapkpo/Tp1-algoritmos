#include <string>
using namespace std;

class Cajon {
private:
    int id;
    string tipo;
    int cantidad;
    int pesoMaximo;
public:
    Cajon(int id, string tipo, int pesoMaximo = 20) {
        this->id = id;
        this->tipo = tipo;
        this->cantidad = 0;
        this->pesoMaximo = pesoMaximo;
    }
    void agregarFruta(int cantidad) {
        if (this->cantidad + cantidad > this->pesoMaximo) {
            throw "El cajón está lleno";
        }
        this->cantidad += cantidad;
    }
    void quitarFruta(int cantidad) {
        if (this->cantidad < cantidad) {
            throw "No hay suficiente fruta en el cajón";
        }
        this->cantidad -= cantidad;
    }
    bool estaLleno() {
        if (this->cantidad == this->pesoMaximo){
            return true;
        } else {
            return false;
        }
    }
    string getTipo() {
        return this->tipo;
    }
    double getCantidad() {
        return this->cantidad;
    }
};
