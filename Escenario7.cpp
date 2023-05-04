#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Fruteria.hpp"

using namespace std;

int main() {
    cout << "               Grupo 7    escenario 7"<< endl;
    cout<<"--------------No alcanza stock p/ pedidos mayor. y si p/ minor. (Prioridad Mayor.)-------------"<<endl;

    Fruteria* uno = new Fruteria();

 	//uno->prioridad(); //Prioridad Min
 	
 
    uno->agregarFruta("banana",100,uno->getBanana());
    uno->agregarFruta("pera",100,uno->getPera());
    uno->agregarFruta("manzana",100,uno->getManzana());

    uno->imprimirStock();
 
    uno->agregarPedido("miguel",20,20,30,true);
	uno->agregarPedido("miguelo",20,20,20,true);	 // true = minorista
    uno->agregarPedido("raul",100,10,10,false);      //false = mayorista
 


    uno->imprimirPedidos();

    uno->prepararPedidos();

    uno->prepararPedidos();

    uno->imprimirPedidos();

    

    uno->imprimirStock();


    system("pause");
    
    ////////////////////////////////////////////////////
    
    

    return 0;
}
