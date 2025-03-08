#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int global_contadorOperaciones = 0;

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

// Función para omitir los espacios principio y al final de un string
string qEsp(const string &str) {
    int cInicio = 0;
    // Encuentra el primer carácter no blanco desde el principio
    while (cInicio < str.length() && (str[cInicio] == ' ' || str[cInicio] == '\t' || str[cInicio] == '\n' || str[cInicio] == '\r')) {
        cInicio++;
    }

    int cFinal = str.length() - 1;
    // Encuentra el primer carácter no blanco desde el final
    while (cFinal >= cInicio && (str[cFinal] == ' ' || str[cFinal] == '\t' || str[cFinal] == '\n' || str[cFinal] == '\r')) {
        cFinal--;
    }

    // Crea una nueva cadena con el contenido recortado
    string resultado = "";
    for (int i = cInicio; i <= cFinal; i++) {
        resultado += str[i];
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
                //cout << adn[i_adn][j_adn] << " ";
                j_adn++;

                if(i_adn<=n_adn && j_adn==n_adn){
                    i_adn++;
                    j_adn=0;
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

        /*
        ~Aventurero() {
            delete[] faccion;
            delete[] atributos;
            for (int i = 0; i < n_adn; ++i) {
                delete[] adn[i];
            }
            delete[] adn;
        }
        */
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
        int *atrVal_temp;
        int cantAtr = 0;
        int cantOp = 0;

    public:
        string *operaciones;
        string *simbolo;
        int *atrVal;
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

        void modificarAtrOp(int num) {
            atrVal_temp = new int[num];

            for (int i = 0; i < cantAtr; i++) {
                atrVal_temp[i] = atrVal[i];
            }

            if (cantAtr > 0) {
                delete[] atrVal;
            }

            atrVal = atrVal_temp;
            cantAtr++;
        }

        ~Operaciones() {
            delete[] operaciones;
            delete[] simbolo;
            if(cantAtr != 0) {
                delete[] atrVal;
            }
        }
};

class Funciones {
    private:
        void bubbleSort(Aventurero *av, int &n, const string atributoNombre, string &simbolo, int &contador) {
            contador = 0;
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

                    // Si uno de los aventureros no tiene el atributo, se manda al final
                    if (posA == -1 || posB == -1) {
                        if (posA == -1 && posB != -1) {
                            // Intercambiar los aventureros
                            Aventurero temp = av[j];
                            av[j] = av[j + 1];
                            av[j + 1] = temp;
                        }
                        continue;
                    }

                    if (simbolo == ">" && av[j].atributos[posA].cantidad > av[j + 1].atributos[posB].cantidad) {
                        // Intercambiar los aventureros
                        Aventurero temp = av[j];
                        av[j] = av[j + 1];
                        av[j + 1] = temp;
                    } else if (simbolo == "<" && av[j].atributos[posA].cantidad < av[j + 1].atributos[posB].cantidad) {
                        // Intercambiar los aventureros
                        Aventurero temp = av[j];
                        av[j] = av[j + 1];
                        av[j + 1] = temp;
                    }
                }
            }

            for(int i = 0; i < n; i++) {
                for(int j = 0; j < av[i].cantAtributos; j++) {
                    if(cStrMin(av[i].atributos[j].nombre) == atributoNombre) {
                        contador++;
                    }
                }   
            }
        }

        void seleccionarAventurero(Aventurero *av, int n, string &atbNombre, string simbolo, int valor, int &contador, bool &activacionAnterior) {
            int tempCount = 0;
            // i es aventurero
            // j es atributo
            if(activacionAnterior = true) {
                tempCount = contador;
            }

            for (int i = tempCount; i < n; i++) {
                for(int j = 0; j < av[i].cantAtributos; j++) {

                    if(cStrMin(av[i].atributos[j].nombre) == atbNombre) {
                        if (simbolo == ">" && av[i].atributos[j].cantidad < valor) {
                            Aventurero temp = av[i];
                            av[i] = av[tempCount];
                            av[tempCount] = temp;
                            tempCount++;
                            break;
                        } else if (simbolo == "<" && av[i].atributos[j].cantidad > valor) {
                            Aventurero temp = av[i];
                            av[i] = av[tempCount];
                            av[tempCount] = temp;
                            tempCount++;
                            break;
                        // Aca no se si es mayor o igual
                        } else if (simbolo == "EXISTE" && av[i].atributos[j].cantidad > 0) {
                            Aventurero temp = av[i];
                            av[i] = av[tempCount];
                            av[tempCount] = temp;
                            tempCount++;
                            break;
                        }
                    }
                }
            }

            contador = tempCount;
            activacionAnterior = true;
        }
    
        void buscarAventurero(Aventurero *av, int n, string &busqueda, string &simbolo, int &contador, bool &activacionAnterior) {
            int tempCount = 0;

            if(activacionAnterior = true) {
                tempCount = contador;
            }

            // n es cantidad de aventureros, simbolo es lo que se buscara.
            for (int i = 0; i < n; i++) {
                if(busqueda == "nombre") {
                    if (av[i].nombre == simbolo) {
                        Aventurero temp = av[i];
                        av[i] = av[tempCount];
                        av[tempCount] = temp;
                        tempCount++;
                    }
                } else if (busqueda == "clase") {
                    if (av[i].clase == simbolo) {
                        Aventurero temp = av[i];
                        av[i] = av[tempCount];
                        av[tempCount] = temp;
                        tempCount++;
                    }
                } else if (busqueda == "faccion") {
                    // Faccion, al ser un arreglo, debe ser recorrida
                    for (int j = 0; j < av[i].cantFacciones; j++) {
                        if (av[i].faccion[j] == simbolo) {
                            Aventurero temp = av[i];
                            av[i] = av[tempCount];
                            av[tempCount] = temp;
                            tempCount++;
                            break;
                        }
                    }
                }
            }

            contador = tempCount;
            activacionAnterior = true;
        }
    public:
        int contImprimir = 0; // Contador de archivos .out

        void Buscar(Aventurero *aventureros, int &cantAventureros) {
            string arg1;            // arg1 es el PARAMETRO
            string simbolo;         // simbolo en este caso es el nombre de lo que se quiere buscar
            bool iniciar = true;    // Bandera para finalizar el ciclo
            Operaciones op;         // Declaracion del objeto de operaciones

            int contador = 0;

            // Ciclo de ejecucion. Se detiene cuando se ingresa "INICIAR"
            while (iniciar == true) {
                cin >> arg1;

                if(arg1 == "INICIAR") {
                    iniciar = false;
                    break;
                }

                // Recibir el nombre de lo que se quiere bucar
                cin.ignore(); 
                getline(cin, simbolo, '\''); 
                getline(cin, simbolo, '\''); 

                arg1 = cStrMin(arg1);       // Convertir en minuscula lo que sea, por que ya conozco casos...
                simbolo = qEsp(simbolo);    // Quitar espacios adelante y atras, por si acaso.

                // Esto modifica y asigna el array de operaciones (dentro del objeto) (para almacenarlas)
                op.modificarArrayOperaciones(op.numOp); 
                
                // Almacenar el tipo de operacion (busqueda) y su parametro
                // Debe ser numOp - 1 SIEMPRE (esta iniciado en 1)
                op.operaciones[op.numOp-1] = arg1;
                op.simbolo[op.numOp-1] = simbolo;

                //cout << "operacion numero: " << op.numOp << endl;;

                op.numOp++; // Sumar 1 al numero de operaciones
            }
            
            //cout << "===========" << endl;

            bool activacionAnterior = false;

            // Ordenar los aventureros segun las operaciones
            for (int i = 0; i < op.numOp-1; i++) {
                buscarAventurero(aventureros, cantAventureros, op.operaciones[i], op.simbolo[i], contador, activacionAnterior);
            }

            cantAventureros = contador;
        }

        void Ordenar(Aventurero *aventureros, int &cantAventureros) {
            string arg1;             // arg1 es el atributo
            string simbolo = "<";   // simbolo es el simbolo de ordenamiento (default <)
            bool iniciar = true;    // Bandera para finalizar el ciclo
            Operaciones op;         // Declaracion del objeto de operaciones

            int contador = 0;

            // Ciclo de ejecucion. Se detiene cuando se ingresa "INICIAR"
            while (iniciar == true) {
                cin >> arg1;    // Atributo

                if(arg1 == "INICIAR") {
                    iniciar = false;
                    break;
                }
                
                if (cin.peek() != '\n') {
                    cin >> simbolo;             // Recibir el simbolo de ordenamiento
                } 

                arg1 = cStrMin(arg1);       // Convertir en minuscula lo que sea, por que ya conozco casos...

                // Esto modifica y asigna el array de operaciones (dentro del objeto) (para almacenarlas)
                op.modificarArrayOperaciones(op.numOp); 
                
                // Almacenar el tipo de operacion (atributo) y su simbolo
                // Debe ser numOp - 1 SIEMPRE (esta iniciado en 1)
                op.operaciones[op.numOp-1] = arg1;
                op.simbolo[op.numOp-1] = simbolo;

                //cout << "operacion numero: " << op.numOp << endl;;

                op.numOp++; // Sumar 1 al numero de operaciones
            }
            
            //cout << "===========" << endl;

            // Ordenar los aventureros segun las operaciones
            // Se usa un bubble sort
            for (int i = 0; i < op.numOp-1; i++) {
                //cout << op.operaciones[i] << " " << op.simbolo[i] << endl;
                bubbleSort(aventureros, cantAventureros, op.operaciones[i], simbolo, contador);
            }

            cantAventureros = contador;
        }

        void Seleccionar(Aventurero *av, int &cantAventureros) {
            string arg1;              // arg1 es el atributo, simbolo es el simbolo de ordenamiento (>, <)
            string simbolo = "EXISTE";
            int valor = 0;          // valor es el valor a comparar del atributo
            bool iniciar = true;    // Bandera para finalizar el ciclo
            int contador = 0;
            Operaciones op;         // Declaracion del objeto de operaciones

            // Ciclo de ejecucion. Se detiene cuando se ingresa "INICIAR"
            while (iniciar == true) {
                cin >> arg1;    // Atributo

                if(arg1 == "INICIAR") {
                    iniciar = false;
                    break;
                }

                if (cin.peek() != '\n') {
                    cin >> simbolo;             // Recibir el simbolo de ordenamiento
                    cin >> valor;               // Recibir Valor de ordenamiento
                } 

                arg1 = cStrMin(arg1);  

                op.modificarArrayOperaciones(op.numOp);
                op.modificarAtrOp(op.numOp);

                // Almacenar el tipo de operacion (atributo) y su simbolo
                // Debe ser numOp - 1 SIEMPRE (esta iniciado en 1)
                op.operaciones[op.numOp-1] = arg1;
                op.simbolo[op.numOp-1] = simbolo;
                op.atrVal[op.numOp-1] = valor;

                //cout << "operacion numero: " << op.numOp << endl;;

                simbolo = "EXISTE"; // Para evitar problemas. Volver al valor default.
                op.numOp++;         // Sumar 1 al numero de operaciones                
            }

            //cout << "===========" << endl;

            bool activacionAnterior = false;

            // Seleccionar los aventureros segun las operaciones
            for (int i = 0; i < op.numOp-1; i++) {
                seleccionarAventurero(av, cantAventureros, op.operaciones[i], op.simbolo[i], op.atrVal[i], contador, activacionAnterior);
            }

            cantAventureros = contador; 
        }

        void Imprimir(Aventurero *av, int &cantAventureros) {
            contImprimir++;
            char buffer[10]; 
            itoa(contImprimir, buffer, 10);
            string nombreArchivo = "operaciones/operacion" + string(buffer) + ".out";

            ofstream archivo(nombreArchivo);

            if(!archivo.is_open()) {
                system("mkdir operaciones"); 
                archivo.open(nombreArchivo);
            }

            archivo << "operaciones realizadas: " << global_contadorOperaciones << endl;
            archivo << "aventureros encontrados: " << cantAventureros << endl;
            if(cantAventureros != 0) {
                archivo << "lista de aventureros: " << endl;
            }
            
            for(int i = 0; i < cantAventureros; i++) {
                archivo << "#"<< i+1 << endl;                           // Numero del Aventurero
                archivo << "Puntaje: " << av[i].puntajeADN << endl;     // Puntaje del ADN/Aventurero
                archivo << "Clase: " << av[i].clase << endl;            // Clase del Aventurero
                archivo << "Faccion: ";                                 // Faccion del Aventurero
                for(int j = 0; j < av[i].cantFacciones; j++) {
                    archivo << av[i].faccion[j] << " ";
                    if (j < av[i].cantFacciones-1) {
                        archivo << "| ";
                    }
                }
                archivo << endl;
                archivo << "Nombre: " << av[i].nombre << endl;          // Nombre del Aventurero
                archivo << "Atributos";                                 // Atributos
                for (int j = 0; j < av[i].cantAtributos; j++) {
                    archivo << av[i].atributos[j].nombre << ": ";
                    archivo << av[i].atributos[j].cantidad << endl;
                }
            }
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
                            aventurero[iterador].clase = qEsp(linea);
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
                                aventurero[iterador].faccion[i] = qEsp(faccionesNombres[i]);
                            }
                            
                            delete[] faccionesNombres;
                            continue;
                        }
                        else if(linea=="Nombre"){
                            getline(archivo_manipulado,linea);
                            aventurero[iterador].nombre = qEsp(linea);
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

            // Calcular Puntaje
            aventurero[iterador].calcularPuntajeADN();

            /*
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
            }*/

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
                if (cin.eof()) break; // Previene un bucle infinito si se lee la entrada de un archivo.
                if(dato == "CARGAR") {
                    getline(cin, directorio, '"');
                    getline(cin, directorio, '"');
                    leerCarpeta(directorio);
                    crearArrayAventureros(cantArchivos);
                    modificarStringDirectorio();
                    asignarAventureros();
                    global_contadorOperaciones++;           // no se si se debe sumar en cargar, lol
                } else if (dato == "BUSCAR") {
                    //cout << "estoy en la funcion BUSCAR" << endl;
                    Buscar(aventurero, cantAventureros);
                    crearArrayAventureros(0);
                    global_contadorOperaciones++;
                } else if (dato == "ORDENAR") {
                    //cout << "estoy en la funcion ORDENAR" << endl;
                    Ordenar(aventurero, cantAventureros);
                    crearArrayAventureros(0);
                    global_contadorOperaciones++;
                } else if (dato == "SELECCIONAR") {
                    //cout << "estoy en la funcion SELECCIONAR" << endl;
                    Seleccionar(aventurero, cantAventureros);
                    crearArrayAventureros(0);
                    global_contadorOperaciones++;
                } else if (dato == "IMPRIMIR") {
                    //cout << "estoy en la funcion IMPRIMIR" << endl;
                    /*
                    for (int i = 0; i < cantAventureros; i++) {
                        cout << "Aventurero "<< i+1 << ":" << aventurero[i].nombre << endl;
                    }
                    */
                    Imprimir(aventurero, cantAventureros);
                } else if (dato == "SALIR") {
                    exit(0); // esto no va, salir no existe
                }
            }
        }
};

int main() {
    Inicializador programa;
    programa.iniciar();
    return 0;
}