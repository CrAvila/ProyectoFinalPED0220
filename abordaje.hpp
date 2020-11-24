//funcion de abordaje
#pragma once
#include <iostream>
#include <vector>
#include "rutas.hpp"
#include "validaciones.hpp"

using namespace std;

/*informacion de cada pasajero*/
struct cliente{
    string nombre;
    int edad;
    char discapacidad;
    ruta rutaVuelo;
    float costoTotal;
};


//Codigo Gil *aprovado*
 struct puerta{
    string destino;
};

vector <puerta> puertas;

void Crear_puerta(vector <cliente>, vector <cliente>);
void Abordar_pasajeros(puerta, vector <cliente>, vector <cliente>);

//Funciones ejecutadas directamente por el menu 
void Crear_puerta(vector <cliente> pasajeros , vector <cliente> pasajerosDiscapacitados){
    if (pasajeros.empty() && pasajerosDiscapacitados.empty()){
        cout<<"\nNo hay ningun clientes para abordar\n\n";
    }
    else{
        cliente uncl;//un cliente
        int n = 1, o = 0;//contador y opcion 
        //variable donde se guardara el nombre del destino
        puerta unapuerta;

        unapuerta.destino = ciudades[pasajeros.front().rutaVuelo.pares.front().destino].ciudad; //asignando el destino del primer nodo
        
        cout<<endl<<"++++++++++ PUERTAS DE ABORDAJE +++++++++"<<endl;
        //Se imprime la primera puerta
        cout<<"Puerta "<<n++<<" con destino a "<<unapuerta.destino<<endl;
        puertas.push_back(unapuerta);
        /*recorremos la lista comparando los destinos para sacar solo los destinos existentes
        si estos destinos son diferentes al anterior se imprime como una puerta nueva*/
        for (auto i = 0; i < pasajeros.size(); i++) {
            uncl = pasajeros[i];
            if (!(unapuerta.destino == ciudades[uncl.rutaVuelo.pares.front().destino].ciudad)){
            unapuerta.destino = ciudades[uncl.rutaVuelo.pares.front().destino].ciudad;
            cout<<"Puerta "<<n++<<" con destino a "<<unapuerta.destino<<endl;
            puertas.push_back(unapuerta);
            }
        }
        bool c = true;
        do
        {
        //debe ingresar uno de los destinos previamente mostrados
        cout<<endl<<"Ingrese el Numero de la puerta del vuelo que desea abordar:"<<endl;
        cin>>o;cin.ignore();
        if ( o < 0 || o > n-1 ){
                cout << endl;
                cout << "Por favor intentalo otra vez." << endl;
                cout << endl;
            } 
        else {
                c = false;
            }
        }
        while (c);
        Abordar_pasajeros(puertas[o-1], pasajeros, pasajerosDiscapacitados);//pasa el destino y las listas a la funcion 
    }
}

void Abordar_pasajeros(puerta unap, vector <cliente> pasajeros , vector <cliente> pasajerosDiscapacitados){
    cliente uncl;
    if (pasajeros.empty() && pasajerosDiscapacitados.empty()){ //nos aseguramos que hayan registros de clientes
        cout<<"\nNo hay registros de clientes\n\n";
    }
    else{ //Si hay clientes en el registro procedemos a pasarlos a la cola de abordaje
        if (!pasajeros.empty()){ //evaluamos primero los pasajeros no prioritarios
        cout<<"========== Pasajeros corrientes =========="<<endl<<endl;
            for (auto i = 0; i < pasajeros.size(); i++) //creamos un iterador para recorrer la lista 
            {    
                uncl = pasajeros[i];                                                                     
                if (ciudades[uncl.rutaVuelo.pares.front().destino].ciudad == unap.destino){ //este se detendra al encontrar un elemento con la condicion establecida
                    cout<<"Nombre: "<<uncl.nombre<<endl;
                    cout<<"Edad: "<<uncl.edad<<endl;
                    cout<<"Destino: "<<ciudades[uncl.rutaVuelo.pares.front().destino].ciudad<<endl<<endl;
                   // i = pasajeros.remove(i); //se elimina el nodo               
                }
            }
        } //se repite el proceso anterior con la lista de discapacitados para pasarlos a la cola prioritaria
        if (!pasajerosDiscapacitados.empty()){
            cout<<"========== Pasajeros prioritarios =========="<<endl<<endl;
            for (auto i = 0; i < pasajerosDiscapacitados.size(); i++) 
            {
                uncl = pasajerosDiscapacitados[i];
                if (ciudades[uncl.rutaVuelo.pares.front().destino].ciudad == unap.destino){
                    cout<<"Nombre: "<<uncl.nombre<<endl;
                    cout<<"Edad: "<<uncl.edad<<endl;
                    cout<<"Destino: "<<ciudades[uncl.rutaVuelo.pares.front().destino].ciudad<<endl<<endl;
                    //i =  pasajerosDiscapacitados.erase(i);               
                }
            }
        //mostramos un mensaje si todo es correcto
        cout<<"\nEl destino "<<unap.destino<<" ha sido elegido satisfactoriamente\n\n";
        }
    }
}