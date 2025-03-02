#include <iostream>
#include <fstream>

using namespace std;

struct Atributo {
    string nombre;
    int cantidad;
};

class Aventurero {
    public:
        string clase;
        string faccion;
        string nombre;
        Atributo *atributos;
        int adn;

        Aventurero(string clase, string faccion, string nombre, int cantAtributos) {
            this->clase = clase;
            this->faccion = faccion;
            this->nombre = nombre;
            atributos = new Atributo[cantAtributos];
        }
};

int main() {
    return 0;
}