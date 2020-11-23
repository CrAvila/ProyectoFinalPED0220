//Rutas para vuelos

#pragma once

#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <clocale>

using namespace std;

struct Nodo
{
    int inicio;
    int fin;
    int peso;
};


struct destino{
    string ciudad;
    string pais;
    string continente;
};

struct par{
    int origen;
    int destino;
    int peso;
};

struct ruta{
    queue<par> pares;
    float peso{};
};

queue<ruta> rutas;

struct Data
{
    int fin;
    int peso;
};

struct idaYVuelta{
    ruta ida;
    ruta vuelta;
};

idaYVuelta viajeCompleto;

destino ciudades[60] = {
        {"San Salvador",        "El Salvador",            "America"},
        {"Los Angeles",         "Estados Unidos",         "America"},
        {"Washington",          "Estados Unidos",         "America"},
        {"Dubai",               "Emiratos Arabes Unidos", "Asia"},
        {"Kabul",               "Afganistan",             "Asia"},
        {"Madrid",              "Espana",                 "Europa"},
        {"Frankfurt",           "Alemania",               "Europa"},
        {"Ciudad de Guatemala", "Guatemala",              "America"},
        {"Nueva York",          "Estados Unidos",         "America"},
        {"Saint John",          "Antigua y Barbuda",      "America"},
        {"Amsterdam",           "Paises Bajos",           "Europa"},
        {"Nador",               "Marruecos",              "Africa"},
        {"Argel",               "Argelia",                "Africa"},
        {"Doha",                "Catar",                  "Asia"},
        {"Paris",               "Francia",                "Europa"},
        {"Ciudad de Panama",    "Panama",                 "America"},
        {"Buenos Aires",        "Argentina",              "America"},
        {"Nadi",                "Fiyi",                   "Oceania"},
        {"Melbourne",           "Australia",              "Oceania"},
        {"Houston",             "Estados Unidos",         "America"},
        {"Florida",             "USA",                    "America"},
        {"George Town",         "Bahamas",                "America"},
        {"Puerto Espana",       "Trinidad y Tobago",      "America"},
        {"Bridgetown",          "Barbados",               "America"},
        {"Belmopan",            "Belice",                 "America"},
        {"Bogota",              "Colombia",               "America"},
        {"La Paz",              "Bolivia",                "America"},
        {"Belo Horizonte",      "Brasil",                 "America"},
        {"Toronto",             "Canada",                 "America"},
        {"Varsovia",            "Polonia",                "Europa"},
        {"Munich",              "Alemania",               "Europa"},
        {"San Jose",            "Costa Rica",             "America"},
        {"Copenhage",           "Dinamarca",              "Europa"},
        {"Guayaquil",           "Ecuador",                "Europa"},
        {"Londres",             "Inglaterra",             "Europa"},
        {"Atenas",              "Grecia",                 "Europa"},
        {"Tegucigalpa",         "Honduras",               "America"},
        {"Chicago",             "Estados Unidos",         "America"},
        {"Nueva Delhi",         "India",                  "Asia"},
        {"Reikavik",            "Islandia",               "Europa"},
        {"Roma",                "Italia",                 "Europa"},
        {"Ciudad de Mexico",    "Mexico",                 "America"},
        {"Tokio",               "Japon",                  "Asia"},
        {"Shangai",             "China",                  "Asia"},
        {"California",          "USA",                    "America"},
        {"Taipei",              "Taiwan",                 "Asia"},
        {"Managua",             "Nicaragua",              "America"},
        {"Montevideo",          "Uruguay",                "America"},
        {"Lima",                "Peru",                   "America"},
        {"Asunciòn",            "Paraguay",               "America"},
        {"Santiago",            "Chile",                  "America"},
        {"La Habana",           "Cuba",                   "America"},
        {"Atlanta",             "Estados Unidos",         "America"},
        {"Seul",                "Corea del Sur",          "Asia"},
        {"Seattle",             "Estados Unidos",         "America"},
        {"Tel Aviv",            "Israel",                 "Asia"},
        {"Mauricio",            "Mauricio",               "Africa"},
        {"Istambul",            "Turquia",                "Asia"},
        {"Lagos",               "Nigeria",                "Africa"},
        {"Zurich",              "Suiza",                  "Europa"},

};


Nodo node[114] = {
        {0, 1, 315},
        {0, 5, 620},
        {0, 7, 56},
        {0, 15, 125},
        {0, 19, 181},
        {0, 24, 90},
        {0, 25, 180},
        {0, 28, 290},
        {0, 31, 76},
        {0, 33, 180},
        {0, 36, 60},
        {0, 41, 135},
        {0, 46, 55},
        {0, 52, 214},
        {1, 3, 955},
        {1, 8, 307},
        {1, 17, 640},
        {1, 19, 195},
        {2, 0, 286},
        {2, 6, 460},
        {3, 2, 345},
        {3, 4, 160},
        {3, 38, 250},
        {4, 3, 23},
        {5, 6, 170},
        {5, 7, 695},
        {6, 5, 205},
        {6, 20, 660},
        {6, 32, 80},
        {6, 43, 640},
        {7, 0, 55},
        {8, 0, 295},
        {8, 2, 83},
        {8, 9, 241},
        {8, 10, 415},
        {8, 37, 152},
        {8, 39, 345},
        {8, 40, 495},
        {8, 59, 450},
        {9, 8, 274},
        {10, 11, 185},
        {11, 12, 115},
        {12, 13, 370},
        {13, 14, 430},
        {14, 8, 500},
        {14, 56, 670},
        {15, 0, 126},
        {15, 16, 431},
        {15, 22, 192},
        {15, 27, 414},
        {15, 47, 377},
        {15, 48, 219},
        {15, 50, 382},
        {15, 51, 155},
        {16, 15, 442},
        {17, 18, 355},
        {18, 1, 855},
        {19, 0, 184},
        {19, 8, 218},
        {19, 20, 150},
        {19, 57, 700},
        {20, 19, 155},
        {20, 21, 95},
        {21, 20, 95},
        {22, 15, 195},
        {22, 23, 55},
        {23, 22, 60},
        {24, 0, 85},
        {25, 0, 185},
        {25, 26, 225},
        {25, 49, 330},
        {26, 25, 230},
        {27, 15, 419},
        {28, 0, 300},
        {28, 6, 455},
        {28, 19, 223},
        {28, 30, 470},
        {28, 34, 420},
        {28, 55, 625},
        {29, 28, 550},
        {30, 29, 90},
        {31, 0, 78},
        {32, 28, 485},
        {33, 0, 180},
        {34, 19, 640},
        {34, 35, 215},
        {35, 34, 245},
        {36, 0, 55},
        {37, 3, 805},
        {38, 8, 935},
        {39, 8, 370},
        {40, 6, 130},
        {41, 0, 130},
        {41, 42, 880},
        {42, 41, 735},
        {42, 45, 250},
        {43, 44, 660},
        {44, 19, 230},
        {45, 42, 200},
        {46, 0, 55},
        {47, 15, 369},
        {48, 15, 227},
        {49, 25, 325},
        {50, 15, 395},
        {51, 15, 165},
        {52, 53, 865},
        {53, 54, 605},
        {54, 1, 154},
        {55, 28, 725},
        {56, 34, 730},
        {57, 8, 690},
        {57, 58, 430},
        {58, 57, 390},
        {59, 28, 530},

};



int counter = 0;
int V = 0; //Numero de vertices
list<Data>* adj; //Puntero al arreglo de la lista de adyacencia

//Prototipo de funciones
void agregarBorde(Nodo n[], int v);
void imprimirTodosLosCaminos(int s, int d);
void buscarCaminos(int, int, bool[], int[], int&, ruta*); 
ruta comenzarBusqueda(int s, int d);
ruta imprimirMejorRuta();
float costoTotalFinal = 0;

ruta comenzarBusqueda(int s, int d)
{
    costoTotalFinal = 0;
    ruta RutaFinal;
    V = 60;
    adj = new list<Data>[V];
    
    agregarBorde(node, 114); 

    cout << endl << endl << "La siguiente es la mejor ruta desde " << ciudades[s].ciudad << " a " << ciudades[d].ciudad << endl << endl;
     imprimirTodosLosCaminos(s, d);
     RutaFinal = imprimirMejorRuta();
     viajeCompleto.ida = RutaFinal;

    cout << "La siguiente es la mejor ruta de regreso desde " << ciudades[d].ciudad << " a " << ciudades[s].ciudad << endl << endl;
    imprimirTodosLosCaminos(d, s);

    viajeCompleto.vuelta = imprimirMejorRuta();
    costoTotalFinal = 2.73 * (viajeCompleto.ida.peso + viajeCompleto.vuelta.peso);
    return RutaFinal;
   }

//Conecta los diferentes vertices del grafo
void agregarBorde(Nodo n[], int v)
{
    Data data;
    for (int i = 0; i < v; i++)
    {
        data.fin = n[i].fin;
        data.peso = n[i].peso;
        adj[n[i].inicio].push_back(data);
    }
}

ruta imprimirMejorRuta(){
    ruta unaRuta;
    
    float menor = rutas.front().peso;
    queue<ruta> temp;

    while(!rutas.empty()){
        if(rutas.front().peso < menor){
            menor = rutas.front().peso;
        }
        temp.push(rutas.front());
        rutas.pop();
    }

    while(!temp.empty()){
        if(temp.front().peso == menor){
            unaRuta = temp.front();
            while(!temp.front().pares.empty()){
                cout  << "[$" << (temp.front().pares.front().peso) * 2.73 << "]  "
                      << ciudades[temp.front().pares.front().origen].ciudad << " (" << ciudades[temp.front().pares.front().origen].pais << ") -> "
                      << ciudades[temp.front().pares.front().destino].ciudad << " (" << ciudades[temp.front().pares.front().destino].pais << ") "
                      <<  endl;
                temp.front().pares.pop();
            }
            cout << endl << "Costo total del viaje: $" << (temp.front().peso)*2.73 << endl << endl;
        }
        temp.pop();
    }
    return unaRuta;
}

//Imprime todos los caminos de 's' a 'd'
void imprimirTodosLosCaminos(int s, int d)
{
    //Marcar todos los vertices como no visitados
    bool* visited = new bool[V];

    //Crear arreglo para guardar los caminos
    int* path = new int[V];

    //Inicializa path[] como vacio
    int path_index = 0;

    //Inicializa todos los vertices como no visitados
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }
    
    //Llama la funcion revursiva auxiliar para imprimir todos las rutas
    ruta unaRuta;
    buscarCaminos(s, d, visited, path, path_index, &unaRuta);
}

void buscarCaminos(int u, int d, bool visited[], int path[], int& path_index, ruta* r)
{
    //Marca el nodo actual y lo almacena en path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    //Si el actual vertice es el mismo que el destino, entonces imprime el path[] actual
    if (u == d)
    {
        for (int i = 0; i < path_index; i++)
        {
            if(i+1 < path_index){
                    int pesoTemp = 0;
                    for(auto & n : node){
                        if(n.inicio == path[i] && n.fin == path[i+1]){
                            pesoTemp = n.peso;
                            counter += pesoTemp;
                        }

                    }

                    //counter += matrix[path[i]][path[i+1]];
                    //cout << ciudades[path[i]]->ciudad <<  " -> "  << ciudades[path[i+1]]->ciudad << "  - $" << matrix[path[i]][path[i+1]];
                    par unPar;
                    unPar.origen = path[i];
                    unPar.destino = path[i+1];
                    unPar.peso = pesoTemp;
                    r->pares.push(unPar);
                }
            //cout << ciudades[path[i]]->ciudad << endl;
            //cout << endl;
            }


        //cout << " Peso Total del Viaje: " << counter << endl;
        r->peso = counter;
        counter = 0;
        //cout << endl;
        rutas.push(*r);
        while(!r->pares.empty()){
            r->pares.pop();
        }
    }
    else //Si el actual vertice no es el destino
    {
        list<Data>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            if (!visited[i->fin])
            {
                buscarCaminos(i->fin, d, visited, path, path_index, r);
            }
        }
    }

    //Remover el actual vertice de path[] y marcarlo como visitado
    path_index--;
    visited[u] = false;
}