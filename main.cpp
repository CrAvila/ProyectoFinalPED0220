/**
 * ============================================================================
 * EVERYWHERE AIRLINES - Main Application
 * ============================================================================
 * Flight Reservation System with Graph-Based Route Optimization
 *
 * PRESERVED DATA STRUCTURES (Soul of the Project):
 * - vector<cliente>: Dynamic passenger storage
 * - queue<ruta>: Route pathfinding results
 * - stack<maleta>: LIFO luggage management
 * - list<Data>: Graph adjacency list
 * - set<string>: Unique destinations
 *
 * Final Project - Programacion de Estructuras Dinamicas (PED)
 * Ciclo 02/2020
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <cstring>

#include "rutas.hpp"
#include "maletas.hpp"
#include "abordaje.hpp"
#include "validaciones.hpp"
#include "logo.hpp"

using namespace std;

// ============================================================================
// ANSI Color Definitions
// ============================================================================

namespace MainColors {
    const string RESET   = "\033[0m";
    const string BOLD    = "\033[1m";
    const string DIM     = "\033[2m";
    const string CYAN    = "\033[36m";
    const string GREEN   = "\033[32m";
    const string YELLOW  = "\033[33m";
    const string BLUE    = "\033[34m";
    const string RED     = "\033[31m";
    const string WHITE   = "\033[97m";
    const string MAGENTA = "\033[35m";
}

// ============================================================================
// Function Prototypes
// ============================================================================

void clientes();
void ganancias();
int despliegueDestinos();
void mostrarMenuPrincipal();
void limpiarEstado();

// ============================================================================
// Global State (PRESERVED - Original vector-based passenger storage)
// ============================================================================

vector<cliente> listaPasajeros;           // Regular passengers
vector<cliente> pasajerosDiscapacitados;  // Priority passengers (disabled/elderly)
set<string> destinos;                     // Unique destinations (for gate creation)

string continentes[5] = {
    "America", "Africa", "Asia", "Europa", "Oceania"
};

ruta rutaCliente;  // Current route being processed

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * Comparison function for alphabetical sorting
 * PRESERVED: Original implementation
 */
bool compNombres(const string& a, const string& b) {
    return a < b;
}

/**
 * Clears input buffer safely
 */
void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * Checks for EOF condition
 */
bool esEOF() {
    if (cin.eof()) {
        cout << "\n" << MainColors::YELLOW << "[Sesion terminada por el usuario]"
             << MainColors::RESET << "\n\n";
        return true;
    }
    return false;
}

// ============================================================================
// Main Entry Point
// ============================================================================

int main() {
    using namespace MainColors;

    // Display welcome logo
    mostrarLogo();

    bool continuar = true;
    int opcion = 0;

    // Main application loop
    while (continuar) {
        mostrarMenuPrincipal();

        // Get menu selection with validation
        opcion = validarRango("", 1, 4);

        if (opcion == -1) {
            // EOF detected - graceful exit
            continuar = false;
            continue;
        }

        cout << CYAN << "════════════════════════════════════════════════════════" << RESET << "\n";

        switch (opcion) {
            case 1:
                clientes();
                break;

            case 2:
                ganancias();
                break;

            case 3:
                Crear_puerta(listaPasajeros, pasajerosDiscapacitados);
                break;

            case 4:
                continuar = false;
                cout << "\n";
                cout << GREEN << BOLD << "╔═══════════════════════════════════════════════════════════════╗" << RESET << "\n";
                cout << GREEN << BOLD << "║" << WHITE << "     Gracias por usar Everywhere Airlines. Buen viaje!         " << GREEN << "║" << RESET << "\n";
                cout << GREEN << BOLD << "╚═══════════════════════════════════════════════════════════════╝" << RESET << "\n\n";
                break;

            default:
                cout << RED << "Opcion no valida. Intente de nuevo." << RESET << "\n";
                break;
        }
    }

    return 0;
}

// ============================================================================
// Main Menu Display
// ============================================================================

void mostrarMenuPrincipal() {
    using namespace MainColors;

    cout << "\n";
    cout << CYAN << BOLD << "╔═══════════════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << CYAN << BOLD << "║" << WHITE << "                    M E N U   P R I N C I P A L                " << CYAN << "║" << RESET << "\n";
    cout << CYAN << BOLD << "╠═══════════════════════════════════════════════════════════════╣" << RESET << "\n";
    cout << CYAN << BOLD << "║" << RESET << "                                                               " << CYAN << BOLD << "║" << RESET << "\n";
    cout << CYAN << BOLD << "║" << RESET << "   " << GREEN << "1." << RESET << " Registrar nuevo pasajero                                 " << CYAN << BOLD << "║" << RESET << "\n";
    cout << CYAN << BOLD << "║" << RESET << "   " << GREEN << "2." << RESET << " Ver ganancias totales                                    " << CYAN << BOLD << "║" << RESET << "\n";
    cout << CYAN << BOLD << "║" << RESET << "   " << GREEN << "3." << RESET << " Iniciar proceso de abordaje                             " << CYAN << BOLD << "║" << RESET << "\n";
    cout << CYAN << BOLD << "║" << RESET << "   " << GREEN << "4." << RESET << " Salir del sistema                                       " << CYAN << BOLD << "║" << RESET << "\n";
    cout << CYAN << BOLD << "║" << RESET << "                                                               " << CYAN << BOLD << "║" << RESET << "\n";
    cout << CYAN << BOLD << "╚═══════════════════════════════════════════════════════════════╝" << RESET << "\n";

    // Show current stats
    int totalPasajeros = listaPasajeros.size() + pasajerosDiscapacitados.size();
    if (totalPasajeros > 0) {
        cout << DIM << "  Pasajeros registrados: " << totalPasajeros;
        cout << " | Destinos: " << destinos.size() << RESET << "\n";
    }

    cout << "\n" << YELLOW << "  Seleccione una opcion: " << RESET;
}

// ============================================================================
// Client Registration
// PRESERVED: Original data collection flow with vector storage
// ENHANCED: Input validation and visual formatting
// ============================================================================

void clientes() {
    using namespace MainColors;

    cliente unPasajero;  // PRESERVED: Original struct usage

    cout << "\n";
    cout << MAGENTA << BOLD << "╔═══════════════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << MAGENTA << BOLD << "║" << WHITE << "              REGISTRO DE NUEVO PASAJERO                       " << MAGENTA << "║" << RESET << "\n";
    cout << MAGENTA << BOLD << "╚═══════════════════════════════════════════════════════════════╝" << RESET << "\n\n";

    // --- Name Input ---
    cout << CYAN << "  ┌─ Datos Personales ─────────────────────────────────────┐" << RESET << "\n";
    cout << "  Ingrese el nombre del pasajero: ";

    unPasajero.nombre = validarString();
    if (unPasajero.nombre.empty()) {
        cout << YELLOW << "  [Registro cancelado]" << RESET << "\n\n";
        return;
    }

    // --- Age Input ---
    cout << "  Ingrese la edad del pasajero: ";
    unPasajero.edad = validarEdad();
    if (unPasajero.edad == -1) {
        cout << YELLOW << "  [Registro cancelado]" << RESET << "\n\n";
        return;
    }

    // --- Disability Status ---
    cout << "  Tiene alguna discapacidad? (s/n): ";
    unPasajero.discapacidad = validarSiNo();

    cout << CYAN << "  └────────────────────────────────────────────────────────┘" << RESET << "\n";

    // --- Destination Selection ---
    cout << "\n";
    cout << BLUE << "  ┌─ Seleccion de Destino ─────────────────────────────────┐" << RESET << "\n";
    cout << "  Continentes disponibles:\n\n";

    int destinoSeleccionado = despliegueDestinos();

    if (destinoSeleccionado <= 0 || destinoSeleccionado >= 60) {
        cout << YELLOW << "  [Destino invalido - Registro cancelado]" << RESET << "\n\n";
        return;
    }

    // --- Route Calculation ---
    // PRESERVED: Original graph-based route finding
    rutaCliente = comenzarBusqueda(0, destinoSeleccionado);

    // Validate route was found
    if (rutaCliente.pares.empty()) {
        cout << RED << "  No se encontro una ruta disponible." << RESET << "\n";
        cout << YELLOW << "  [Registro cancelado]" << RESET << "\n\n";
        return;
    }

    // Store passenger data
    unPasajero.rutaVuelo = rutaCliente;
    unPasajero.costoTotal = costoTotalFinal;

    string destinoData = ciudades[unPasajero.rutaVuelo.pares.front().destino].ciudad;

    // --- Display Cost Summary ---
    cout << "\n";
    cout << GREEN << BOLD << "  ╔═══════════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << GREEN << BOLD << "  ║" << WHITE << "                 RESUMEN DE RESERVA                        " << GREEN << "║" << RESET << "\n";
    cout << GREEN << BOLD << "  ╠═══════════════════════════════════════════════════════════╣" << RESET << "\n";
    cout << GREEN << BOLD << "  ║" << RESET << " Pasajero: " << BOLD << unPasajero.nombre << RESET;
    int padding = 48 - unPasajero.nombre.length();
    for (int i = 0; i < padding && i < 48; i++) cout << " ";
    cout << GREEN << BOLD << "║" << RESET << "\n";

    cout << GREEN << BOLD << "  ║" << RESET << " Destino:  " << BOLD << destinoData << RESET;
    padding = 48 - destinoData.length();
    for (int i = 0; i < padding && i < 48; i++) cout << " ";
    cout << GREEN << BOLD << "║" << RESET << "\n";

    cout << GREEN << BOLD << "  ║" << RESET << " Costo total (ida y vuelta): " << BOLD << "$"
         << fixed << setprecision(2) << unPasajero.costoTotal << RESET;
    char costStr[32];
    snprintf(costStr, sizeof(costStr), "%.2f", unPasajero.costoTotal);
    padding = 28 - strlen(costStr);
    for (int i = 0; i < padding && i < 28; i++) cout << " ";
    cout << GREEN << BOLD << "║" << RESET << "\n";

    cout << GREEN << BOLD << "  ╚═══════════════════════════════════════════════════════════╝" << RESET << "\n";

    // Track destination for gate creation
    destinos.insert(destinoData);

    // --- Luggage Registration ---
    cout << "\n";
    cout << YELLOW << "  Continuando al registro de maletas..." << RESET << "\n";
    cout << DIM << "  Presione Enter para continuar..." << RESET;
    cout.flush();

    limpiarEntrada();
    cin.get();

    MenuMaletas();

    // Clear any remaining input
    if (!cin.eof()) {
        limpiarEntrada();
    }

    // --- Store Passenger ---
    // PRESERVED: Original priority queue logic (disabled/elderly get priority)
    if (unPasajero.discapacidad == 's' || unPasajero.edad > 65) {
        pasajerosDiscapacitados.push_back(unPasajero);
        cout << "\n" << GREEN << "  ✓ Pasajero registrado con " << BOLD << "ABORDAJE PRIORITARIO"
             << RESET << GREEN << "." << RESET << "\n";
        if (unPasajero.edad > 65) {
            cout << DIM << "    (Adulto mayor - 65+ años)" << RESET << "\n";
        }
        if (unPasajero.discapacidad == 's') {
            cout << DIM << "    (Requiere asistencia especial)" << RESET << "\n";
        }
    } else {
        listaPasajeros.push_back(unPasajero);
        cout << "\n" << GREEN << "  ✓ Pasajero registrado exitosamente." << RESET << "\n";
    }

    cout << "\n";
}

// ============================================================================
// Destination Selection Menu
// PRESERVED: Original hierarchical selection (Continent -> Country -> City)
// PRESERVED: Original vector and sorting algorithms
// ============================================================================

int despliegueDestinos() {
    using namespace MainColors;

    // PRESERVED: Original variable declarations
    int opt = 0;
    vector<string> paises, ciudadesDisponibles;
    int counter = 0, optPais = 0, optFinal = 0, numDestino = 0;
    string pais, ciudad;

    // Display continents
    for (int i = 0; i < 5; i++) {
        cout << "    " << GREEN << (i + 1) << "." << RESET << " " << continentes[i] << "\n";
    }

    // Get continent selection
    cout << "\n  Seleccione el continente: ";
    opt = validarRango("", 1, 5);
    if (opt == -1) return -1;

    string continente = continentes[opt - 1];

    // --- Country Selection ---
    cout << "\n  Paises disponibles en " << BOLD << continente << RESET << ":\n\n";

    // PRESERVED: Original vector population logic
    for (int i = 1; i < 60; i++) {
        if (ciudades[i].continente == continente) {
            paises.push_back(ciudades[i].pais);
        }
    }

    // PRESERVED: Original sorting and deduplication
    sort(paises.begin(), paises.end(), compNombres);
    paises.erase(unique(paises.begin(), paises.end()), paises.end());

    // Display countries
    counter = 0;
    for (vector<string>::iterator it = paises.begin(); it != paises.end(); ++it) {
        counter++;
        cout << "    " << GREEN << counter << "." << RESET << " " << *it << "\n";
    }

    // Get country selection
    cout << "\n  Seleccione el pais: ";
    optPais = validarRango("", 1, static_cast<int>(paises.size()));
    if (optPais == -1) return -1;

    // PRESERVED: Original iterator-based selection
    counter = 0;
    for (vector<string>::iterator it = paises.begin(); it != paises.end(); ++it) {
        counter++;
        if (counter == optPais) {
            pais = *it;
            break;
        }
    }

    // --- City Selection ---
    cout << "\n  Ciudades disponibles en " << BOLD << pais << RESET << ":\n\n";

    // PRESERVED: Original city population logic
    for (int i = 1; i < 60; i++) {
        if (ciudades[i].pais == pais) {
            ciudadesDisponibles.push_back(ciudades[i].ciudad);
        }
    }

    // PRESERVED: Original sorting and deduplication
    sort(ciudadesDisponibles.begin(), ciudadesDisponibles.end(), compNombres);
    ciudadesDisponibles.erase(unique(ciudadesDisponibles.begin(), ciudadesDisponibles.end()),
                              ciudadesDisponibles.end());

    // Display cities
    counter = 0;
    for (vector<string>::iterator it = ciudadesDisponibles.begin();
         it != ciudadesDisponibles.end(); ++it) {
        counter++;
        cout << "    " << GREEN << counter << "." << RESET << " " << *it << "\n";
    }

    // Get city selection
    cout << "\n  Seleccione la ciudad: ";
    optFinal = validarRango("", 1, static_cast<int>(ciudadesDisponibles.size()));
    if (optFinal == -1) return -1;

    // PRESERVED: Original city name extraction
    counter = 0;
    for (vector<string>::iterator it = ciudadesDisponibles.begin();
         it != ciudadesDisponibles.end(); ++it) {
        counter++;
        if (counter == optFinal) {
            ciudad = *it;
            break;
        }
    }

    // PRESERVED: Original city index lookup
    for (int i = 1; i < 60; i++) {
        if (ciudades[i].ciudad == ciudad) {
            numDestino = i;
            break;
        }
    }

    cout << BLUE << "  └────────────────────────────────────────────────────────┘" << RESET << "\n";

    return numDestino;
}

// ============================================================================
// Revenue Display
// PRESERVED: Original calculation logic
// ============================================================================

void ganancias() {
    using namespace MainColors;

    float ganancia1 = 0.0f, ganancia2 = 0.0f, gananciaTotal = 0.0f;

    // PRESERVED: Original vector iteration
    for (size_t i = 0; i < listaPasajeros.size(); i++) {
        ganancia1 += listaPasajeros[i].costoTotal;
    }

    for (size_t i = 0; i < pasajerosDiscapacitados.size(); i++) {
        ganancia2 += pasajerosDiscapacitados[i].costoTotal;
    }

    gananciaTotal = ganancia1 + ganancia2;

    cout << "\n";
    cout << GREEN << BOLD << "╔═══════════════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << GREEN << BOLD << "║" << WHITE << "                  REPORTE DE GANANCIAS                        " << GREEN << "║" << RESET << "\n";
    cout << GREEN << BOLD << "╠═══════════════════════════════════════════════════════════════╣" << RESET << "\n";

    cout << GREEN << BOLD << "║" << RESET << " Pasajeros regulares:     " << setw(5) << listaPasajeros.size()
         << "  |  $" << setw(10) << fixed << setprecision(2) << ganancia1 << "       " << GREEN << BOLD << "║" << RESET << "\n";

    cout << GREEN << BOLD << "║" << RESET << " Pasajeros prioritarios:  " << setw(5) << pasajerosDiscapacitados.size()
         << "  |  $" << setw(10) << fixed << setprecision(2) << ganancia2 << "       " << GREEN << BOLD << "║" << RESET << "\n";

    cout << GREEN << BOLD << "╠═══════════════════════════════════════════════════════════════╣" << RESET << "\n";

    cout << GREEN << BOLD << "║" << WHITE << BOLD << " TOTAL:                   " << setw(5)
         << (listaPasajeros.size() + pasajerosDiscapacitados.size())
         << "  |  $" << setw(10) << fixed << setprecision(2) << gananciaTotal << "       " << GREEN << BOLD << "║" << RESET << "\n";

    cout << GREEN << BOLD << "╚═══════════════════════════════════════════════════════════════╝" << RESET << "\n";

    if (gananciaTotal == 0) {
        cout << "\n" << DIM << "  No hay ventas registradas aun." << RESET << "\n";
    }

    cout << "\n";
}
