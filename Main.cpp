#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Cajon.hpp"
#include "Deposito.hpp"

using namespace std;

void nuevaPila(Lista<Pila<Cajon*>*>* lista){  //crea una nueva pila en la lista
    Pila<Cajon*>* pila = new Pila<Cajon*>();
    lista->add(pila);
}

void agregarFruta(string fruta, int kilos, Lista<Pila<Cajon*>*>* lista){
    // Verificar si existe una lista de pilas de cajones o si la que esta esta llena hasta el tope y entonces crear una en ambos casos
    if (lista->esvacia() || (lista->cabeza()->tamanio() == 10 && lista->cabeza()->tope()->getCantidad() == 20)) { 
        cout<<"estaba vacia o llena se creo otra"<<endl;
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
    if (pila->pilavacia() && kilos > 200){
        int kilosTemporales = kilos;
        while(kilosTemporales>0){
            if(pila->tamanio() < 10 && kilosTemporales >= 20){
            Cajon* cajona = new Cajon(20,fruta);
            pila->apilar(cajona);
            kilosTemporales = kilosTemporales - 20;
            } else if(pila->tamanio() < 10 && kilosTemporales < 20){
                Cajon* cajona = new Cajon(kilosTemporales,fruta);
                pila->apilar(cajona);
                kilosTemporales = 0;
            } else cout<<"mas de 200"<<endl;
            agregarFruta(fruta,kilosTemporales,lista);
            break;
        }
    }

    //caso 3 pila no vacia y mas de 200 elementos
    if (!pila->pilavacia()){cout<<"por ahcer"<<endl;}
       

        

        
    

    














        /*

    // Agregar los cajones correspondientes a la pila
        if (kilos > 200){
        //recursiva hasta que sea menos de 200kg
    } else if (kilos <= 20)
    {
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
    int Cantidadfrutaqentraenlapilaactual = (200-((pila->tamanio()-1)*20+pila->tope()->getCantidad()));   */
    
    cout<<"tamanio de la lista "<<lista->size()<<endl; 
    cout<<"tamanio de la pila dentro de la lista "<<pila->tamanio()<<endl; 
    //cout<<Cantidadfrutaqentraenlapilaactual<<endl;
       
        
};


int main() {
    cout << "Hello, World!" << endl;
    
    //creo las listas de pilas de las diferentes frutas, esto seria mi deposito
   Lista<Pila<Cajon*>*>* banana = new Lista<Pila<Cajon*>*>();
   Lista<Pila<Cajon*>*>* manzana = new Lista<Pila<Cajon*>*>();
   Lista<Pila<Cajon*>*>* pera = new Lista<Pila<Cajon*>*>();

  
    agregarFruta("banana",201,banana);
    



    













    return 0;
}

