#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "rutas.hpp"

/*#include "rutas.hpp"
#include "maletas.hpp"
#include "abordaje.hpp"*/

using namespace std;

//Andrea subio su codigo yay!

struct cliente
{
    string nombre;
    int edad;
    char discapacidad;
    int destino;
};

bool compNombres(string a, string b) {return a < b;};

void clientes();
void ganancias();
int despliegueDestinos();
void verNums(int);

vector <cliente> listaPasajeros;
vector<cliente> pasajerosDiscapacitados;

string continentes[5] = {
    "América", "África", "Asia", "Europa", "Oceanía" 
};

int main()
{

    bool stop=true;
    int opt;
    cout<<"Bienvenido"<<endl;

    do
    {
        cout<<"===================== M E N U ====================="; cout<<endl;
        cout<<"               1. Ingresar clientes."<<endl;
        cout<<"               2. Mostrar Ganancias."<<endl;
        cout<<"               3. Iniciar abordaje."<<endl;
        cout<<"               4. Salir. "<<endl;
        cout<<"Opcion: ";
        cin>>opt;
        verNums(opt);
        cout<<"===================================================="<<endl;

        switch (opt)
        {
            case 1:
                clientes();
            break;
            case 2:
                ganancias();
            break;
            case 3:
                //samuel's code.
            break;
            case 4:
                stop=false;
            break;

            default:
                cout<<"Opcion no valida. Intente de nuevo."<<endl;
            break;
        }
        
    } while (stop);
    return 0;

    
}

void clientes()
{

    cliente unPasajero; //declaracion de objeto para acceder a la estructura.

    
    //inicio de recoleccion de datos.
    int num=0;
    int cont=0;

    cout<<"Bienvenido. "<<endl;
    cout<<"Numero de pasajero a ingresar: ";
    cin>>num;
    cin.ignore();

    while (cont<num)
    {
        cout<<"Ingrese el nombre del pasajero "<<cont+1<<": "<<endl;
        getline(cin, unPasajero.nombre);
        cout<<"Ingrese la edad del pasajero "<<cont+1<<": "<<endl;
        cin>>unPasajero.edad;
        cout<<"Tiene alguna discapacidad? ";
        bool opt2=true;
        
        while(opt2) //validacion de dato
        {
            cout<<"(s/n): ";
            cin>>unPasajero.discapacidad;

            if (unPasajero.discapacidad!='n' && unPasajero.discapacidad!='s')
            {
                cout<<"Opcion invalida. Intentelo de nuevo"<<endl;
            }
            else 
            {
                opt2=false;
            } 
            
        }

        cout<< endl << "Continentes disponibles: "<<endl << endl;
        despliegueDestinos();
        bool opt3=true;
        while(opt3) //validacion de dato
        {
            cout<<"Elija su opcion: ";
            cin>>unPasajero.destino;
            if (unPasajero.destino>8)
            {
                cout<<"Opcion no valida. Intentelo de nuevo. "<<endl;
                opt3=true;
            }else opt3=false;   
        }
        
        cout<<"Redirigiendo al sistema de registro de maletas..."<<endl;
        //ernesto's code.
        cin.ignore();
        
        if (unPasajero.discapacidad=='s' || unPasajero.edad>65) //validacion de lista de pertenencia
        {
            pasajerosDiscapacitados.push_back(unPasajero); //cola pasajeros discapacitados y adultos mayores
        } else listaPasajeros.push_back(unPasajero); //cola pasajeros 
        cont++;

    }
}

int despliegueDestinos(){
    int opt = 0;
    for(int i = 0; i < 5; i++){
        cout << i+1 << "] " << continentes[i] << endl;
    }
    
    cout << endl << "Ingrese el numero del continente al que desea visitar: ";
    cin >> opt;
    string continente = continentes[opt-1];
    cout << endl << "Países disponibles en " << continente << ": " << endl << endl;

    vector<string> paises;

    for(int i = 1; i < 60; i++){
        if(ciudades[i].continente == continente){
            paises.push_back(ciudades[i].pais);
        }
    }
    sort(paises.begin(), paises.end(), compNombres);
    paises.erase(unique(paises.begin(), paises.end()), paises.end());

    int counter = 0;
    for(vector<string>::iterator it=paises.begin(); it!=paises.end(); it++){
        counter++;
        cout << counter << "] " << *it << endl;
    }
    cout << endl;
    int optPais = 0;
        cout << "Ingrese el numero del país al que desea visitar: ";
        cin >> optPais;
    cout << endl;

    string pais;

    counter = 0;

    for(vector<string>::iterator it=paises.begin(); it!=paises.end(); it++){
        counter++;
        if(counter == optPais) pais = *it;
    }
    
    counter = 0;
    vector<string> ciudadesDisponibles;
    for(int i = 1; i < 60; i++){
        if(ciudades[i].pais == pais){
            ciudadesDisponibles.push_back(ciudades[i].ciudad);
        }
    }

    sort(ciudadesDisponibles.begin(), ciudadesDisponibles.end(), compNombres);
    ciudadesDisponibles.erase(unique(ciudadesDisponibles.begin(), ciudadesDisponibles.end()), ciudadesDisponibles.end());

    counter = 0;
    for(vector<string>::iterator it=ciudadesDisponibles.begin(); it!=ciudadesDisponibles.end(); it++){
        counter++;
        cout << counter << "] " << *it << endl;
    }
    
    cout << endl;
    cout << "Ciudades disponibles en " << pais << ": " << endl;
    int optFinal = 0;
        cout << "Ingrese el numero de la ciudad que desea visitar: ";
        cin >> optFinal;


    string ciudad;
    counter = 0;
    for(vector<string>::iterator it=ciudadesDisponibles.begin(); it!=ciudadesDisponibles.end(); it++){
        if(counter == optFinal) ciudad = *it;
    }

    int numDestino = 0;

    for(int i = 1; i < 60; i++){
        if(ciudades[i].ciudad == ciudad) numDestino = i;
    }

    return numDestino;
}

void ganancias(){
    cout<<"ganancias."<<endl;
}

void verNums(int opt)
{
    if (cin.fail())
    {
        cout<<"Por favor, ingrese solo numeros. "<<endl;
        cin.clear();
        cin.ignore();
    } 
}