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

        Aventurero() {
            this->clase = "";
            this->faccion = "";
            this->nombre = "";

            this->cantAtributos = 0;
            this->n_adn = 0;
        }

        void asignarAtributos(int cantAtributos) {
            this->cantAtributos = cantAtributos;
            atributos = new Atributo[cantAtributos];
        }

        void asignarADN(int n_adn) {
            this->n_adn = n_adn;
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

class Directorio {
    private:
        void crearArrayArchivos(int num) {
            archivos = new string[num];
        }

    public:
        string directorio;
        string *archivos;
        int cantArchivos = 0;

        void leerCarpeta(string directorio) {
            directorio = "dir /b " + directorio + " > database.temp";
            system(directorio.c_str());

            ifstream archivo("database.temp");
            string linea;
            if (!archivo.is_open()) return;

            while (getline(archivo, linea)) {
                cantArchivos++;
            }

            crearArrayArchivos(cantArchivos);

            archivo.close();
            archivo.open("database.temp");
            if (!archivo.is_open()) return;

            for (int i = 0; i < cantArchivos; i++) {
                getline(archivo, linea);
                archivos[i] = linea;
            }
            
            system("del database.temp");
        }
};

class Funciones {

};

class Inicializador : Directorio, Funciones {
    
    private:
        void crearArrayAventureros(int num) {
            aventurero = new Aventurero[num]();
        }

        // nombre del archivo, iteracion
        void asignarAventurero(string dir_archivo, int iterador) {
            int cantAtributos = 0;

            string direccion = "D:\\Biblioteca\\Documentos\\Proyectos\\AyP\\Proyecto-Gremio_de_Aventureros-AyP\\database\\" + dir_archivo;

            ifstream archivo(direccion);
            
            // acondicionamos el archivo para ser leido sin contar espacios ni simbolos
            if (archivo.is_open()) {
                ofstream archivo_manipulado;
                archivo_manipulado.open("archivo_manipulado.temp");
                
                string linea;

                int posAtributos=101, posADN=101;
                for (int i = 0; getline(archivo,linea) ; i++) {

                    if(linea=="ATRIB "){
                        posAtributos = i;
                    }
                    else if(linea=="ADN "){
                        posADN = i;
                    }
                    if(i>posAtributos && i<posADN){
                        cantAtributos ++;
                    }

                    for (int i = 0; i<linea.length() ; i++)
                    {
                        if(linea[i]==':'||linea[i]=='|'){
                            linea[i]= ' ';
                            archivo_manipulado << linea[i];
                        }
                        else
                        {
                            archivo_manipulado << linea[i];
                        }
                    }
                    archivo_manipulado<< endl;
                }
                archivo_manipulado.close();
                archivo.close();
            }
            
            
            // leemos el archivo manipulado y guardamos los datos en la estructura aventurero
            aventurero[iterador].asignarAtributos(cantAtributos);

            ifstream archivo_manipulado("archivo_manipulado.temp");

            if(archivo_manipulado.is_open()){ 
                string linea;
                for (int i = 0; archivo_manipulado>>linea && linea!="ADN"; i++) {
                    if(linea=="Clase"){
                        getline(archivo_manipulado,linea);
                        aventurero[iterador].clase = linea;
                        i--;
                        continue;
                    }
                    if(linea=="Faccion"){
                        getline(archivo_manipulado,linea);
                        aventurero[iterador].faccion = linea;
                        i--;
                        continue;
                    }
                    if(linea=="Nombre"){
                        getline(archivo_manipulado,linea);
                        aventurero[iterador].nombre = linea;
                        i--;
                        continue;
                    }
                    else if(linea!="ATRIB"){
                        aventurero[iterador].atributos[i].nombre = linea;
                        getline(archivo_manipulado,linea);

                        //aventurero[iterador].atributos[i].cantidad = linea;
                        continue;
                    }
                    else{
                        i--;
                    }
                }
                archivo.close();
            }
            
            cout << "Clase: " << aventurero[iterador].clase << endl;
            cout << "Faccion: " << aventurero[iterador].faccion << endl;
            cout << "Nombre: " << aventurero[iterador].nombre << endl;
            cout << "Atributos: " << endl;
            for (int i = 0; i < cantAtributos; i++) 
                cout << aventurero[iterador].atributos[i].nombre << ": " << aventurero[iterador].atributos[i].cantidad << endl;
        }
    
        void asignarAventureros() {
            for (int i = 0; i < cantArchivos; i++) {
                asignarAventurero(archivos[i], i);
            }
        }

    public:
        Aventurero *aventurero;

        void iniciar() {
            string dato;
        
            while(true) {
                cin >> dato;
                if(dato == "CARGAR") {
                    cin >> directorio;
                    leerCarpeta(directorio);
                    crearArrayAventureros(2); // ASIGNADO MANUALMENTE
                    asignarAventureros();
                } else if (dato == "BUSCAR") {
                    cout << "estoy en la funcion BUSCAR" << endl;
                } else if (dato == "ORDENAR") {
                    cout << "estoy en la funcion ORDENAR" << endl;
                } else if (dato == "SELECCIONAR") {
                    cout << "estoy en la funcion SELECCIONAR" << endl;
                } else if (dato == "IMPRIMIR") {
                    cout << "estoy en la funcion IMPRIMIR" << endl;
                }
            }
        }
};




int main() {
    //Aventurero test("Guerrero", "Corridas En Frio", "Leo", 5, 5);
    //test.asignarADN();
    //cout << test.calcularPuntajeADN() << endl;

    Inicializador programa;
    programa.iniciar();
    return 0;
}