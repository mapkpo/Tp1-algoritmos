#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Fruteria.hpp"

using namespace std;

int main() {
    cout << "                        Grupo 7    escenario 1"<< endl;
    cout<<"----------------------------------------------------------------------"<<endl;

    Fruteria* uno = new Fruteria();

    uno->agregarFruta("banana",500,uno->getBanana());
    uno->agregarFruta("pera",210,uno->getPera());
    uno->agregarFruta("manzana",300,uno->getManzana());

    uno->imprimirStock();

    uno->agregarPedido("miguel",1,1,1,true);
    uno->agregarPedido("raul",1,1,1,false);

    uno->imprimirPedidos();

    uno->prepararPedidos();

    uno->prepararPedidos();

    uno->imprimirPedidos();

    uno->prioridad();

    uno->imprimirStock();

    system("pause");


    

    return 0;
}
