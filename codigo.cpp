#include <iostream>
#include <fstream>
#include <cstdlib>

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
        
        int cantAtributos;
        int n_adn;
        Atributo *atributos;
        int **adn;

        Aventurero(string clase, string faccion, string nombre, int cantAtributos, int n_adn) {
            this->clase = clase;
            this->faccion = faccion;
            this->nombre = nombre;

            this->cantAtributos = cantAtributos;
            this->n_adn = n_adn;

            atributos = new Atributo[cantAtributos];
            adn = new int*[n_adn];
            for (int i = 0; i < n_adn; i++) {
                adn[i] = new int[n_adn];
            }
        }

        void guardarAtributo(int n, string nombre, int cantidad) {
            atributos[n].nombre = nombre;
            atributos[n].cantidad = cantidad;
        }

        int calcularPuntajeADN() {
            // hay que recorrer la matriz y hacer las debidas operaciones
            return 1;
        }
};

class Archivo {
    public:
        string directorio;

        void leerArchivo() {

        };
};

void leerCarpeta() {
    string directorio;
    cin >> directorio;
    directorio = "dir /b " + directorio + " > database.temp";
    system(directorio.c_str());
}

int main() {
    leerCarpeta();
    return 0;
}