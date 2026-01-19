/**
 * ============================================================================
 * EVERYWHERE AIRLINES - Luggage Management Module
 * ============================================================================
 * Stack-based luggage tracking system
 * PRESERVED: Stack data structure for LIFO luggage handling
 * ENHANCED: Input validation, memory safety, visual formatting
 * ============================================================================
 */

#pragma once

#include <iostream>
#include <stack>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

// ANSI Colors for luggage display
namespace LuggageColors {
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
// Core Data Structure (PRESERVED)
// ============================================================================

/**
 * Luggage record structure
 * PRESERVED: Original struct with vector for weights
 */
struct maleta {
    int cantidad;
    vector<float> peso;  // Vector of individual bag weights
};

// ============================================================================
// Global State (PRESERVED - Stack for LIFO luggage handling)
// ============================================================================

stack<maleta> maletaPila;  // Main luggage stack

// ============================================================================
// Function Prototypes
// ============================================================================

int MenuMaletas();
void agregaMaletas();
void mostraPila(stack<maleta> Pila);

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * Safely reads an integer with validation
 * Returns -1 on EOF
 */
inline int leerEnteroMaletas() {
    string input;
    int resultado = 0;

    while (true) {
        if (!(cin >> input)) {
            if (cin.eof()) return -1;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << LuggageColors::RED << "  ✗ Entrada invalida." << LuggageColors::RESET << "\n";
            cout << "  Intente de nuevo: ";
            continue;
        }

        bool esValido = !input.empty();
        for (char c : input) {
            if (!isdigit(c)) {
                esValido = false;
                break;
            }
        }

        if (!esValido) {
            cout << LuggageColors::RED << "  ✗ Ingrese solo numeros." << LuggageColors::RESET << "\n";
            cout << "  Intente de nuevo: ";
            continue;
        }

        try {
            resultado = stoi(input);
        } catch (...) {
            cout << LuggageColors::RED << "  ✗ Numero fuera de rango." << LuggageColors::RESET << "\n";
            cout << "  Intente de nuevo: ";
            continue;
        }

        return resultado;
    }
}

/**
 * Safely reads a float with validation
 * Returns -1.0f on EOF
 */
inline float leerPesoMaleta() {
    string input;
    float resultado = 0.0f;

    while (true) {
        if (!(cin >> input)) {
            if (cin.eof()) return -1.0f;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << LuggageColors::RED << "  ✗ Entrada invalida." << LuggageColors::RESET << "\n";
            cout << "  Intente de nuevo: ";
            continue;
        }

        bool esValido = !input.empty();
        bool tienePunto = false;
        for (size_t i = 0; i < input.length(); i++) {
            char c = input[i];
            if (c == '.') {
                if (tienePunto) {
                    esValido = false;
                    break;
                }
                tienePunto = true;
            } else if (!isdigit(c)) {
                esValido = false;
                break;
            }
        }

        if (!esValido) {
            cout << LuggageColors::RED << "  ✗ Ingrese un peso valido." << LuggageColors::RESET << "\n";
            cout << "  Intente de nuevo: ";
            continue;
        }

        try {
            resultado = stof(input);
        } catch (...) {
            cout << LuggageColors::RED << "  ✗ Numero fuera de rango." << LuggageColors::RESET << "\n";
            cout << "  Intente de nuevo: ";
            continue;
        }

        if (resultado < 0.1f) {
            cout << LuggageColors::RED << "  ✗ El peso debe ser mayor a 0." << LuggageColors::RESET << "\n";
            cout << "  Intente de nuevo: ";
            continue;
        }

        if (resultado > 100.0f) {
            cout << LuggageColors::YELLOW << "  ⚠ Peso excede 100 lbs. Puede haber cargos adicionales." << LuggageColors::RESET << "\n";
        }

        return resultado;
    }
}

// ============================================================================
// Main Luggage Menu
// PRESERVED: Original menu loop structure
// ENHANCED: Input validation and visual formatting
// ============================================================================

/**
 * Main luggage management menu
 * Returns 0 on successful completion
 */
int MenuMaletas() {
    using namespace LuggageColors;

    cout << "\n";
    cout << CYAN << BOLD << "╔═══════════════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << CYAN << BOLD << "║" << WHITE << "           SISTEMA DE REGISTRO DE MALETAS                     " << CYAN << "║" << RESET << "\n";
    cout << CYAN << BOLD << "╚═══════════════════════════════════════════════════════════════╝" << RESET << "\n";

    bool seguir = true;

    while (seguir) {
        cout << "\n";
        cout << BLUE << "  ┌───────────────────────────────────────┐" << RESET << "\n";
        cout << BLUE << "  │" << WHITE << "              M E N U                  " << BLUE << "│" << RESET << "\n";
        cout << BLUE << "  ├───────────────────────────────────────┤" << RESET << "\n";
        cout << BLUE << "  │" << RESET << "  1. Agregar Maletas                   " << BLUE << "│" << RESET << "\n";
        cout << BLUE << "  │" << RESET << "  2. Ver Maletas Registradas           " << BLUE << "│" << RESET << "\n";
        cout << BLUE << "  │" << RESET << "  3. Finalizar Registro                " << BLUE << "│" << RESET << "\n";
        cout << BLUE << "  └───────────────────────────────────────┘" << RESET << "\n";
        cout << "\n";
        cout << YELLOW << "  Opcion: " << RESET;

        int opcion = leerEnteroMaletas();

        if (opcion == -1) {
            cout << "\n" << YELLOW << "[Sesion terminada]" << RESET << "\n";
            return 0;
        }

        switch (opcion) {
            case 1:
                agregaMaletas();
                break;
            case 2:
                mostraPila(maletaPila);
                break;
            case 3:
                seguir = false;
                cout << "\n" << GREEN << "  ✓ Registro de maletas completado." << RESET << "\n";
                break;
            default:
                cout << RED << "  ✗ Opcion invalida. Seleccione 1, 2 o 3." << RESET << "\n";
                break;
        }
    }

    return 0;
}

// ============================================================================
// Add Luggage Function
// PRESERVED: Stack push operation for luggage storage
// ENHANCED: Input validation and weight tracking
// ============================================================================

/**
 * Registers luggage for a passenger
 * PRESERVED: Original stack-based storage logic
 */
void agregaMaletas() {
    using namespace LuggageColors;

    maleta nuevaMaleta;
    nuevaMaleta.cantidad = 0;

    cout << "\n";
    cout << MAGENTA << "  ┌─────────────────────────────────────────┐" << RESET << "\n";
    cout << MAGENTA << "  │" << WHITE << "         REGISTRO DE MALETAS             " << MAGENTA << "│" << RESET << "\n";
    cout << MAGENTA << "  └─────────────────────────────────────────┘" << RESET << "\n";
    cout << "\n";

    // Get number of bags
    int cantidad = 0;
    while (true) {
        cout << "  Cuantas maletas desea registrar? (1-10): ";
        cantidad = leerEnteroMaletas();

        if (cantidad == -1) {
            cout << "\n" << YELLOW << "[Registro cancelado]" << RESET << "\n";
            return;
        }

        if (cantidad < 1) {
            cout << RED << "  ✗ Debe registrar al menos 1 maleta." << RESET << "\n";
            continue;
        }

        if (cantidad > 10) {
            cout << RED << "  ✗ Maximo 10 maletas por registro." << RESET << "\n";
            continue;
        }

        break;
    }

    nuevaMaleta.cantidad = cantidad;
    float pesoTotal = 0.0f;

    // Register each bag's weight
    for (int i = 0; i < cantidad; i++) {
        cout << "\n";
        cout << CYAN << "  Maleta #" << (i + 1) << " de " << cantidad << RESET << "\n";
        cout << "  Ingrese el peso en libras: ";

        float peso = leerPesoMaleta();

        if (peso < 0) {
            cout << "\n" << YELLOW << "[Registro cancelado]" << RESET << "\n";
            return;
        }

        nuevaMaleta.peso.push_back(peso);
        pesoTotal += peso;

        cout << GREEN << "  ✓ Maleta registrada: " << fixed << setprecision(1) << peso << " lbs" << RESET << "\n";
    }

    // PRESERVED: Push to stack (LIFO structure)
    maletaPila.push(nuevaMaleta);

    // Summary
    cout << "\n";
    cout << GREEN << "  ═══════════════════════════════════════════" << RESET << "\n";
    cout << GREEN << BOLD << "  ✓ REGISTRO EXITOSO" << RESET << "\n";
    cout << GREEN << "  ═══════════════════════════════════════════" << RESET << "\n";
    cout << "  Maletas registradas: " << cantidad << "\n";
    cout << "  Peso total: " << fixed << setprecision(1) << pesoTotal << " lbs\n";

    if (pesoTotal > 50.0f) {
        cout << YELLOW << "  ⚠ Nota: Peso total excede 50 lbs." << RESET << "\n";
        cout << YELLOW << "    Pueden aplicar cargos por exceso." << RESET << "\n";
    }

    cout << "\n";
}

// ============================================================================
// Display Luggage Stack
// PRESERVED: Stack traversal logic (copy to preserve original)
// ENHANCED: Visual formatting
// ============================================================================

/**
 * Displays all registered luggage
 * PRESERVED: Original stack-based display algorithm
 */
void mostraPila(stack<maleta> Pila) {
    using namespace LuggageColors;

    if (Pila.empty()) {
        cout << "\n";
        cout << YELLOW << "  ┌─────────────────────────────────────────┐" << RESET << "\n";
        cout << YELLOW << "  │" << WHITE << "  Pila vacia - No hay maletas registradas" << YELLOW << " │" << RESET << "\n";
        cout << YELLOW << "  └─────────────────────────────────────────┘" << RESET << "\n\n";
        return;
    }

    cout << "\n";
    cout << CYAN << BOLD << "  ╔═════════════════════════════════════════╗" << RESET << "\n";
    cout << CYAN << BOLD << "  ║" << WHITE << "       MALETAS REGISTRADAS              " << CYAN << "║" << RESET << "\n";
    cout << CYAN << BOLD << "  ╚═════════════════════════════════════════╝" << RESET << "\n";

    // PRESERVED: Original stack traversal algorithm
    // Copy stack to preserve original (stack is LIFO, can't iterate directly)
    stack<maleta> tempStack;
    int registroNum = Pila.size();

    // Transfer to temp stack (reverses order)
    while (!Pila.empty()) {
        tempStack.push(Pila.top());
        Pila.pop();
    }

    // Display from temp stack (now in original insertion order)
    float pesoGrandTotal = 0.0f;
    int maletasTotales = 0;

    while (!tempStack.empty()) {
        const maleta& m = tempStack.top();

        cout << "\n";
        cout << BLUE << "  ┌─── Registro #" << registroNum-- << " ───────────────────────┐" << RESET << "\n";
        cout << BLUE << "  │" << RESET << " Cantidad de maletas: " << BOLD << m.cantidad << RESET << "\n";

        float pesoRegistro = 0.0f;

        for (size_t i = 0; i < m.peso.size() && i < static_cast<size_t>(m.cantidad); i++) {
            cout << BLUE << "  │" << RESET << "   └── Maleta #" << (i + 1) << ": ";
            cout << WHITE << fixed << setprecision(1) << m.peso[i] << " lbs" << RESET << "\n";
            pesoRegistro += m.peso[i];
            maletasTotales++;
        }

        cout << BLUE << "  │" << DIM << " Subtotal: " << pesoRegistro << " lbs" << RESET << "\n";
        cout << BLUE << "  └────────────────────────────────────────┘" << RESET << "\n";

        pesoGrandTotal += pesoRegistro;
        tempStack.pop();
    }

    // Grand total
    cout << "\n";
    cout << GREEN << "  ═══════════════════════════════════════════" << RESET << "\n";
    cout << WHITE << BOLD << "  RESUMEN TOTAL" << RESET << "\n";
    cout << "  Total de maletas: " << maletasTotales << "\n";
    cout << "  Peso total: " << fixed << setprecision(1) << pesoGrandTotal << " lbs\n";
    cout << GREEN << "  ═══════════════════════════════════════════" << RESET << "\n\n";
}
