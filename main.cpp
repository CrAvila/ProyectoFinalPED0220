#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include "rutas.hpp"
#include "maletas.hpp"
#include "abordaje.hpp"
#include "validaciones.hpp"

using namespace std;

bool compNombres(string a, string b) {return a < b;};

void clientes();
void ganancias();
int despliegueDestinos();
void verNums(int);

vector <cliente> listaPasajeros;
vector<cliente> pasajerosDiscapacitados;
set<string> destinos;

string continentes[5] = {
    "América", "África", "Asia", "Europa", "Oceanía" 
};

ruta rutaCliente;

int main()
{

    bool stop=true;
    int opt = 0;
    cout<<"Bienvenido"<<endl;

    do
    {
        cout<<"===================== M E N U ====================="; cout<<endl;
        cout<<"               1. Ingresar clientes."<<endl;
        cout<<"               2. Mostrar Ganancias."<<endl;
        cout<<"               3. Iniciar abordaje."<<endl;
        cout<<"               4. Salir. "<<endl;
        cout<<"Opcion: ";
        opt = validarRango(to_string(opt), 1, 4);
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
                //crearPuertas(destinos, listaPasajeros, pasajerosDiscapacitados);
                Crear_puerta(listaPasajeros, pasajerosDiscapacitados);
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
    
    bool error = true;

    cout << endl;
    cout<<"Bienvenido."<<endl;
    cout << endl;

    cin.ignore();

    string auxString = " ";

    cout<<"-Ingrese el nombre del pasajero: ";       
    unPasajero.nombre = validarString();

    do
    {
        cout<<"-Ingrese la edad del pasajero: ";
        cin>>unPasajero.edad;

        if (cin.fail() || unPasajero.edad < 1)
        {
            cin.clear();
            cin.ignore();
            cout << endl;
            cout << "Por favor ingresa un numero entero positivo, intentalo otra vez." << endl;
            cout << "----------------------------------------------------------------" << endl;
            cout << endl;
        } 
        else 
        {
            error = false;
        }
            
    } while (error);

    cout<<"-Tiene alguna discapacidad? ";
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
        
    //Retorna la ruta con todos sus datos
    rutaCliente = comenzarBusqueda(0, despliegueDestinos());

    unPasajero.rutaVuelo=rutaCliente;
    unPasajero.costoTotal = costoTotalFinal;
    string destinoData = ciudades[unPasajero.rutaVuelo.pares.front().destino].ciudad;
    cout << endl << "Costo total por ida y vuelta: $" << unPasajero.costoTotal << endl << endl;
    destinos.insert(destinoData);

    //cout << "Primer destino: " << ciudades[rutaCliente.pares.front().destino].ciudad << endl;
        
    cout<<"Redirigiendo al sistema de registro de maletas..."<<endl<<endl;
    system("pause");
    MenuMaletas();
    cin.ignore();
        
    if (unPasajero.discapacidad=='s' || unPasajero.edad>65) //validacion de lista de pertenencia
    {
        pasajerosDiscapacitados.push_back(unPasajero); //cola pasajeros discapacitados y adultos mayores
    } 
    
    else 
    {
        listaPasajeros.push_back(unPasajero); //cola pasajeros
    } 
}

int despliegueDestinos(){
    //Se declaran variables temporales necesarias
    int opt = 0;
    vector<string> paises, ciudadesDisponibles;
    int counter = 0, optPais = 0, optFinal = 0, numDestino = 0;
    string pais, ciudad;

    //Se despliegan los continentes
    for(int i = 0; i < 5; i++) cout << i+1 << "] " << continentes[i] << endl;
    
    //Se solicita al usuario ingresar el numero de continente
    cout << endl << "Ingrese el numero del continente al que desea visitar: ";
    opt = validarRango(to_string(opt), 1, 5);
    string continente = continentes[opt-1];

    //Se despliegan los paises disponibles en dicho continente: 
    cout << endl << "Países disponibles en " << continente << ": " << endl << endl;

    //Se agregan los paises de dicho continente a la lista de países
    for(int i = 1; i < 60; i++){
        if(ciudades[i].continente == continente)paises.push_back(ciudades[i].pais);
    }

    //Se ordenan alfabeticamente y se eliminan duplicados
    sort(paises.begin(), paises.end(), compNombres);
    paises.erase(unique(paises.begin(), paises.end()), paises.end());

    //Se muestran en pantalla
    for(vector<string>::iterator it=paises.begin(); it!=paises.end(); it++){
        counter++;
        cout << counter << "] " << *it << endl;
    }

    //Se soclicita al usuario el numero del país que desea visitar
    cout << endl;
    cout << "Ingrese el numero del país al que desea visitar: ";
    optPais = validarRango(to_string(optPais), 1, paises.size());
    cout << endl;

    //Se guarda el nombre del país seleccionado
    counter = 0;
    for(vector<string>::iterator it=paises.begin(); it!=paises.end(); it++){
        counter++;
        if(counter == optPais) pais = *it;
    }
    
    //Se llena la lista de ciudades con las del país correspondiente
    counter = 0;
    for(int i = 1; i < 60; i++){
        if(ciudades[i].pais == pais) ciudadesDisponibles.push_back(ciudades[i].ciudad);
    }

    //Se ordenan alfabeticamente y se eliminan duplicados
    sort(ciudadesDisponibles.begin(), ciudadesDisponibles.end(), compNombres);
    ciudadesDisponibles.erase(unique(ciudadesDisponibles.begin(), ciudadesDisponibles.end()), ciudadesDisponibles.end());

    //Se muestran en pantalla
    counter = 0;
    for(vector<string>::iterator it=ciudadesDisponibles.begin(); it!=ciudadesDisponibles.end(); it++){
        counter++;
        cout << counter << "] " << *it << endl;
    }
    
    //Se solicita al usuario el numero de la ciudad que desea visitar
    cout << endl;
    cout << "Ciudades disponibles en " << pais << ": " << endl;
    cout << "Ingrese el numero de la ciudad que desea visitar: ";
    optFinal = validarRango(to_string(optFinal), 1, ciudadesDisponibles.size());

    //Se guarda el nombre de la ciudad
    counter = 0;
    for(vector<string>::iterator it=ciudadesDisponibles.begin(); it!=ciudadesDisponibles.end(); it++){
        counter++;
        if(counter == optFinal) ciudad = *it;
    }

    //Se busca en el arreglo de ciudades para obtener su correlativo correspondiente
    for(int i = 1; i < 60; i++){
        if(ciudades[i].ciudad == ciudad) numDestino = i;
    }

    //Se retorna el correlativo de la ciudad
    return numDestino;
}

void ganancias(){

    float ganancia1=0, ganancia2=0, gananciaTotal=0;

    for (int i = 0; i < listaPasajeros.size(); i++)
    {
        ganancia1+=(listaPasajeros[i].costoTotal);
    }

    for (int i = 0; i < pasajerosDiscapacitados.size(); i++)
    {
        ganancia2+=(pasajerosDiscapacitados[i].costoTotal);
    }

    gananciaTotal+=ganancia1+ganancia2;

    cout<<"\nGanancias por boletos: $"<<gananciaTotal<<endl << endl;
}

void verNums(int opt)
{
    if (cin.fail() || opt < 1 || opt > 4)
    {
        cout<<"Por favor, ingrese solo numeros. "<<endl;
        cin.clear();
        cin.ignore();
    } 
}