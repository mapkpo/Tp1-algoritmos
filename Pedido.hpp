#include <string>
using namespace std;

class Pedido{
    private:
        string cliente;
        /*string fruta1;
        string fruta2;
        string fruta3;*/
        int banana;
        int pera;
        int manzana;
        bool minorista;
        bool pendiente;

    public:
        Pedido(){}
        Pedido(string nombre, int banana, int pera, int manzana, bool min){
            pendiente = false;
            this->cliente = nombre;
            /*this->fruta1 = f1;
            this->fruta2 = f2;
            this->fruta3 = f3;*/
            this->banana = banana;
            this->pera = pera;
            this->manzana = manzana;
            this->minorista = min;
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
