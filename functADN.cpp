/*
    TESTS DE LA FUNCION ADN
    
    ESTE ARCHIVO NO FORMA PARTE DEL PROYECTO
*/
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "./output/color.hpp" // Eliminar, esto es para los colores

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


int main() {    
    Aventurero test("Guerrero", "Corridas En Frio", "Leo", 5, 5);
    int SUMATORIA = 0;

    // La asignacion se hara tal cual asi
    for (int i = 0; i < test.n_adn; i++) {
        for (int j = 0; j < test.n_adn; j++) {
            cin >> test.adn[i][j];
        }
    }

    // Recorrer toda la matriz
    cout << endl << hue::aqua << "[Recorrido Matriz] Estoy mostrando lo siguiente: " << hue::reset << endl;

    for (int i = 0; i < test.n_adn; i++) {
        for (int j = 0; j < test.n_adn; j++) {
            cout << test.adn[i][j] << " ";
        }
        cout << endl;
    }
    cout << hue::aqua << "Este es el ADN perteneciente a: " << test.nombre << endl;


    // Lectura de campos verdes
    cout << endl << hue::green << "Ahora leere los verdes: " << endl;
    for (int i = 0; i < test.n_adn; i++) {
        cout << hue::green << test.adn[i][i] << " ";
        SUMATORIA += test.adn[i][i];
    }

    cout << endl << endl; 

    // Importante, ahora debemos sustraer la mitad
    int mitad = ((test.n_adn/2) + 1) - 1;

    cout << hue::reset << "La mitad sera el numero: " <<  mitad;
    cout << endl << endl; 

    
    // Ahora los azules, se usa mitad
    cout << hue::blue << "Numeros Azules: " << endl;

    for (int i = 0; i < test.n_adn; i++) {
        if (!(i == mitad)) {
            cout << hue::blue << test.adn[i][mitad] << " ";
            SUMATORIA += test.adn[i][mitad];
        } else {
            cout << "[MITAD:" << test.adn[i][mitad] << "] ";
        }
    }

    cout << endl << endl;

    // Ahora los Naranjas
    cout << hue::light_yellow << "Numeros Naranjas: " << endl;
    for (int i = 0; i < test.n_adn; i++) {
        if (!(i == mitad)) {
            cout << hue::light_yellow << test.adn[mitad][i] << " ";
            SUMATORIA += test.adn[mitad][i];
        } else {
            cout << "[MITAD:" << test.adn[mitad][i] << "] ";
        }
    }

    cout << endl << endl;

    cout << hue::yellow << "Ahora los Amarillos:" << endl;
    // Ahora la amarilla 
    for (int i = 0, j = test.n_adn - 1; i < test.n_adn; i++, j--) {
        if (!(i == mitad) && !(j == mitad) ) {
            cout << hue::yellow << test.adn[i][j] << " ";
            SUMATORIA += test.adn[i][j];
            //break;
        } else if (i== mitad && j == mitad) {
            cout << "[MITAD:" << test.adn[i][j] << "] ";
            //break;
        }
    }

    cout << endl << hue::reset;

    cout << hue::aqua << "La sumatoria de los numeros es: " << hue::reset << SUMATORIA << endl;

    return 0;

}