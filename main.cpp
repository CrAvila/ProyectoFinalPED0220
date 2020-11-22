#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "rutas.hpp"
#include "maletas.hpp"
//#include "abordaje.hpp"

using namespace std;

//Andrea subio su codigo yay!

struct cliente
{
    string nombre;
    int edad;
    char discapacidad;
    ruta rutaVuelo;
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

ruta rutaCliente;

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
                //menu(listaPasajeros, pasajerosDiscapacitados);
            break;
            case 4:
                stop=false;
            break;

            default:
                cout<<"Opcion no valida. Intente de nuevo."<<endl;
            break;
        }
        
    } while (stop);

    ciudades[unPasajero[0].rutaVuelo.pares.front().destino].ciudad;

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
        cout<<"Ingrese el nombre del pasajero "<<cont+1<<": " ;
        getline(cin, unPasajero.nombre);
        cout<<"Ingrese la edad del pasajero "<<cont+1<<": ";
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
        
        //Retorna la ruta con todos sus datos
        rutaCliente = comenzarBusqueda(0, despliegueDestinos());

        unPasajero.rutaVuelo=rutaCliente;

        //cout << "Primer destino: " << ciudades[rutaCliente.pares.front().destino].ciudad << endl;
        
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
    //Se declaran variables temporales necesarias
    int opt = 0;
    vector<string> paises, ciudadesDisponibles;
    int counter = 0, optPais = 0, optFinal = 0, numDestino = 0;
    string pais, ciudad;

    //Se despliegan los continentes
    for(int i = 0; i < 5; i++) cout << i+1 << "] " << continentes[i] << endl;
    
    //Se solicita al usuario ingresar el numero de continente
    cout << endl << "Ingrese el numero del continente al que desea visitar: ";
    cin >> opt;
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
    cin >> optPais;
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
    cin >> optFinal;

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