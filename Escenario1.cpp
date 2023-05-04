#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Fruteria.hpp"

using namespace std;

int main() {
    cout << "                        Grupo 7    escenario 1"<< endl;
    cout<<"----------------------------------------------------------------------"<<endl;

    Fruteria* uno = new Fruteria();

    uno->agregarFruta("banana",150,uno->getBanana());
    uno->agregarFruta("pera",210,uno->getPera());
    uno->agregarFruta("manzana",150,uno->getManzana());

    uno->imprimirStock();

    uno->agregarPedido("miguel",1,1,1,true);        //true minoristas
    uno->agregarPedido("raul",1,1,1,false);         //false mayorista
    uno->agregarPedido("a",500,120,236,true);
    uno->agregarPedido("b",12,16,10,false);

    uno->imprimirPedidos();
    uno->prepararPedidos();
    uno->prepararPedidos();
    uno->imprimirPedidos();

    uno->prioridad();

    uno->imprimirStock();
    uno->agregarFruta("banana",650,uno->getBanana());
    uno->agregarFruta("pera",256,uno->getPera());
    uno->agregarFruta("manzana",320,uno->getManzana());

    uno->prepararPedidos();
    uno->prepararPedidos();
    uno->imprimirPedidos();
    uno->prepararPedidos();

    uno->imprimirStock();

    system("pause");


    

    return 0;
}
