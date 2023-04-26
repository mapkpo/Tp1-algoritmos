#include <string>
using namespace std;

class Cajon {
private:
    int id;
    string tipo;
    double cantidad;
    double pesoMaximo;
public:
    Cajon(int id, string tipo, double pesoMaximo = 20.0) {
        this->id = id;
        this->tipo = tipo;
        this->cantidad = 0.0;
        this->pesoMaximo = pesoMaximo;
    }
    void agregarFruta(double cantidad) {
        if (this->cantidad + cantidad > this->pesoMaximo) {
            throw "El cajón está lleno";
        }
        this->cantidad += cantidad;
    }
    void quitarFruta(double cantidad) {
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
