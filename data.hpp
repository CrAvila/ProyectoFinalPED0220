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
        {"San Salvador", "El Salvador", "America"},
        {"Los Angeles", "Estados Unidos", "America"},
        {"Washington", "Estados Unidos", "America"},
        {"Dubai", "Emiratos \u00c1rabes Unidos", "Asia"},
        {"Kabul", "Afganist\u00e1n", "Asia"},
        {"Madrid", "Espana", "Europa"},
        {"Frankfurt", "Alemania", "Europa"},
        {"Ciudad de Guatemala", "Guatemala", "America"},
        {"Nueva York", "Estados Unidos", "America"},
        {"Saint John", "Antigua y Barbuda", "America"},
        {"Amsterdam", "Paises Bajos", "Europa"},
        {"Nador", "Marruecos", "\u00c1frica"},
        {"Argel", "Argelia", "\u00c1frica"},
        {"Doha", "Catar", "Asia"},
        {"Paris", "Francia", "Europa"},
        {"Ciudad de Panam\u00e1", "Panam\u00e1", "America"},
        {"Buenos Aires", "Argentina", "America"},
        {"Nadi", "Fiyi", "Oceania"},
        {"Melbourne", "Australia", "Oceania"},
        {"Houston", "Estados Unidos", "America"},
        {"Florida", "USA", "America"},
        {"George Town", "Bahamas", "America"},
        {"Puerto Espana", "Trinidad y Tobago", "America"},
        {"Bridgetown", "Barbados", "America"},
        {"Belmop\u00e1n", "Belice", "America"},
        {"Bogot\u00e1", "Colombia", "America"},
        {"La Paz", "Bolivia", "America"},
        {"Belo Horizonte", "Brasil", "America"},
        {"Toronto", "Canada", "America"},
        {"Varsovia", "Polonia", "Europa"},
        {"Munich", "Alemania", "Europa"},
        {"San Jose", "Costa Rica", "America"},
        {"Copenhage", "Dinamarca", "Europa"},
        {"Guayaquil", "Ecuador", "Europa"},
        {"Londres", "Inglaterra", "Europa"},
        {"Atenas", "Grecia", "Europa"},
        {"Tegucigalpa", "Honduras", "America"},
        {"Chicago", "Estados Unidos", "America"},
        {"Nueva Delhi", "India", "Asia"},
        {"Reikavik", "Islandia", "Europa"},
        {"Roma", "Italia", "Europa"},
        {"Ciudad de Mexico", "Mexico", "America"},
        {"Tokio", "Japon", "Asia"},
        {"Shangai", "China", "Asia"},
        {"California", "USA", "America"},
        {"Taipei", "Taiwan", "Asia"},
        {"Managua", "Nicaragua", "America"},
        {"Montevideo", "Uruguay", "America"},
        {"Lima", "Peru", "America"},
        {"Asunciòn", "Paraguay", "America"},
        {"Santiago", "Chile", "America"},
        {"La Habana", "Cuba", "America"},
        {"Atlanta", "Estados Unidos", "America"},
        {"Seul", "Corea del Sur", "Asia"},
        {"Seattle", "Estados Unidos", "America"},
        {"Tel Aviv", "Israel", "Asia"},
        {"Mauricio", "Mauricio", "Africa"},
        {"Istambul", "Turquia", "Asia"},
        {"Lagos", "Nigeria", "\u00c1frica"},
        {"Zurich", "Suiza", "Europa"},

};

