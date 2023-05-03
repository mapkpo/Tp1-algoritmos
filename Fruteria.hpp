#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Cajon.hpp"
#include "Deposito.hpp"
#include "Seguidordepedidos.hpp"
#include "Pedido.hpp"

class Fruteria
{
private:
    bool priorizarMayoristas;
    Lista<Pila<Cajon*>*>* banana;
    Lista<Pila<Cajon*>*>* pera;
    Lista<Pila<Cajon*>*>* manzana;
    Cola<Pedido*>* minoristas;
    Cola<Pedido*>* mayoristas;

public:
    Fruteria();
    ~Fruteria();
    
    void prioridad()
        {
        priorizarMayoristas = !priorizarMayoristas;
        }

    void imprimirPedidos(){
        cout<<"Pedidos en espera:"<<endl;
            if(!mayoristas->colavacia()){
                cout<<"Mayorista en espera, cliente: "<<mayoristas->tope()->getNombre()<<" / con bananas, pera y manzanas: "<<mayoristas->tope()->getBanana()
                <<","<<mayoristas->tope()->getPera()<<","<<mayoristas->tope()->getManzana()<<endl;
            }
            if(!minoristas->colavacia()){
                cout<<"Menorista en espera, cliente: "<<minoristas->tope()->getNombre()<<" / con bananas, manzana y pera: "<<minoristas->tope()->getBanana()
                <<","<<minoristas->tope()->getPera()<<","<<minoristas->tope()->getManzana()<<endl;
            }
    }
   
    void agregarPedido(string cliente, int bananas, int peras, int manzanas, bool minorista1){
        //crear el pedido
        if(bananas >= 0 && peras >= 0 && manzanas >= 0){
        Pedido* nuevo = new Pedido(cliente, bananas, peras, manzanas, minorista1);
        if(minorista1){
            minoristas->encolar(nuevo);
            //cout<<"Se agrego un pedido minorista a nombre de: "<<cliente<<", "<<bananas<<" bananas, "<<peras<<" peras, "<<manzanas<<" manzanas."<<endl;
            //cout<<"----------------------------------------------------------------------"<<endl;
        } else mayoristas->encolar(nuevo);
            //cout<<"Se agrego un pedido minorista a nombre de: "<<cliente<<", "<<bananas<<" bananas, "<<peras<<" peras, "<<manzanas<<" manzanas."<<endl;
            //cout<<"----------------------------------------------------------------------"<<endl;
        } else cout<<"error"<<endl;
    }

    void prepararPedidos(){

        if(priorizarMayoristas){
            if(!mayoristas->colavacia()){
            //chequear los mayoristas 
                Pedido* pedido = mayoristas->tope();

                    if(contarStock(banana) >= pedido->getBanana() && 
                        contarStock(manzana) >= pedido->getManzana() &&
                            contarStock(pera) >= pedido->getPera()){
                                quitarFruta(pedido->getBanana(),banana);
                                quitarFruta(pedido->getManzana(),manzana);
                                quitarFruta(pedido->getPera(),pera);
                                mayoristas->desencolar();
                                cout<<"se ha completado un pedido mayorista de "<<pedido->getNombre()<<endl;
                                cout<<"----------------------------------------------------------------------"<<endl;
                                } 
                                else{
                                    cout<<"no ha completado un pedido de mayoristas se lo movido a pendientes"<<endl;
                                    cout<<"----------------------------------------------------------------------"<<endl;}
                                    }
                        
        } else if(!minoristas->colavacia()){
        Pedido* pedido = minoristas->tope();

                    if(contarStock(banana) >= pedido->getBanana() && 
                    contarStock(manzana) >= pedido->getManzana() &&
                        contarStock(pera) >= pedido->getPera()){
                            quitarFruta(pedido->getBanana(),banana);
                            quitarFruta(pedido->getManzana(),manzana);
                            quitarFruta(pedido->getPera(),pera);
                            minoristas->desencolar();
                            cout<<"se ha completado un pedido minorista de "<<pedido->getNombre()<<endl;
                            cout<<"----------------------------------------------------------------------"<<endl;
                        } else {
                                cout<<"no se ha completado un pedido minorista"<<endl;
                                cout<<"----------------------------------------------------------------------"<<endl;
                                }


            } else if(!mayoristas->colavacia()){
                Pedido* pedido = mayoristas->tope();

                            if(contarStock(banana) >= pedido->getBanana() && 
                                contarStock(manzana) >= pedido->getManzana() &&
                                    contarStock(pera) >= pedido->getPera()){
                                        quitarFruta(pedido->getBanana(),banana);
                                        quitarFruta(pedido->getManzana(),manzana);
                                        quitarFruta(pedido->getPera(),pera);
                                        mayoristas->desencolar();
                                        cout<<"se ha completado un pedido mayorista de "<<pedido->getNombre()<<endl;
                                        cout<<"----------------------------------------------------------------------"<<endl;
                                        } else {
                                            cout<<"no ha completado un pedido de mayoristas"<<endl;
                                            cout<<"----------------------------------------------------------------------"<<endl;
                                            }
    }
    }

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
       
    void nuevaPila(Lista<Pila<Cajon*>*>* lista){  //crea una nueva pila en la lista
        Pila<Cajon*>* pila = new Pila<Cajon*>();
        lista->add(pila);
    }

    void agregarFruta(string fruta, int kilos, Lista<Pila<Cajon*>*>* lista){
        // Verificar si existe una lista de pilas de cajones o si la que esta esta llena hasta el tope y entonces crear una en ambos casos
        if (lista->esvacia() || (lista->cabeza()->tamanio() == 10 && lista->cabeza()->tope()->getCantidad() == 20)) { 
            //cout<<"La lista estaba vacia o llena, se creo otra"<<endl;
            //cout<<"----------------------------------------------------------------------"<<endl;
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
                //cout<<"se lleno la pila actual se creo otra"<<endl;
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
        //cout<<"Se agregaron "<<kilos<<" kilos de "<<lista->cabeza()->tope()->getTipo()<<endl;
        //cout<<"El tamanio de la lista es: "<<lista->size()<<endl; 
        //cout<<"tamanio de la pila dentro de la lista es: "<<pila->tamanio()<<endl;  
    };

    void imprimirStock(){
        cout<<"_____Stock_____"<<endl;
        cout<<"banana: "<<contarStock(banana)<<endl;
        cout<<"pera: "<<contarStock(pera)<<endl;
        cout<<"manzana: "<<contarStock(manzana)<<endl;
        cout<<"----------------------------------------------------------------------"<<endl;
    }

    void quitarFruta(int cantidad, Lista<Pila<Cajon*>*>* lista){
        string fruta = lista->cabeza()->tope()->getTipo();
        int temp = contarStock(lista);
        temp = temp - cantidad;
        if(cantidad > contarStock(lista)){
            cout<<"No hay suficiente stock"<<endl;
            cout<<"----------------------------------------------------------------------"<<endl;
        
        } else { while(!lista->esvacia()){
            lista->borrar();
        } if(temp != 0){
        agregarFruta(fruta,temp,lista);
        }
        }
    }

    Lista<Pila<Cajon*>*>* getBanana(){
        return banana;
    }

    Lista<Pila<Cajon*>*>* getManzana(){
        return manzana;
    }

    Lista<Pila<Cajon*>*>* getPera(){
        return pera;
    }

};

Fruteria::Fruteria()
{
    banana = new Lista<Pila<Cajon*>*>();
    manzana = new Lista<Pila<Cajon*>*>();
    pera = new Lista<Pila<Cajon*>*>();
    minoristas = new Cola<Pedido*>();
    mayoristas = new Cola<Pedido*>();
    priorizarMayoristas = true;
}




