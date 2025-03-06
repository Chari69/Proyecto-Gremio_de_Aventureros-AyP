#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int convertirCharAMinusc(int caracter) {
    if (caracter >= 'A' && caracter <= 'Z') {
        return caracter + 32;
    }
    return caracter;
}

string cStrMin(const string &str) {
    string resultado = str;
    for (size_t i = 0; i < str.length(); ++i) {
        resultado[i] = convertirCharAMinusc(str[i]);
    }
    return resultado;
}

struct Atributo {
    string nombre;
    int cantidad;
};

class Aventurero {
    private:
        int i_adn = 0, j_adn = 0;

    public:
        string clase;
        int cantFacciones;
        string *faccion;
        string nombre;
        
        int cantAtributos;
        int n_adn;
        Atributo *atributos;
        int **adn;

        int puntajeADN = 0;

        Aventurero() {
            this->clase = "";
            this->nombre = "";
            this->cantAtributos = 0;
            this->n_adn = 0;
            this->cantFacciones = 0;
        }

        void asignarFaccion(int cantFacciones) {
            this->cantFacciones = cantFacciones;
            faccion = new string[cantFacciones];
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

        void guardarADN (int valor) {
            if(i_adn<n_adn && j_adn<n_adn){
                adn[i_adn][j_adn] = valor;
                cout << adn[i_adn][j_adn] << " ";
                j_adn++;

                if(i_adn<=n_adn && j_adn==n_adn){
                    i_adn++;
                    j_adn=0;
                    cout << endl;
                }
            }
        }

        void guardarAtributo(int n, string nombre, int cantidad) {
            atributos[n].nombre = nombre;
            atributos[n].cantidad = cantidad;
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
            directorio = "dir /b \"" + directorio + "\" > database.temp";
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

            archivo.close();
            system("del database.temp");
        }

        void modificarStringDirectorio() {
            string directorio_temp;
            for (int i = 0; i < directorio.length(); i++) {
                if (directorio[i] == '"') {
                    continue;
                } else {
                    directorio_temp += directorio[i];
                }
            }
            if (directorio_temp[directorio_temp.length() - 1] != '/' ) {
                directorio_temp += '/';
            }
            directorio = directorio_temp;
        }

        void resetearDirectorio() {
            cantArchivos = 0;
            delete[] archivos;
        }
};

// Clase de operaciones
class Operaciones {
    private:
        string *op_temp;
        string *sim_temp;
        int cantOp = 0;

    public:
        string *operaciones;
        string *simbolo;
        int numOp = 1;

        void modificarArrayOperaciones(int num) {
            op_temp = new string[num];
            sim_temp = new string[num];

            for (int i = 0; i < cantOp; i++) {
                op_temp[i] = operaciones[i];
                sim_temp[i] = simbolo[i];
            }

            if (cantOp > 0) {
                delete[] operaciones;
                delete[] simbolo;
            }

            operaciones = op_temp;
            simbolo = sim_temp;

            cantOp++;
        }

        ~Operaciones() {
            delete[] operaciones;
            delete[] simbolo;
        }
};

class Funciones {
    private:
        // HAY QUE PULIR
        // SE NECESITA PODER ORDENAR PA LANTE O PA ATRAS SEGUN LO QUE INDIQUE EL USUARIO.
        void bubbleSort(Aventurero *av, int n, const string atributoNombre) {
            // Ordenar usando bubble sort
            for (int i = 0; i < n - 1; ++i) {
                for (int j = 0; j < n - i - 1; ++j) {
                    int posA = -1, posB = -1;
        
                    // Encontrar la posición del atributo en el aventurero j
                    for (int k = 0; k < av[j].cantAtributos; ++k) {
                        if (cStrMin(av[j].atributos[k].nombre) == atributoNombre) {
                            posA = k;
                            break;
                        }
                    }
        
                    // Encontrar la posición del atributo en el aventurero j + 1
                    for (int k = 0; k < av[j + 1].cantAtributos; ++k) {
                        if (cStrMin(av[j + 1].atributos[k].nombre) == atributoNombre) {
                            posB = k;
                            break;
                        }
                    }
        
                    if (posA == -1 || posB == -1) {
                        cout << "Atributo no encontrado en uno de los aventureros." << endl;
                        return;
                    }
        
                    if (av[j].atributos[posA].cantidad > av[j + 1].atributos[posB].cantidad) {
                        // Intercambiar los aventureros
                        Aventurero temp = av[j];
                        av[j] = av[j + 1];
                        av[j + 1] = temp;
                    }
                }
            }
        }

    public:
        void Buscar(Aventurero *aventureros, int &cantAventureros) {
            string parametro, busqueda;
            int contador;

            cin >> parametro;
            cin.ignore(); 
            getline(cin, busqueda, '\''); 
            getline(cin, busqueda, '\''); 

            if (parametro == "CLASE") {
                for (int i = 0; i < cantAventureros; i++) {
                    if (aventureros[i].clase == busqueda) {
                        cout << aventureros[i].nombre << endl;
                    }
                }
            } else if (parametro == "FACCION") {
                for (int i = 0; i < cantAventureros; i++) {
                    for (int j = 0; j < aventureros[i].cantFacciones; j++) {

                        if (aventureros[i].faccion[j] == busqueda) {
                            cout << aventureros[i].nombre << endl;
                        }

                    }
                }
            } else if (parametro == "NOMBRE") {
                for (int i = 0; i < (cantAventureros - 1); i++) {
                    if (aventureros[i].nombre == busqueda) {
                        cout << aventureros[i].nombre << endl;
                    }
                }
            }
        }

        void Ordenar(Aventurero *aventureros, int &cantAventureros) {
            string arg1, simbolo;   // arg1 es el atributo, simbolo es el simbolo de ordenamiento (>, <)
            bool iniciar = true;    // Bandera para finalizar el ciclo
            Operaciones op;         // Declaracion del objeto de operaciones

            // Ciclo de ejecucion. Se detiene cuando se ingresa "INICIAR"
            while (iniciar == true) {
                cin >> arg1;    // Atributo

                if(arg1 == "INICIAR") {
                    iniciar = false;
                    break;
                }
                
                cin >> simbolo;             // Recibir el simbolo de ordenamiento
                arg1 = cStrMin(arg1);       // Convertir en minuscula lo que sea, por que ya conozco casos...

                // Esto modifica y asigna el array de operaciones (dentro del objeto) (para almacenarlas)
                op.modificarArrayOperaciones(op.numOp); 
                
                // Almacenar el tipo de operacion (atributo) y su simbolo
                // Debe ser numOp - 1 SIEMPRE (esta iniciado en 1)
                op.operaciones[op.numOp-1] = arg1;
                op.simbolo[op.numOp-1] = simbolo;

                cout << "operacion numero: " << op.numOp << endl;;

                op.numOp++; // Sumar 1 al numero de operaciones
            }
            
            cout << "===========" << endl;

            // Ordenar los aventureros segun las operaciones
            // Se usa un bubble sort
            for (int i = 0; i < op.numOp-1; i++) {
                cout << op.operaciones[i] << " " << op.simbolo[i] << endl;
                bubbleSort(aventureros, cantAventureros, op.operaciones[i]);
            }


            /*
                Como tal, funciona, sin embargo!!!!
                Hay que tomar en cuenta que lo que no se encuentre, debe ser descartado

                Un dolor de bolas, basicamente...
            */
            cout << "LISTO" << endl;
        }
};

class Inicializador : Directorio, Funciones {
    
    private:
        void crearArrayAventureros(int num) {
            Aventurero* aventurero_array = new Aventurero[cantAventureros + num]();
            for (int i = 0; i < cantAventureros; i++) {
            aventurero_array[i] = aventurero[i];
            }
            delete[] aventurero;
            aventurero = aventurero_array;
        }

        // nombre del archivo, iteracion
        void asignarAventurero(string dir_archivo, int iterador) {
            string direccion = directorio + dir_archivo;

            int cantAtributos=0, ordenMatriz=0;
            int posAtributos=101, posADN=101;
        
            // acondicionamos el archivo para ser leido sin contar espacios ni simbolos
        
            ifstream archivo(direccion);
        
            if (archivo.is_open()) {
                ofstream archivo_manipulado;
                archivo_manipulado.open("archivo_manipulado.temp");
                
                string linea;
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
                    if(i>posADN){
                        ordenMatriz++;
                    }
        
                    for (int i = 0; i<linea.length() ; i++)
                    {
                        if(linea[i]==':'){
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
            aventurero[iterador].asignarADN(ordenMatriz);

            ifstream archivo_manipulado("archivo_manipulado.temp");

            if(archivo_manipulado.is_open()){ 
                string linea;
                for (int i = 0; archivo_manipulado>>linea; i++) {
                    if(i<posADN){
                        if(linea=="Clase"){
                            getline(archivo_manipulado,linea);
                            aventurero[iterador].clase = linea;
                            continue;
                        }
                        else if(linea=="Faccion"){
                            getline(archivo_manipulado,linea);
                            int cantfacciones=1;
                            
                            for (int i = 0; i < linea.length(); i++)
                            {
                                if(linea[i] == '|'){
                                    cantfacciones++;
                                }
                            }

                            string *faccionesNombres = new string[cantfacciones];
                            int contador_culo = 0;
                            int j = 0;
                            for (int i = 0; i < cantfacciones; i++)
                            {
                                while (j < linea.length()) {
                                    if(linea[j] == '|'){
                                        j++;
                                        break;
                                    }
                                    else{
                                        faccionesNombres[i]= faccionesNombres[i] + linea[j];
                                        j++;
                                    }
                                }
                            }

                            aventurero[iterador].asignarFaccion(cantfacciones);
                            
                            for (int i = 0; i < cantfacciones; i++) {
                                aventurero[iterador].faccion[i] = faccionesNombres[i];
                            }
                            
                            delete[] faccionesNombres;
                            continue;
                        }
                        else if(linea=="Nombre"){
                            getline(archivo_manipulado,linea);
                            aventurero[iterador].nombre = linea;
                            continue;
                        }
                        else if(linea=="ATRIB"){
                            posAtributos++;
                        }
                        if(i>=posAtributos && i<(posADN)){
                            aventurero[iterador].atributos[i-posAtributos].nombre = linea;
                            getline(archivo_manipulado,linea);
                            aventurero[iterador].atributos[i-posAtributos].cantidad = stoi(linea);
                            continue;
                        }
                    }
                    else if(i>posADN){
                        aventurero[iterador].guardarADN(stoi(linea));
                    }
                }
                archivo_manipulado.close();
            }

            cout << "Clase: " << aventurero[iterador].clase << endl;
            for(int i = 0; i < aventurero[iterador].cantFacciones; i++) {
                cout << "Faccion: " << aventurero[iterador].faccion[i] << " ";
            }
            cout << "Nombre: " << aventurero[iterador].nombre << endl;
            cout << "Atributos: " << endl;
            for (int i = 0; i < cantAtributos; i++) 
                cout << aventurero[iterador].atributos[i].nombre << ": " << aventurero[iterador].atributos[i].cantidad << endl;
        
            for (int i = 0; i < ordenMatriz; i++) {
                for (int j = 0; j < ordenMatriz; j++) {
                    cout << aventurero[iterador].adn[i][j] << " ";
                }
                cout << endl;
            }

            system("del archivo_manipulado.temp");
        }
    
        void asignarAventureros() {
            for (int i = 0; i < cantArchivos; i++, cantAventureros++) {
                // if( < cantAventureros)
                asignarAventurero(archivos[i], cantAventureros);
            }
            resetearDirectorio();
        }

    public:
        Aventurero *aventurero;
        int cantAventureros = 0;

        void iniciar() {
            string dato;
        
            while(true) {
                cin >> dato;
                if(dato == "CARGAR") {
                    getline(cin, directorio, '"');
                    getline(cin, directorio, '"');
                    leerCarpeta(directorio);
                    crearArrayAventureros(cantArchivos);
                    modificarStringDirectorio();
                    asignarAventureros();
                } else if (dato == "BUSCAR") {
                    cout << "estoy en la funcion BUSCAR" << endl;
                    Buscar(aventurero, cantAventureros);
                } else if (dato == "ORDENAR") {
                    cout << "estoy en la funcion ORDENAR" << endl;
                    Ordenar(aventurero, cantAventureros);
                } else if (dato == "SELECCIONAR") {
                    cout << "estoy en la funcion SELECCIONAR" << endl;
                } else if (dato == "IMPRIMIR") {
                    cout << "estoy en la funcion IMPRIMIR" << endl;

                    for (int i = 0; i < cantAventureros; i++) {
                        cout << "Aventurero "<< i+1 << ":" << aventurero[i].nombre << endl;
                    }
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