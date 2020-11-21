#include <iostream>
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


extern destino ciudades[60][3]{
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

