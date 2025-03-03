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

        int puntajeADN = 0;

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

        void asignarADN () {
            for (int i = 0; i < n_adn; i++) {
                for (int j = 0; j < n_adn; j++) {
                    cin >> adn[i][j];
                }
            }
        }

        int calcularPuntajeADN() {
            int mitad = ((n_adn/2) + 1) - 1; // Mitad de la matriz
            int mult = 1; // Valor base de multiplicacion

            // Verdes
            for (int i = 0; i < n_adn; i++) {
                puntajeADN += adn[i][i];
                adn[i][i] = -1;
            }

            // Azules
            for (int i = 0; i < n_adn; i++) {
                if (!(i == mitad)) {
                    puntajeADN += adn[i][mitad];
                    adn[i][mitad] = -1;
                }
            }

            // Naranjas
            for (int i = 0; i < n_adn; i++) {
                if (!(i == mitad)) {
                    puntajeADN += adn[mitad][i];
                    adn[mitad][i] = -1;
                }
            }

            // Amarillos
            for (int i = 0, j = n_adn - 1; i < n_adn; i++, j--) {
                if (!(i == mitad) && !(j == mitad) ) {
                    puntajeADN += adn[i][j];
                    adn[i][j] = -1;
                } 
            }

            // Multiplicar puntaje blancos
            for (int i = 0; i < n_adn; i++) {
                for (int j = 0; j < n_adn; j++) {
                    if (adn[i][j] == -1) continue;
                    mult *= adn[i][j];
                }
            }
            
            // Segun la formula dada:
            mult /= 4;
            puntajeADN = mult - puntajeADN; 
            return puntajeADN; 
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
    Aventurero test("Guerrero", "Corridas En Frio", "Leo", 5, 5);
    test.asignarADN();
    cout << test.calcularPuntajeADN() << endl;
    return 0;
}