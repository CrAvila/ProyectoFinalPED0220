//funcion de abordaje
#pragma once
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//informacion de cada pasajero 
struct Cliente{
    string nombre;
    int edad;
    char discapsitado;
    string destino;

};
typedef struct Cliente cliente;

//Enumerar los destinos posibles 
enum destino{EEUU, Canada, Colombia};

//Una cola de de pasajeros corrientes y una de pasajeros prioritarios 
queue <cliente> normal;
queue <cliente> prioritario;

void Menu_abordaje (vector <cliente>,vector <cliente>);
void Elegir_destino(vector <cliente>, vector <cliente>);
void Abordar_pasajeros();
void Abordaje_destino(destino, vector <cliente>, vector <cliente>);

void Menu_abordaje(vector <cliente> pasajeros, vector <cliente> pasajerosDiscapacitados){
    bool s=true;
    int opcion;
    //Menu de opciones principales
    do{
        cout<<endl<<"********** MENU DE OPCIONES **********"<<endl;
        cout<<"1.Elegir destino\n"<<"2.Abordar a los pasajeros\n"<<"3.salir\n";
        cout<<endl<<"Ingrese su opcion:"<<endl;
        cin>>opcion;cin.ignore();
        switch (opcion){
            case 1: Elegir_destino(pasajeros, pasajerosDiscapacitados); break;
            case 2: Abordar_pasajeros(); break;
            case 3: s = false; break;
            default: cout<<"\nLa opcion ingresada no es valida\n";
        }       
    } while (s);
}
//Funciones ejecutadas directamente por el menu 
void Elegir_destino(vector <cliente> pasajeros , vector <cliente> pasajerosDiscapacitados){
    destino vuelo;
    bool s=true;
    int pais;
    do{ //desplegamos otro menu para que el usuario escoja el destino del vuelo
        cout<<endl<<"++++++++++ CODIGOS DE PAISES +++++++++"<<endl;
        cout<<"1.EEUU\n"<<"2.Canada\n"<<"3.Colombia\n"<<"4.Salir\n";
        cout<<endl<<"Ingrese el destino del vuelo:"<<endl;
        cin>>pais;cin.ignore();
        
        switch (pais){
            case 1: vuelo = EEUU; break;
            case 2: vuelo = Canada; break;
            case 3: vuelo = Colombia; break;
            case 4: s = false; break;
            default:
                cout<<"Opcion no valida. Intente nuevamente.";
            break;
        }
        Abordaje_destino(vuelo, pasajeros, pasajerosDiscapacitados);
        s = false;
    } while (s);
}

void Abordar_pasajeros(){
    if (normal.empty() && prioritario.empty()){ //nos aseguramos que las colas no esten vacias 
    cout<<"\nNo hay pasajeros para este destino\n\n";
    }
    //Mostramos la cola de pasajeros prioritarios
    else if (!prioritario.empty() && !normal.empty()){
        cout<<"========== Pasajeros prioritarios =========="<<endl<<endl;
        while (!prioritario.empty()){
            cliente siguiente_abordar = prioritario.front();
            //mostramos sus datos en consola
            cout<<"Nombre: "<<siguiente_abordar.nombre<<endl;
            cout<<"Edad: "<<siguiente_abordar.edad<<endl;
            cout<<"Destino: "<<siguiente_abordar.destino<<endl<<endl;
            //Procedemos a abordarlos despejando la cola
            prioritario.pop();
        }
    //Repetimos el proceso anterios pero ahora con la cola de no prioritarios
        cout<<"========== Pasajeros corrientes =========="<<endl<<endl;
        while (!normal.empty()){
            cliente siguiente_abordar = normal.front();
            
            cout<<"Nombre: "<<siguiente_abordar.nombre<<endl;
            cout<<"Edad: "<<siguiente_abordar.edad<<endl;
            cout<<"Destino: "<<siguiente_abordar.destino<<endl<<endl;
            
            normal.pop();
        }
    }
}
//Funcion secundaria
void Abordaje_destino(destino v, vector <cliente> pasajeros , vector <cliente> pasajerosDiscapacitados){
    string d;
    switch (v){
        case EEUU: d = "EEUU"; break;
        case Canada: d = "Canada"; break;
        case Colombia: d = "Colombia"; break;
    }
    if (!prioritario.empty() && !normal.empty()){ //Condicion para que no se pueda tener dos destinos en una misma cola
        cout<<"\nLa cola de abordaje esta llena.\nIngresa a los pasajeros a su vuelo antes de elegir un nuevo destino\n\n";
    }
    else if (pasajeros.empty() && pasajerosDiscapacitados.empty()){ //nos aseguramos que hayan registros de clientes
        cout<<"\nNo hay registros de clientes\n\n";
    }
    else{ //Si hay clientes en el registro procedemos a pasarlos a la cola de abordaje
        if (!pasajeros.empty()){ //evaluamos primero los pasajeros no prioritarios
            for (vector<cliente>::iterator i = pasajeros.begin(); i != pasajeros.end(); ) //creamos un iterador para recorrer la lista 
            {                                                                           
                if (i->destino == d){ //este se detendra al encontrar un elemento con la condicion establecida
                    normal.push(*i); //añadira el elemento a nuestra cola
                    i =  pasajeros.erase(i); //se elimina el nodo               
                }
                else
                    i++;
            }
        } //se repite el proceso anterior con la lista de discapacitados para pasarlos a la cola prioritaria
        if (!pasajerosDiscapacitados.empty()){
            for (vector<cliente>::iterator i = pasajerosDiscapacitados.begin(); i != pasajerosDiscapacitados.end(); )
            {
                if (i->destino == d){
                    prioritario.push(*i);
                    i =  pasajerosDiscapacitados.erase(i);               
                }
                else
                    i++;
            }
        }
        //mostramos un mensaje si todo es correcto
        cout<<"\nEl destino "<<d<<" ha sido elegido satisfactoriamente\n\n";
    }
}
