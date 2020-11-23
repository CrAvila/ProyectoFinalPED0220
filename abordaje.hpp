//funcion de abordaje
#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include "rutas.hpp"

using namespace std;

/*informacion de cada pasajero*/
struct cliente{
    string nombre;
    int edad;
    char discapacidad;
    ruta rutaVuelo;
};
//nuevo struc para las colas de las puertas, que contienen solo los datos de interes para el abordaje
struct pasajero{
    string nombre;
    int edad;
    string destino;
};

struct Puertas
{
    string destino;
    queue<pasajero> normal;
    queue<pasajero> prioritario;
};

vector<Puertas> puerta;

//Una cola de pasajeros corrientes y una de pasajeros prioritarios 
// queue <pasajero> normal;
// queue <pasajero> prioritario;

/*
void Menu_abordaje (vector <cliente>,vector <cliente>);
void Elegir_destino(vector <cliente>, vector <cliente>);
void Abordar_pasajeros();
void Abordaje_destino(string, vector <cliente>, vector <cliente>);
*/

void crearPuertas(set<string> destinos, vector <cliente> pasajeros,vector <cliente> pasajerosDiscapacitados);
void agregarPasajeros(vector <cliente> pasajeross,vector <cliente> pasajerosDiscapacitados);

void crearPuertas(set<string> destinos, vector <cliente> pasajeros,vector <cliente> pasajerosDiscapacitados)
{
    Puertas aux;

    for (auto it = destinos.begin(); it != destinos.end(); ++it)
    {
        aux.destino = *it;
        puerta.push_back(aux);
    }

    agregarPasajeros(pasajeros, pasajerosDiscapacitados);
}

void agregarPasajeros(vector <cliente> pasajeros,vector <cliente> pasajerosDiscapacitados)
{
    
}

// void Menu_abordaje(vector <cliente> pasajeros, vector <cliente> pasajerosDiscapacitados){
//     bool s=true;
//     int opcion;
//     //Menu de opciones principales
//     do{
//         cout<<endl<<"********** MENU DE OPCIONES **********"<<endl;
//         cout<<"1.Elegir destino\n"<<"2.Abordar a los pasajeros\n"<<"3.salir\n";
//         cout<<endl<<"Ingrese su opcion:"<<endl;
//         cin>>opcion;cin.ignore();
//         switch (opcion){
//             case 1: Elegir_destino(pasajeros, pasajerosDiscapacitados); break;
//             case 2: Abordar_pasajeros(); break;
//             case 3: s = false; break;
//             default: cout<<"\nLa opcion ingresada no es valida\n";
//         }       
//     } while (s);
// }
// //Funciones ejecutadas directamente por el menu 
// void Elegir_destino(vector <cliente> pasajeros , vector <cliente> pasajerosDiscapacitados){
//     cliente uncl;//un cliente
//     int n = 1;//contador
//     string ds;//variable donde se guardara el nombre del destino
    
//     ds = ciudades[pasajeros.front().rutaVuelo.pares.front().destino].ciudad; //asignando el destino del primer nodo
    
//     cout<<endl<<"++++++++++ CODIGOS DE PAISES +++++++++"<<endl;
//     //Se imprime la primera puerta
//     //cout<<"Puerta "<<n<<" con destino a "<<ds<<endl;
    
//     /*recorremos la lista comparando los destinos para sacar solo los destinos existentes
//     si estos destinos son diferentes al anterior se imprime como una puerta nueva*/
//     for (auto i = 0; i < pasajeros.size(); i++) {
//         uncl = pasajeros[i];
//         ds = ciudades[uncl.rutaVuelo.pares.front().destino].ciudad;
//         cout<<"Puerta "<<n++<<" con destino a "<<ds<<endl;
//     }

//     //debe ingresar uno de los destinos previamente mostrados
//     cout<<endl<<"Ingrese el destino del vuelo:"<<endl;
//     getline(cin,ds);
//     Abordaje_destino(ds, pasajeros, pasajerosDiscapacitados);//pasa el destino y las listas a la funcion 
// }


// void Abordar_pasajeros(){
//     if (normal.empty() && prioritario.empty()){ //nos aseguramos que las colas no esten vacias 
//     cout<<"\nNo hay pasajeros para este destino\n\n";
//     }
//     //Mostramos la cola de pasajeros prioritarios
//     else if (!prioritario.empty() && !normal.empty()){
//         cout<<"========== Pasajeros prioritarios =========="<<endl<<endl;
//         while (!prioritario.empty()){
//             pasajero siguiente_abordar = prioritario.front();
//             //mostramos sus datos en consola
//             cout<<"Nombre: "<<siguiente_abordar.nombre<<endl;
//             cout<<"Edad: "<<siguiente_abordar.edad<<endl;
//             cout<<"Destino: "<<siguiente_abordar.destino<<endl<<endl;
//             //Procedemos a abordarlos despejando la cola
//             prioritario.pop();
//         }
//     //Repetimos el proceso anterios pero ahora con la cola de no prioritarios
//         cout<<"========== Pasajeros corrientes =========="<<endl<<endl;
//         while (!normal.empty()){
//             pasajero siguiente_abordar = normal.front();
            
//             cout<<"Nombre: "<<siguiente_abordar.nombre<<endl;
//             cout<<"Edad: "<<siguiente_abordar.edad<<endl;
//             cout<<"Destino: "<<siguiente_abordar.destino<<endl<<endl;
            
//             normal.pop();
//         }
//     }
// }
// //Funcion secundaria
// void Abordaje_destino(string ds, vector <cliente> pasajeros , vector <cliente> pasajerosDiscapacitados){
//     pasajero unp; // un pasajero

//     if (!prioritario.empty() && !normal.empty()){ //Condicion para que no se pueda tener dos destinos en una misma cola
//         cout<<"\nLa cola de abordaje esta llena.\nIngresa a los pasajeros a su vuelo antes de elegir un nuevo destino\n\n";
//     }
//     else if (pasajeros.empty() && pasajerosDiscapacitados.empty()){ //nos aseguramos que hayan registros de clientes
//         cout<<"\nNo hay registros de clientes\n\n";
//     }
//     else{ //Si hay clientes en el registro procedemos a pasarlos a la cola de abordaje
//         if (!pasajeros.empty()){ //evaluamos primero los pasajeros no prioritarios
//             for (vector<cliente>::iterator i = pasajeros.begin(); i != pasajeros.end(); ) //creamos un iterador para recorrer la lista 
//             {                                                                           
//                 if (ciudades[i->rutaVuelo.pares.front().destino].ciudad == ds){ //este se detendra al encontrar un elemento con la condicion establecida
//                     unp.nombre = i->nombre;     //llenamos los datos de "un pasajero"...
//                     unp.edad = i->edad;         //...solo con la informacion que nos interesa 
//                     unp.destino = ds;
//                     normal.push(unp); //añadira el elemento a nuestra cola
//                     i =  pasajeros.erase(i); //se elimina el nodo               
//                 }
//                 else
//                     i++;
//             }
//         } //se repite el proceso anterior con la lista de discapacitados para pasarlos a la cola prioritaria
//         if (!pasajerosDiscapacitados.empty()){
//             for (vector<cliente>::iterator i = pasajerosDiscapacitados.begin(); i != pasajerosDiscapacitados.end(); )
//             {
//                 if (ciudades[i->rutaVuelo.pares.front().destino].ciudad == ds){
//                     unp.nombre = i->nombre;
//                     unp.edad = i->edad;
//                     unp.destino = ds;
//                     prioritario.push(unp);
//                     i =  pasajerosDiscapacitados.erase(i);               
//                 }
//                 else
//                     i++;
//             }
//         }
//         //mostramos un mensaje si todo es correcto
//         cout<<"\nEl destino "<<ds<<" ha sido elegido satisfactoriamente\n\n";
//     }
// }
