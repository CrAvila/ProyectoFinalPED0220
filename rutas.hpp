//Rutas para vuelos

#pragma once

#include <iostream>
#include <list>
#include <queue>

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

destino ciudades[60][3]{
        {"San Salvador", "El Salvador", "América"},
        {"Los Angeles", "Estados Unidos", "América"},
        {"Washington", "Estados Unidos", "América"},
        {"Dubai", "Emiratos Árabes Unidos", "Asia"},
        {"Kabul", "Afganistán", "Asia"},
        {"Madrid", "España", "Europa"},
        {"Frankfurt", "Alemania", "Europa"},
        {"Ciudad de Guatemala", "Guatemala", "América"},
        {"Nueva York", "Estados Unidos", "América"},
        {"Saint John", "Antigua y Barbuda", "América"},
        {"Amsterdam", "Países Bajos", "Europa"},
        {"Nador", "Marruecos", "África"},
        {"Argel", "Argelia", "África"},
        {"Doha", "Catar", "Asia"},
        {"Paris", "Francia", "Europa"},
        {"Ciudad de Panamá", "Panamá", "América"},
        {"Buenos Aires", "Argentina", "América"},
        {"Nadi", "Fiyi", "Oceanía"},
        {"Melbourne", "Australia", "Oceanía"},
        {"Houston", "Estados Unidos", "América"},
        {"Florida", "USA", "América"},
        {"George Town", "Bahamas", "América"},
        {"Puerto España", "Trinidad y Tobago", "América"},
        {"Bridgetown", "Barbados", "América"},
        {"Belmopán", "Belice", "América"},
        {"Bogotá", "Colombia", "América"},
        {"La Paz", "Bolivia", "América"},
        {"Belo Horizonte", "Brasil", "América"},
        {"Toronto", "Canada", "América"},
        {"Varsovia", "Polonia", "Europa"},
        {"Munich", "Alemania", "Europa"},
        {"San José", "Costa Rica", "América"},
        {"Copenhage", "Dinamarca", "Europa"},
        {"Guayaquil", "Ecuador", "Europa"},
        {"Londres", "Inglaterra", "Europa"},
        {"Atenas", "Grecia", "Europa"},
        {"Tegucigalpa", "Honduras", "América"},
        {"Chicago", "Estados Unidos", "América"},
        {"Nueva Delhi", "India", "Asia"},
        {"Reikavik", "Islandia", "Europa"},
        {"Roma", "Italia", "Europa"},
        {"Ciudad de Mexico", "Mexico", "América"},
        {"Tokio", "Japon", "Asia"},
        {"Shangai", "China", "Asia"},
        {"California", "USA", "América"},
        {"Taipei", "Taiwan", "Asia"},
        {"Managua", "Nicaragua", "América"},
        {"Montevideo", "Uruguay", "America"},
        {"Lima", "Perú", "América"},
        {"Asunciòn", "Paraguay", "América"},
        {"Santiago", "Chile", "América"},
        {"La Habana", "Cuba", "América"},
        {"Atlanta", "Estados Unidos", "América"},
        {"Seúl", "Corea del Sur", "Asia"},
        {"Seattle", "Estados Unidos", "América"},
        {"Tel Aviv", "Israel", "Asia"},
        {"Mauricio", "Mauricio", "Africa"},
        {"Istambul", "Turquia", "Asia"},
        {"Lagos", "Nigeria", "África"},
        {"Zúrich", "Suiza", "Europa"},

};

int couter = 0;
int V = 0; //Numero de vertices
list<Data>* adj; //Puntero al arreglo de la lista de adyacencia

//Prototipo de funciones
void agregarBorde(Nodo n[], int v);
void imprimirTodosLosCaminos(int s, int d);
void buscarCaminos(int, int, bool[], int[], int&); 
int comenzarBusqueda(int s, int d);

int comenzarBusqueda(int s, int d)
{
    V = 4;
    adj = new list<Data>[V];

    Nodo node[6] = {{0, 1, 4}, {0, 2, 1}, {0, 3, 2}, {2, 0, 5}, {2, 1, 6}, {1, 3, 1}}; 

    agregarBorde(node, 6); 

    cout << "Los siguientes son todos caminos diferentes de " << s << " a " << d << endl;

    imprimirTodosLosCaminos(s, d);

    return 0;
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
    buscarCaminos(s, d, visited, path, path_index);
}

void buscarCaminos(int u, int d, bool visited[], int path[], int& path_index)
{
    //Marca el nodo actual y lo almacena en path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    //Si el actual vertice es el mismo que el destino, entonces imprime el path[] actual
    if (u == d)
    {
        cout << endl;
        for (int i = 0; i < path_index; i++)
        {
            cout << path[i] << " ";
        }
        cout << endl;
    }
    else //Si el actual vertice no es el destino 
    {
        list<Data>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            if (!visited[i->fin])
            {
                buscarCaminos(i->fin, d, visited, path, path_index);
            }   
        }   
    }

    //Remover el actual vertice de path[] y marcarlo como visitado
    path_index--;
    visited[u] = false;
}