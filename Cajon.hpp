#include <string>
using namespace std;

class Cajon{
private:
    string tipo;
    int cantidad;
    int pesoMaximo = 20;
public:
    Cajon(){}
    Cajon(int peso, string tipo) {
        if (peso > 20){
            throw "No se puede meter";
        }
        this->tipo = tipo;
        this->cantidad = peso;
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
    int getCantidad() {
        return this->cantidad;
    }
};