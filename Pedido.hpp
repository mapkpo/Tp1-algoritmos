#include <string>
using namespace std;

class Pedido{
    private:
        string cliente;
        string fruta1;
        string fruta2;
        string fruta3;
        int f1;
        int f2;
        int f3;
        bool minorista;
        bool pendiente;

    public:
        Pedido(){}
        Pedido(string nombre, string f1, string f2, string f3, int c1, int c2, int c3, bool min){
            pendiente = false;
            this->cliente = nombre;
            this->fruta1 = f1;
            this->fruta2 = f2;
            this->fruta3 = f3;
            this->f1 = c1;
            this->f2 = c2;
            this->f3 = c3;
            this->minorista = min;
        }

        void setPendiente(){
            this->pendiente = true;
        }

        bool getPendiente(){
            return pendiente;
        }
};
