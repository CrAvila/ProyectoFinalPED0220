/**
 * ============================================================================
 * EVERYWHERE AIRLINES - Input Validation Module
 * ============================================================================
 * Robust input validation with graceful error handling
 * Handles EOF, invalid input, and edge cases
 * ============================================================================
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

// ANSI Colors for error messages
namespace ValidColors {
    const string RESET  = "\033[0m";
    const string RED    = "\033[31m";
    const string YELLOW = "\033[33m";
    const string GREEN  = "\033[32m";
    const string BOLD   = "\033[1m";
    const string DIM    = "\033[2m";
}

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * Clears cin error state and discards remaining input
 */
inline void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * Checks if cin has reached EOF (user pressed Ctrl+D)
 * Returns true if EOF detected
 */
inline bool verificarEOF() {
    if (cin.eof()) {
        cout << "\n" << ValidColors::YELLOW << "[Sesion terminada por el usuario]" << ValidColors::RESET << "\n";
        return true;
    }
    return false;
}

/**
 * Displays a formatted error message
 */
inline void mostrarError(const string& mensaje) {
    cout << ValidColors::RED << "  ✗ " << mensaje << ValidColors::RESET << "\n";
}

/**
 * Displays a success indicator
 */
inline void mostrarExito(const string& mensaje) {
    cout << ValidColors::GREEN << "  ✓ " << mensaje << ValidColors::RESET << "\n";
}

// ============================================================================
// Menu System (preserving original struct for compatibility)
// ============================================================================

struct opcion {
    int num{};
    string texto;
    void (*funcion)(){};
};
typedef struct opcion Opcion;

/**
 * Creates a menu from options array
 * PRESERVED: Original dynamic structure logic
 */
vector<Opcion> poblarMenu(string *opciones, int cant, void (*funciones[])()) {
    vector<Opcion> menu;
    for (int i = 0; i < cant; i++) {
        Opcion unaOpcion;
        unaOpcion.num = i + 1;
        unaOpcion.texto = *(opciones + i);
        unaOpcion.funcion = funciones[i];
        menu.push_back(unaOpcion);
    }
    return menu;
}

/**
 * Displays and handles menu interaction
 * PRESERVED: Original vector-based menu structure
 */
void mostrarMenu(const vector<Opcion>& menu) {
    bool continuar = true;
    int opcion = 0;

    while (continuar) {
        cout << "\nMenu:\n\n";
        for (const Opcion& unaOpcion : menu) {
            cout << unaOpcion.num << "] " << unaOpcion.texto << endl;
        }
        cout << "\nIntroduzca su opcion: ";

        if (!(cin >> opcion)) {
            if (verificarEOF()) return;
            limpiarBuffer();
            mostrarError("Por favor ingrese un numero valido.");
            continue;
        }
        limpiarBuffer();

        bool encontrado = false;
        for (const Opcion& unaOpcion : menu) {
            if (opcion == unaOpcion.num) {
                encontrado = true;
                unaOpcion.funcion();
                if (static_cast<size_t>(unaOpcion.num) == menu.size()) {
                    continuar = false;
                }
                break;
            }
        }

        if (!encontrado) {
            mostrarError("Opcion no valida. Intente de nuevo.");
        }
    }
}

// ============================================================================
// Number Validation Functions
// ============================================================================

/**
 * Validates a positive natural number (>= 1)
 * Handles: invalid input, negative numbers, decimals, EOF
 */
int validarNatural(const string& /* placeholder for compatibility */) {
    string numero;
    int resultado = 0;

    while (true) {
        if (!(cin >> numero)) {
            if (verificarEOF()) return -1;
            limpiarBuffer();
            mostrarError("Entrada invalida.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        // Check for valid digits only
        bool esValido = !numero.empty();
        for (char c : numero) {
            if (!isdigit(c)) {
                esValido = false;
                break;
            }
        }

        if (!esValido) {
            mostrarError("Debe ingresar solo digitos numericos.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        // Convert and validate range
        try {
            resultado = stoi(numero);
        } catch (...) {
            mostrarError("Numero fuera de rango.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        if (resultado < 1) {
            mostrarError("Debe ingresar un entero mayor o igual a 1.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        return resultado;
    }
}

/**
 * Validates any non-negative integer (>= 0)
 * Handles: invalid input, negative numbers, decimals, EOF
 */
int validarEntero(const string& /* placeholder for compatibility */) {
    string numero;
    int resultado = 0;

    while (true) {
        if (!(cin >> numero)) {
            if (verificarEOF()) return -1;
            limpiarBuffer();
            mostrarError("Entrada invalida.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        // Check for valid digits only
        bool esValido = !numero.empty();
        for (char c : numero) {
            if (!isdigit(c)) {
                esValido = false;
                break;
            }
        }

        if (!esValido) {
            mostrarError("Debe ingresar solo digitos numericos.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        try {
            resultado = stoi(numero);
        } catch (...) {
            mostrarError("Numero fuera de rango.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        return resultado;
    }
}

/**
 * Validates a positive float (> 0)
 * Handles: invalid input, negative numbers, EOF
 */
float validarFloat(const string& /* placeholder for compatibility */) {
    string numero;
    float resultado = 0.0f;

    while (true) {
        if (!(cin >> numero)) {
            if (verificarEOF()) return -1.0f;
            limpiarBuffer();
            mostrarError("Entrada invalida.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        // Check for valid float characters
        bool esValido = !numero.empty();
        bool tienePunto = false;
        for (size_t i = 0; i < numero.length(); i++) {
            char c = numero[i];
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
            mostrarError("Debe ingresar un numero decimal valido.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        try {
            resultado = stof(numero);
        } catch (...) {
            mostrarError("Numero fuera de rango.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        if (resultado < 0.1f) {
            mostrarError("Debe ingresar un numero positivo (mayor a 0).");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        return resultado;
    }
}

/**
 * Validates an integer within a specific range [min, max]
 * Handles: invalid input, out of range, EOF
 */
int validarRango(const string& /* placeholder */, int min, int max) {
    string numero;
    int resultado = 0;

    while (true) {
        if (!(cin >> numero)) {
            if (verificarEOF()) return -1;
            limpiarBuffer();
            mostrarError("Entrada invalida.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        // Check for valid digits only
        bool esValido = !numero.empty();
        for (char c : numero) {
            if (!isdigit(c)) {
                esValido = false;
                break;
            }
        }

        if (!esValido) {
            mostrarError("Debe ingresar solo digitos numericos.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        try {
            resultado = stoi(numero);
        } catch (...) {
            mostrarError("Numero fuera de rango.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        if (resultado < min || resultado > max) {
            cout << ValidColors::RED << "  ✗ Debe ingresar un numero entre "
                 << min << " y " << max << ValidColors::RESET << "\n";
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        // Clear remaining newline from buffer before returning
        limpiarBuffer();
        return resultado;
    }
}

// ============================================================================
// String Validation
// ============================================================================

/**
 * Validates a non-empty string
 * Handles: empty strings, whitespace-only strings, EOF
 */
string validarString() {
    string texto;

    while (true) {
        getline(cin, texto);

        if (cin.eof()) {
            cout << "\n" << ValidColors::YELLOW << "[Sesion terminada]" << ValidColors::RESET << "\n";
            return "";
        }

        if (cin.fail()) {
            cin.clear();
            mostrarError("Error de lectura.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        // Check for empty or whitespace-only
        bool soloEspacios = true;
        for (char c : texto) {
            if (!isspace(c)) {
                soloEspacios = false;
                break;
            }
        }

        if (texto.empty() || soloEspacios) {
            mostrarError("La cadena no puede estar vacia o contener solo espacios.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        return texto;
    }
}

/**
 * Validates a yes/no response (s/n)
 * Returns: 's' or 'n'
 */
char validarSiNo() {
    string respuesta;

    while (true) {
        if (!(cin >> respuesta)) {
            if (verificarEOF()) return 'n';
            limpiarBuffer();
            mostrarError("Entrada invalida.");
            cout << "  Por favor ingrese 's' o 'n': ";
            continue;
        }

        if (respuesta.length() == 1) {
            char c = tolower(respuesta[0]);
            if (c == 's' || c == 'n') {
                return c;
            }
        }

        mostrarError("Opcion invalida. Use 's' para si o 'n' para no.");
        cout << "  Por favor intente de nuevo (s/n): ";
    }
}

/**
 * Validates age input (1-150)
 * Returns: valid age or -1 on error
 */
int validarEdad() {
    string numero;
    int edad = 0;

    while (true) {
        if (!(cin >> numero)) {
            if (verificarEOF()) return -1;
            limpiarBuffer();
            mostrarError("Entrada invalida.");
            cout << "  Por favor ingrese una edad valida: ";
            continue;
        }

        // Check for valid digits only
        bool esValido = !numero.empty();
        for (char c : numero) {
            if (!isdigit(c)) {
                esValido = false;
                break;
            }
        }

        if (!esValido) {
            mostrarError("La edad debe contener solo numeros.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        try {
            edad = stoi(numero);
        } catch (...) {
            mostrarError("Numero fuera de rango.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        if (edad < 1 || edad > 150) {
            mostrarError("La edad debe estar entre 1 y 150 años.");
            cout << "  Por favor intente de nuevo: ";
            continue;
        }

        return edad;
    }
}
