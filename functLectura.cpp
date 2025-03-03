/*
    TESTS DE LA FUNCION ADN
    
    ESTE ARCHIVO NO FORMA PARTE DEL PROYECTO
*/

#include <iostream>
#include <fstream>


using namespace std;

struct Atributo {
    string nombre;
    string cantidad;
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

        Aventurero(int cantAtributos) {
            atributos = new Atributo[cantAtributos];
        }

        int calcularPuntajeADN() {
            // hay que recorrer la matriz y hacer las debidas operaciones
            return 1;
        }
};

/*class Archivo {
    public:
        string directorio;

        void leerArchivo() {
            ifstream archivo(directorio);
            if (archivo.is_open()) {
                string linea;
                while (archivo >> linea) {
                    cout << linea << endl;
                }
                archivo.close();
            } else {
                cout << "No se pudo abrir el archivo" << endl;
            }
        };
};*/

/*class Datos : Archivo {
    public:

};*/

void ArchivoLeer(){
    string directorio = "../output/Aventurero.txt";
    Aventurero aventurero(10);
    ifstream archivo(directorio);
    
    if (archivo.is_open()) {

        string linea;
        /*for (int i = 0; getline(archivo,linea) ; i++) {
            for (int i = 0; i<linea.length() ; i++)
            {
                if(linea[i]==':'||linea[i]=='|'){
                    linea[i]= ' ';
                }
            }
            cout << linea << endl;
        }*/

        for (int i = 0; archivo>>linea && linea!="ADN"; i++) {
            if(linea=="Clase"){
                getline(archivo,linea);
                cout << linea << endl;
                aventurero.clase = linea;
                i--;
                continue;
            }
            if(linea=="Faccion"){
                getline(archivo,linea);
                cout << linea << endl;
                aventurero.faccion = linea;
                i--;
                continue;
            }
            if(linea=="Nombre"){
                getline(archivo,linea);
                cout << linea << endl;
                aventurero.nombre = linea;
                i--;
                continue;
            }
            else if(linea!="ATRIB"){
                cout << linea << endl;
                aventurero.atributos[i].nombre = linea;
                getline(archivo,linea);
                cout << linea << endl;
                aventurero.atributos[i].cantidad = linea;
            }
            else{
                i--;
            }
        }
        archivo.close();
    }
    cout << aventurero.faccion << endl;
    cout << aventurero.clase << endl;
    cout << "Este es el ADN perteneciente a: " << aventurero.nombre<<endl;
    
    for (int i = 0; i < 10; i++)
    {
        cout << aventurero.atributos[i].nombre << " " << aventurero.atributos[i].cantidad << endl;
    }
    
}


void inicializar() {
    ArchivoLeer();
};

int main() {
    inicializar();
    return 0;
}