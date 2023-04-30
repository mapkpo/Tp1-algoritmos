#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Cajon.hpp"
#include "Deposito.hpp"
#include "Seguidordepedidos.hpp"
#include "Pedido.hpp"
bool priorizarMayoristas;


using namespace std;

void prioridad(bool a){
    priorizarMayoristas = a;
}

void nuevaPila(Lista<Pila<Cajon*>*>* lista){  //crea una nueva pila en la lista
    Pila<Cajon*>* pila = new Pila<Cajon*>();
    lista->add(pila);
}

void agregarFruta(string fruta, int kilos, Lista<Pila<Cajon*>*>* lista){
    // Verificar si existe una lista de pilas de cajones o si la que esta esta llena hasta el tope y entonces crear una en ambos casos
    if (lista->esvacia() || (lista->cabeza()->tamanio() == 10 && lista->cabeza()->tope()->getCantidad() == 20)) { 
        cout<<"La lista estaba vacia o llena, se creo otra"<<endl;
        nuevaPila(lista);
    }
    
    // Obtener la pila de la lista (en este caso seria la de inicio)
    Pila<Cajon*>* pila = lista->cabeza();

    
    //caso 1 pila vacia y menos de 200kg
    if (pila->pilavacia() && kilos <= 200){
        if (kilos <= 20){
        Cajon* cajona = new Cajon(kilos,fruta);
        pila->apilar(cajona);
    } else {
        int kilosTemporales = kilos;
        while (kilosTemporales > 20){
            Cajon* cajona = new Cajon(20,fruta);
            pila->apilar(cajona);
            kilosTemporales = kilosTemporales - 20;                
        }
        Cajon* cajon = new Cajon(kilosTemporales,fruta);
        pila->apilar(cajon);    
        }
    }

   //caso 2 pila vacia y mas de 200 elementos
    else if (pila->pilavacia() && kilos > 200) {
    int kilosTemporales = kilos;
    while (kilosTemporales > 0) {
        // Crear una nueva pila si la actual está llena
        if (pila->tamanio() == 10) {
            cout<<"se lleno la pila actual se creo otra"<<endl;
            nuevaPila(lista);
            pila = lista->cabeza();
        }
        
        // Crear cajones de fruta de 20 kg hasta llegar a los 200 kg
        if (kilosTemporales >= 200) {
            for (int i = 0; i < 10; i++) {
                Cajon* cajona = new Cajon(20, fruta);
                pila->apilar(cajona);
            }
            kilosTemporales -= 200;
        } else {
            // Crear cajones con la fruta sobrante
            int kilosCajon = (kilosTemporales > 20) ? 20 : kilosTemporales;
            Cajon* cajon = new Cajon(kilosCajon, fruta);
            pila->apilar(cajon);
            kilosTemporales -= kilosCajon;
        }
    }

    
}

// Caso 3: pila no vacía
else {
    // Obtener el cajón de la pila actual que está en el tope
    Cajon* cajon = pila->tope();
    
    // Verificar si el cajón tiene espacio para la nueva fruta
    if (cajon->getCantidad() < 20) {
        // Calcular cuántos kilos de fruta caben en el cajón actual
        int kilosRestantes = 20 - cajon->getCantidad();
        
        // Verificar si los kilos de fruta que se quieren agregar caben en el cajón actual
        if (kilos <= kilosRestantes) {
            // Agregar la fruta al cajón actual
            cajon->agregarFruta(kilos);
        }
        else {
            // Agregar la fruta al cajón actual hasta completarlo
            cajon->agregarFruta(kilosRestantes);
            int kilosTemporales = kilos - kilosRestantes;
            
            // Crear una nueva pila en la lista si la actual está llena
            if (pila->tamanio() == 10) {
                nuevaPila(lista);
                pila = lista->cabeza();
            }
            
            // Crear nuevos cajones y agregarlos a la pila actual hasta que se agreguen todos los kilos de fruta
            while (kilosTemporales > 0) {
                if (kilosTemporales <= 20) {
                    Cajon* nuevoCajon = new Cajon(kilosTemporales, fruta);
                    pila->apilar(nuevoCajon);
                    kilosTemporales = 0;
                }
                else {
                    Cajon* nuevoCajon = new Cajon(20, fruta);
                    pila->apilar(nuevoCajon);
                    kilosTemporales -= 20;
                    
                    // Crear una nueva pila en la lista si la actual está llena
                    if (pila->tamanio() == 10) {
                        nuevaPila(lista);
                        pila = lista->cabeza();
                    }
                }
            }
        }
    }
    else {
        // Crear una nueva pila en la lista si la actual está llena
        if (pila->tamanio() == 10) {
            nuevaPila(lista);
            pila = lista->cabeza();
        }
        
        // Crear un nuevo cajón y agregarlo a la pila actual
        Cajon* nuevoCajon = new Cajon(kilos, fruta);
        pila->apilar(nuevoCajon);
    }
}
    cout<<"Se agregaron "<<kilos<<" kilos de "<<lista->cabeza()->tope()->getTipo()<<endl;
    cout<<"El tamanio de la lista es: "<<lista->size()<<endl; 
    cout<<"tamanio de la pila dentro de la lista es: "<<pila->tamanio()<<endl;  
};

int contarStock(Lista<Pila<Cajon*>*>* lista){
    if(lista->esvacia()){ //si la lista es vacia retorna cero
        return 0;
    }
    Pila<Cajon*>* pila = lista->cabeza();
    if (pila->pilavacia()){ //si la pila esta vacia
        return 0;
    } else if (lista->size() == 1  && pila->tamanio()<= 10){   //si la lista tiene una sola pila
        return ((pila->tamanio()-1)*20+pila->tope()->getCantidad());    //si la lista tiene mas de una pila
    } else return (((lista->size()-1)*200) + ((pila->tamanio()-1)*20+pila->tope()->getCantidad())); 
}

void quitarFruta(int cantidad, Lista<Pila<Cajon*>*>* lista){
    string fruta = lista->cabeza()->tope()->getTipo();
    int temp = contarStock(lista);
    temp = temp - cantidad;
    if(cantidad > contarStock(lista)){
        cout<<"No hay suficiente stock"<<endl;
    
    } else { while(!lista->esvacia()){
        lista->borrar();
    } if(temp != 0){
    agregarFruta(fruta,temp,lista);
    }
    }
}

void agregarPedido(string cliente, int bananas, int peras, int manzanas, bool minorista, Cola<Pedido*>* minoristas, Cola<Pedido*>* mayoristas){
    //crear el pedido
    if(bananas >= 0 && peras >= 0 && manzanas >= 0){
    Pedido* nuevo = new Pedido(cliente, bananas, peras, manzanas, minorista);
    if(minorista){
        minoristas->encolar(nuevo);
        cout<<"Se agrego un pedido minorista a nombre de: "<<cliente<<", "<<bananas<<" bananas, "<<peras<<" peras, "<<manzanas<<" manzanas."<<endl;
    } else mayoristas->encolar(nuevo);
        cout<<"Se agrego un pedido minorista a nombre de: "<<cliente<<", "<<bananas<<" bananas, "<<peras<<" peras, "<<manzanas<<" manzanas."<<endl;
    } else cout<<"error"<<endl;
}

void prepararPedidos(Cola<Pedido*>* minoristas,Cola<Pedido*>* minoristasPendientes,Cola<Pedido*>* mayoristas,Cola<Pedido*>* mayoristasPendientes,
Lista<Pila<Cajon*>*>* listabanana, Lista<Pila<Cajon*>*>* listapera, Lista<Pila<Cajon*>*>* listamanzana){

    if(priorizarMayoristas){
        if(!mayoristasPendientes->colavacia()){
            //cheaquear los pendientes mayoristas
            Pedido* pedido = mayoristasPendientes->tope();

            //chequeo si hay suficiente fruta para completar el pedido
            if(contarStock(listabanana) >= pedido->getBanana() && 
                contarStock(listamanzana) >= pedido->getManzana() &&
                    contarStock(listapera) >= pedido->getPera()){
                        quitarFruta(pedido->getBanana(),listabanana);
                        quitarFruta(pedido->getManzana(),listamanzana);
                        quitarFruta(pedido->getPera(),listapera);
                        mayoristasPendientes->desencolar();
                        cout<<"se ha completado un pedido de mayoristas pendientes"<<endl;
                    }

        } else if(!mayoristas->colavacia()){
            //chequear los mayoristas 

            Pedido* pedido = mayoristas->tope();

                if(contarStock(listabanana) >= pedido->getBanana() && 
                contarStock(listamanzana) >= pedido->getManzana() &&
                    contarStock(listapera) >= pedido->getPera()){
                        quitarFruta(pedido->getBanana(),listabanana);
                        quitarFruta(pedido->getManzana(),listamanzana);
                        quitarFruta(pedido->getPera(),listapera);
                        mayoristas->desencolar();
                        cout<<"se ha completado un pedido mayorista"<<endl;
                    } else {pedido->getPendiente(); //si no se puede completar el pedido lo marco como pendiente y lo muevo a la cola de mayoristas pendientes
                            mayoristasPendientes->encolar(pedido);
                            mayoristas->desencolar();
                            cout<<"no ha completado un pedido de mayoristas se lo movido a pendientes"<<endl;}

            } else if(!minoristasPendientes->colavacia()){
                //cehquea pendientes minoristas
                Pedido* pedido = minoristasPendientes->tope();

                    if(contarStock(listabanana) >= pedido->getBanana() && 
                    contarStock(listamanzana) >= pedido->getManzana() &&
                    contarStock(listapera) >= pedido->getPera()){
                        quitarFruta(pedido->getBanana(),listabanana);
                        quitarFruta(pedido->getManzana(),listamanzana);
                        quitarFruta(pedido->getPera(),listapera);
                        minoristasPendientes->desencolar();
                        cout<<"se ha completado un pedido de minorista pendiente"<<endl;
                    }
                
                } else if(!minoristas->colavacia()){
                        //chequear minoristas

                Pedido* pedido = minoristas->tope();

                if(contarStock(listabanana) >= pedido->getBanana() && 
                contarStock(listamanzana) >= pedido->getManzana() &&
                    contarStock(listapera) >= pedido->getPera()){
                        quitarFruta(pedido->getBanana(),listabanana);
                        quitarFruta(pedido->getManzana(),listamanzana);
                        quitarFruta(pedido->getPera(),listapera);
                        minoristas->desencolar();
                        cout<<"se ha completado un pedido"<<endl;
                    } else {pedido->getPendiente(); //si no se puede completar el pedido lo marco como pendiente y lo muevo a la cola de mayoristas pendientes
                            minoristasPendientes->encolar(pedido);
                            minoristas->desencolar();
                            cout<<"no ha completado un pedido minorista se lo movido a pendientes"<<endl;}
                    }

} else if(!minoristasPendientes->colavacia()){ //seria copiar lo de arriba pero en distinto orden XDDDDDDDDDD

    } else if(!minoristas->colavacia()){

        } else if(!mayoristasPendientes->colavacia()){

            } else if(!mayoristasPendientes->colavacia()){

                }


}

int main() {
    cout << "Hello, World!" << endl;

    //le damos prioridad a mayoristas
    prioridad(true);
    
    //creo las listas de pilas de las diferentes frutas, esto seria mi deposito
    Lista<Pila<Cajon*>*>* banana = new Lista<Pila<Cajon*>*>();
    Lista<Pila<Cajon*>*>* manzana = new Lista<Pila<Cajon*>*>();
    Lista<Pila<Cajon*>*>* pera = new Lista<Pila<Cajon*>*>();

    Cola<Pedido*>* minoristas = new Cola<Pedido*>();
    Cola<Pedido*>* minoristasPendientes = new Cola<Pedido*>();
    Cola<Pedido*>* mayoristas = new Cola<Pedido*>();
    Cola<Pedido*>* mayoristasPendientes = new Cola<Pedido*>();
    

    //cout<<contarStock(banana)<<endl;
    agregarFruta("banana",200,banana);
    //cout<<contarStock(banana)<<endl;
    agregarFruta("banana",20,banana);
    //cout<<contarStock(banana)<<endl;
    agregarFruta("manzana",350,manzana);
    agregarFruta("pera",180,pera);
    quitarFruta(80,manzana);
    //cout<<contarStock(banana)<<endl;
    agregarPedido("raul",1,1,0,false,minoristas,mayoristas);
    //cout<<minoristas->colavacia()<<endl;
    prepararPedidos(minoristas,minoristasPendientes,mayoristas,mayoristasPendientes,banana,manzana,pera);


    
    



    













    return 0;
}
