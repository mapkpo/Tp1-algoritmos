#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Fruteria.hpp"

using namespace std;

int main() {
    cout << "               Grupo 7    escenario 2"<< endl;
    cout<<"--------------Alcanza stock p/ pedidos mayor. y no p/ minor. (Prioridad Minor.)-------------"<<endl;

    Fruteria* uno = new Fruteria();

 	uno->prioridad(); //Prioridad Min
 	
 
    uno->agregarFruta("banana",100,uno->getBanana());
    uno->agregarFruta("pera",100,uno->getPera());
    uno->agregarFruta("manzana",100,uno->getManzana());
 
    uno->imprimirStock();

    uno->agregarPedido("miguel",200,200,300,true);	 // true = minorista
    uno->agregarPedido("raul",4,2,2,false);      //false = mayorista
 


    uno->imprimirPedidos();

    uno->prepararPedidos();

    uno->prepararPedidos();

    uno->imprimirPedidos();

    

    uno->imprimirStock();


    system("pause");
    
    ////////////////////////////////////////////////////
    
    

    return 0;
}
