#include <iostream>
#include <stack>
#include <vector>

using namespace std;
struct maleta{
    int cantidad;
    vector<float> peso;
};
int MenuMaletas ();
void mostraPila (stack < maleta >);
void agregaMaletas ();
int opcion;
stack < maleta >maletaPila;

int MenuMaletas ()
{
  cout << endl;    
  cout << "Bienvenido al sistema de registro de maletas" << endl;
  cout << endl;
  bool seguir = true;
  do
    {
      cout << "Ingrese el numero de la accion que desea realizar \n";
      cout<<endl;
	  cout << "------------      MENU       ------------" << endl << endl;
      cout <<"________________________________________"<< endl;
	  cout << "1. Agregar Maletas   " << endl;
	  cout << "2. Ver Maletas       " << endl;
  	  cout << "3. Salir             " << endl;
      cout << "________________________________________"<< endl;
      cout << "-----------------------------------------"<< endl;
      cout << endl;
      cout << " Opcion : "; 
      cin>> opcion;
      if(opcion==1){
         agregaMaletas();
      }else if(opcion == 2){
         mostraPila(maletaPila);
      }else if(opcion ==3){
         seguir = false;
      }else{
          cout << "Opcion Invalida\n\n";
      }
    }
  while (seguir);
return 0;
    
}

void agregaMaletas ()
{
  int cantidad;
  maleta mal;
  do{
    cout << endl;
    cout << "Cuantas maletas desea registar? : ";
    cin >> cantidad;
    
  } while(cantidad < 1);

  mal.cantidad = cantidad;
  mal.peso[cantidad];
      for (size_t i = 0; i < cantidad; i++){
          float pes;
        do{
          cout << endl;
          cout << "Ingrese el peso de la maleta #"<<(i+1) <<" en libras : ";
          cin >> pes;

          if(pes < 0.1){
              cout << "Ingrese un peso valido\n\n" << endl;
          }else{
              mal.peso.push_back(pes);
          }
        } while(pes < 0.1);
      }
  maletaPila.push(mal);
  cout << endl;
  cout << "Registro agregado con exito! \n\n";
  cout << endl;
}

void mostraPila(stack<maleta> Pila){
    if(Pila.size()<1){
        cout<< "Cola Vacia\n\n";
    }else{
        stack<maleta> Pila2;
        int canti = Pila.size(); 
        for(int i = 0; i < canti; i++){
           Pila2.push(Pila.top());
           Pila.pop();
       }
       for(int i = 0; i < canti; i++){
           cout << "Cliente #"<< (i+1)<< ":\n Cantidad de maletas: " << (Pila2.top()).cantidad << endl;
           for (size_t i = 0; i < (Pila2.top()).cantidad; i++)
           {
               cout << "       Maleta #" << (i+1) << ": " << (Pila2.top()).peso[i] <<" libras"<< "\n";
           }
           cout << "\n";
           Pila2.pop();
       }
    }
    cout << "\n\n";
}