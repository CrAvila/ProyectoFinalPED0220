/**
 * ============================================================================
 * EVERYWHERE AIRLINES - Boarding System Module
 * ============================================================================
 * Priority-based passenger boarding with gate management
 * PRESERVED: Vector-based passenger lists, priority queue logic
 * ENHANCED: Input validation, edge case handling, visual formatting
 * ============================================================================
 */

#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include "rutas.hpp"
#include "validaciones.hpp"

using namespace std;

// ANSI Colors for boarding display
namespace BoardColors {
    const string RESET   = "\033[0m";
    const string BOLD    = "\033[1m";
    const string DIM     = "\033[2m";
    const string CYAN    = "\033[36m";
    const string GREEN   = "\033[32m";
    const string YELLOW  = "\033[33m";
    const string BLUE    = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string WHITE   = "\033[97m";
    const string RED     = "\033[31m";
}

// ============================================================================
// Core Data Structures (PRESERVED)
// ============================================================================

/**
 * Passenger information structure
 * PRESERVED: Original struct design
 */
struct cliente {
    string nombre;
    int edad;
    char discapacidad;
    ruta rutaVuelo;
    float costoTotal;
};

/**
 * Boarding gate structure
 * PRESERVED: Original struct design
 */
struct puerta {
    string destino;
};

// Global gates vector (PRESERVED)
vector<puerta> puertas;

// ============================================================================
// Function Prototypes
// ============================================================================

void Crear_puerta(vector<cliente>, vector<cliente>);
void Abordar_pasajeros(puerta, vector<cliente>, vector<cliente>);

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * Clears the global gates vector for fresh boarding session
 */
inline void limpiarPuertas() {
    puertas.clear();
}

/**
 * Safely gets destination from a passenger's route
 * Returns empty string if route is empty
 */
inline string obtenerDestino(const cliente& c) {
    if (c.rutaVuelo.pares.empty()) {
        return "";
    }
    int destIdx = c.rutaVuelo.pares.front().destino;
    if (destIdx >= 0 && destIdx < 60) {
        return ciudades[destIdx].ciudad;
    }
    return "";
}

// ============================================================================
// Gate Creation and Boarding Initiation
// PRESERVED: Original vector iteration and gate creation logic
// ENHANCED: Input validation and edge case handling
// ============================================================================

/**
 * Creates boarding gates based on registered passengers
 * Prompts user to select a gate for boarding
 */
void Crear_puerta(vector<cliente> pasajeros, vector<cliente> pasajerosDiscapacitados) {
    using namespace BoardColors;

    // Clear previous gates
    limpiarPuertas();

    // Check if there are any passengers
    if (pasajeros.empty() && pasajerosDiscapacitados.empty()) {
        cout << "\n";
        cout << YELLOW << "┌─────────────────────────────────────────────────┐" << RESET << "\n";
        cout << YELLOW << "│" << WHITE << "  No hay ningun cliente registrado para abordar " << YELLOW << "│" << RESET << "\n";
        cout << YELLOW << "│" << DIM << "  Registre pasajeros primero (opcion 1)         " << YELLOW << "│" << RESET << "\n";
        cout << YELLOW << "└─────────────────────────────────────────────────┘" << RESET << "\n\n";
        return;
    }

    // Collect all unique destinations
    vector<string> destinosUnicos;

    // From regular passengers
    for (size_t i = 0; i < pasajeros.size(); i++) {
        string dest = obtenerDestino(pasajeros[i]);
        if (!dest.empty()) {
            // Check if destination already exists
            bool existe = false;
            for (size_t j = 0; j < destinosUnicos.size(); j++) {
                if (destinosUnicos[j] == dest) {
                    existe = true;
                    break;
                }
            }
            if (!existe) {
                destinosUnicos.push_back(dest);
            }
        }
    }

    // From priority passengers
    for (size_t i = 0; i < pasajerosDiscapacitados.size(); i++) {
        string dest = obtenerDestino(pasajerosDiscapacitados[i]);
        if (!dest.empty()) {
            bool existe = false;
            for (size_t j = 0; j < destinosUnicos.size(); j++) {
                if (destinosUnicos[j] == dest) {
                    existe = true;
                    break;
                }
            }
            if (!existe) {
                destinosUnicos.push_back(dest);
            }
        }
    }

    // Check if we found any destinations
    if (destinosUnicos.empty()) {
        cout << "\n" << RED << "  Error: No se encontraron destinos validos." << RESET << "\n\n";
        return;
    }

    // Display gates header
    cout << "\n";
    cout << CYAN << BOLD << "╔═══════════════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << CYAN << BOLD << "║" << WHITE << "              PUERTAS DE ABORDAJE DISPONIBLES                 " << CYAN << "║" << RESET << "\n";
    cout << CYAN << BOLD << "╚═══════════════════════════════════════════════════════════════╝" << RESET << "\n\n";

    // Create and display gates
    for (size_t i = 0; i < destinosUnicos.size(); i++) {
        puerta unaPuerta;
        unaPuerta.destino = destinosUnicos[i];
        puertas.push_back(unaPuerta);

        cout << GREEN << "  Puerta " << BOLD << (i + 1) << RESET;
        cout << DIM << " ────────► " << RESET;
        cout << WHITE << BOLD << destinosUnicos[i] << RESET << "\n";
    }

    cout << "\n";

    // Get user selection with validation
    int seleccion = 0;
    int maxPuertas = static_cast<int>(puertas.size());

    while (true) {
        cout << YELLOW << "Ingrese el numero de la puerta del vuelo que desea abordar: " << RESET;

        if (!(cin >> seleccion)) {
            if (cin.eof()) {
                cout << "\n" << YELLOW << "[Sesion terminada]" << RESET << "\n";
                return;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "  ✗ Por favor ingrese un numero valido." << RESET << "\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (seleccion < 1 || seleccion > maxPuertas) {
            cout << RED << "  ✗ Debe seleccionar una puerta entre 1 y " << maxPuertas << RESET << "\n";
            continue;
        }

        break;
    }

    // Proceed with boarding
    Abordar_pasajeros(puertas[seleccion - 1], pasajeros, pasajerosDiscapacitados);
}

// ============================================================================
// Passenger Boarding Display
// PRESERVED: Original vector iteration and priority passenger handling
// ENHANCED: Visual formatting and edge case handling
// ============================================================================

/**
 * Displays passengers boarding at a specific gate
 * Priority passengers (disabled/elderly) are shown first
 */
void Abordar_pasajeros(puerta unap, vector<cliente> pasajeros, vector<cliente> pasajerosDiscapacitados) {
    using namespace BoardColors;

    // Safety check
    if (pasajeros.empty() && pasajerosDiscapacitados.empty()) {
        cout << "\n" << YELLOW << "No hay registros de clientes." << RESET << "\n\n";
        return;
    }

    cout << "\n";
    cout << MAGENTA << BOLD << "╔═══════════════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << MAGENTA << BOLD << "║" << WHITE << "              ABORDAJE - PUERTA: " << BOLD << unap.destino;

    // Padding for alignment
    int padding = 28 - unap.destino.length();
    for (int i = 0; i < padding && i < 28; i++) cout << " ";

    cout << MAGENTA << BOLD << "║" << RESET << "\n";
    cout << MAGENTA << BOLD << "╚═══════════════════════════════════════════════════════════════╝" << RESET << "\n";

    int pasajerosEncontrados = 0;

    // PRIORITY PASSENGERS FIRST (disabled/elderly)
    // PRESERVED: Original priority queue logic
    bool hayPrioritarios = false;
    for (size_t i = 0; i < pasajerosDiscapacitados.size(); i++) {
        string destino = obtenerDestino(pasajerosDiscapacitados[i]);
        if (destino == unap.destino) {
            if (!hayPrioritarios) {
                cout << "\n";
                cout << YELLOW << BOLD << "  ★ PASAJEROS PRIORITARIOS (Abordaje Preferencial)" << RESET << "\n";
                cout << YELLOW << "  ─────────────────────────────────────────────────" << RESET << "\n";
                hayPrioritarios = true;
            }

            pasajerosEncontrados++;
            const cliente& c = pasajerosDiscapacitados[i];

            cout << "\n";
            cout << GREEN << "  ✓ " << BOLD << c.nombre << RESET << "\n";
            cout << DIM << "    Edad: " << RESET << c.edad << " años";
            if (c.edad > 65) {
                cout << YELLOW << " (Adulto Mayor)" << RESET;
            }
            if (c.discapacidad == 's') {
                cout << CYAN << " (Asistencia Especial)" << RESET;
            }
            cout << "\n";
            cout << DIM << "    Destino: " << RESET << destino << "\n";
        }
    }

    // REGULAR PASSENGERS
    // PRESERVED: Original vector iteration
    bool hayRegulares = false;
    for (size_t i = 0; i < pasajeros.size(); i++) {
        string destino = obtenerDestino(pasajeros[i]);
        if (destino == unap.destino) {
            if (!hayRegulares) {
                cout << "\n";
                cout << BLUE << BOLD << "  ◆ PASAJEROS REGULARES" << RESET << "\n";
                cout << BLUE << "  ─────────────────────────────────────────────────" << RESET << "\n";
                hayRegulares = true;
            }

            pasajerosEncontrados++;
            const cliente& c = pasajeros[i];

            cout << "\n";
            cout << WHITE << "  • " << BOLD << c.nombre << RESET << "\n";
            cout << DIM << "    Edad: " << RESET << c.edad << " años\n";
            cout << DIM << "    Destino: " << RESET << destino << "\n";
        }
    }

    // Summary
    cout << "\n";
    cout << CYAN << "═══════════════════════════════════════════════════════════════" << RESET << "\n";

    if (pasajerosEncontrados > 0) {
        cout << GREEN << BOLD << "  ✓ Abordaje iniciado para " << pasajerosEncontrados
             << " pasajero(s) con destino a " << unap.destino << RESET << "\n";
    } else {
        cout << YELLOW << "  No hay pasajeros registrados para este destino." << RESET << "\n";
    }

    cout << CYAN << "═══════════════════════════════════════════════════════════════" << RESET << "\n\n";
}
