#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <clocale>

using namespace std;

struct opcion{
    int num{};
    string texto;
    void (*funcion)(){};
};
typedef struct opcion Opcion;


vector<Opcion> poblarMenu(string *opciones, int cant, void (*funciones[])()){
    vector<Opcion> menu;
    for(int i = 0; i < cant; i++){
        Opcion unaOpcion;
        unaOpcion.num = i+1;
        unaOpcion.texto = *(opciones+i);
        unaOpcion.funcion = funciones[i];
        menu.insert(menu.end(), unaOpcion);
    }
    return menu;
}

void mostrarMenu(const vector<Opcion>& menu){
    bool continuar = true;
    int opcion = 0;
    while(continuar){
        cout << "\nMenu:\n\n";
        for(const Opcion& unaOpcion: menu){
            cout << unaOpcion.num << "] " << unaOpcion.texto << endl;
        }
        cout << "\nIntroduzca su opcion: ";
        cin >> opcion;
        cin.ignore();

        for(const Opcion& unaOpcion: menu){
            if(opcion == unaOpcion.num){
                unaOpcion.funcion();
                if(unaOpcion.num == menu.size()) continuar = false;
            }
        }
    }
}

//Funcion para verificar que el entero introducido sea valido
int validarNatural(string numero){ //Se pone como argumento el string del numero
    /*Mientras se introduzca un numero
        y alguno de sus caracteres no coincida con los permitidos:  */
    while(cin >> numero && numero.find_first_not_of("1234567890") != string::npos || atof(numero.c_str()) < 1){
        //Se advierte el error
        cout << "Numero invalido" << endl << endl;
        if(atof(numero.c_str()) < 1) //si el numero ingresado es negativo, tambien se advierte
            cout << "Debe ingresar un entero mayor o igual a 1." << endl;
        cout << "Por favor intente de nuevo: ";
        //Se borra la entrada anterior
        cin.clear();
        //Se descarta la entrada anterior
        cin.ignore(100, '\n');
    }
    return (int) atof(numero.c_str() );
}

//Funcion para verificar que el entero introducido sea valido
int validarEntero(string numero){ //Se pone como argumento el string del numero
    /*Mientras se introduzca un numero
        y alguno de sus caracteres no coincida con los permitidos:  */
    while(cin >> numero && numero.find_first_not_of("1234567890") != string::npos){
        //Se advierte el error
        cout << "Numero invalido" << endl << endl;
        if(atof(numero.c_str()) < 1) //si el numero ingresado es negativo, tambien se advierte
            cout << "Debe ingresar solo numeros digitos." << endl;
        cout << "Por favor intente de nuevo: ";
        //Se borra la entrada anterior
        cin.clear();
        //Se descarta la entrada anterior
        cin.ignore(100, '\n');
    }
    return (int) atof(numero.c_str() );
}

//Funcion para verificar que el flotante introducido sea valido
float validarFloat(string numero){ //Se pone como argumento el string del numero
    /*Mientras se introduzca un numero
        y alguno de sus caracteres no coincida con los permitidos:  */
    while(cin >> numero && numero.find_first_not_of(".1234567890") != string::npos || atof(numero.c_str()) < 1){
        //Se advierte el error
        cout << "Numero natural invalido" << endl << endl;
        if(atof(numero.c_str()) < 1) //si el numero ingresado es negativo, tambien se advierte
            cout << "Debe ingresar un numero positivo." << endl;
        cout << "Por favor intente de nuevo: ";
        //Se borra la entrada anterior
        cin.clear();
        //Se descarta la entrada anterior
        cin.ignore(100, '\n');
    }
    return (float) atof(numero.c_str() );
}

int validarRango(string numero, int min, int max){ //Se pone como argumento el string del numero
    /*Mientras se introduzca un numero
        y alguno de sus caracteres no coincida con los permitidos:  */
    while(cin >> numero && (numero.find_first_not_of("1234567890") != string::npos || (atof(numero.c_str()) > max)) || (atof(numero.c_str()) < min)){
        //Se advierte el error
        cout << "Numero invalido" << endl << endl;
        if(atof(numero.c_str()) < 1 || atof(numero.c_str()) > max) //si el numero ingresado es negativo, tambien se advierte
            cout << "Debe ingresar un entero entre " << min << " y " << max << endl;
        cout << "Por favor intente de nuevo: ";
        //Se borra la entrada anterior
        cin.clear();
        //Se descarta la entrada anterior
        cin.ignore(100, '\n');
    }
    return (int) atof(numero.c_str() );
}


string validarString(){
    string texto;
    bool valido = false;
    while(!valido ){
        getline(cin, texto);

        if(texto.empty() || texto.find_first_not_of(' ') == std::string::npos){
            cout << "Cadena de texto invalida." << endl;
            cout << "La cadena no puede estar vacia o contener solo espacios." << endl;
            cout << "Por favor intente de nuevo: ";

        } else valido = true;
    }
    return texto;
}
