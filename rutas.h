//Rutas para vuelos

#pragma once

#include <iostream>
#include <list>

using namespace std;

struct Nodo
{
    int inicio;
    int fin;
    int peso;
};

struct Data
{
    int fin;
    int peso;
};

int couter = 0;
int V = 0; //Numero de vertices
list<Data>* adj; //Puntero al arreglo de la lista de adyacencia

//Prototipo de funciones
void agregarBorde(Nodo n[], int v);
void imprimirTodosLosCaminos(int s, int d);
void buscarCaminos(int, int, bool[], int[], int&); 
void comenzarBusqueda(int s, int d);

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