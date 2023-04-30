#include <string>
using namespace std;

class Pedido{
    private:
        string cliente;
        int banana;
        int pera;
        int manzana;
        bool minorista;
        bool pendiente;

    public:
        Pedido(){}
        Pedido(string nombre, int banana, int pera, int manzana, bool minorista){
            pendiente = false;
            this->cliente = nombre;
            if(minorista){
            this->banana = banana;
            this->pera = pera;
            this->manzana = manzana;
            this->minorista = minorista;
            }
            else this->banana = banana * 20;
            this->pera = pera * 20;
            this->manzana = manzana * 20;
            this->minorista = minorista;
        }

        void setPendiente(){
            this->pendiente = true;
        }

        bool getPendiente(){
            return pendiente;
        }

        int getBanana(){
            return banana;
        }

        int getPera(){
            return pera;
        }

        int getManzana(){
            return manzana;
        }
};
