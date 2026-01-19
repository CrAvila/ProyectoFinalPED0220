/**
 * ============================================================================
 * EVERYWHERE AIRLINES - Flight Routing Engine
 * ============================================================================
 * Graph-based route finding using DFS pathfinding algorithm
 * PRESERVED: All core data structures (list, queue, graph representation)
 * ENHANCED: Memory management, error handling, output formatting
 * ============================================================================
 */

#pragma once

#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ANSI Colors for route display
namespace RouteColors {
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
// Core Data Structures (PRESERVED - Soul of the project)
// ============================================================================

/**
 * Graph edge representation
 * PRESERVED: Original struct design
 */
struct Nodo {
    int inicio;
    int fin;
    int peso;
};

/**
 * City/Destination information
 * PRESERVED: Original struct design
 */
struct destino {
    string ciudad;
    string pais;
    string continente;
};

/**
 * Flight segment (origin -> destination with weight)
 * PRESERVED: Original struct design
 */
struct par {
    int origen;
    int destino;
    int peso;
};

/**
 * Complete route with queue of flight segments
 * PRESERVED: Original queue-based design
 */
struct ruta {
    queue<par> pares;  // Queue of flight segments
    float peso{};      // Total route weight
};

/**
 * Adjacency list data for graph
 * PRESERVED: Original struct design
 */
struct Data {
    int fin;
    int peso;
};

/**
 * Round trip (outbound + return)
 * PRESERVED: Original struct design
 */
struct idaYVuelta {
    ruta ida;
    ruta vuelta;
};

// ============================================================================
// Global State (PRESERVED for compatibility)
// ============================================================================

// Queue to store all found routes during pathfinding
queue<ruta> rutas;

// Complete round trip data
idaYVuelta viajeCompleto;

// Final total cost (set after route calculation)
float costoTotalFinal = 0;

// ============================================================================
// City Database - 60 Worldwide Cities
// PRESERVED: Original array with all city data
// ============================================================================

destino ciudades[60] = {
    {"San Salvador",        "El Salvador",            "America"},
    {"Los Angeles",         "Estados Unidos",         "America"},
    {"Washington",          "Estados Unidos",         "America"},
    {"Dubai",               "Emiratos Arabes Unidos", "Asia"},
    {"Kabul",               "Afganistan",             "Asia"},
    {"Madrid",              "Espana",                 "Europa"},
    {"Frankfurt",           "Alemania",               "Europa"},
    {"Ciudad de Guatemala", "Guatemala",              "America"},
    {"Nueva York",          "Estados Unidos",         "America"},
    {"Saint John",          "Antigua y Barbuda",      "America"},
    {"Amsterdam",           "Paises Bajos",           "Europa"},
    {"Nador",               "Marruecos",              "Africa"},
    {"Argel",               "Argelia",                "Africa"},
    {"Doha",                "Catar",                  "Asia"},
    {"Paris",               "Francia",                "Europa"},
    {"Ciudad de Panama",    "Panama",                 "America"},
    {"Buenos Aires",        "Argentina",              "America"},
    {"Nadi",                "Fiyi",                   "Oceania"},
    {"Melbourne",           "Australia",              "Oceania"},
    {"Houston",             "Estados Unidos",         "America"},
    {"Florida",             "Estados Unidos",         "America"},
    {"George Town",         "Bahamas",                "America"},
    {"Puerto Espana",       "Trinidad y Tobago",      "America"},
    {"Bridgetown",          "Barbados",               "America"},
    {"Belmopan",            "Belice",                 "America"},
    {"Bogota",              "Colombia",               "America"},
    {"La Paz",              "Bolivia",                "America"},
    {"Belo Horizonte",      "Brasil",                 "America"},
    {"Toronto",             "Canada",                 "America"},
    {"Varsovia",            "Polonia",                "Europa"},
    {"Munich",              "Alemania",               "Europa"},
    {"San Jose",            "Costa Rica",             "America"},
    {"Copenhage",           "Dinamarca",              "Europa"},
    {"Guayaquil",           "Ecuador",                "America"},
    {"Londres",             "Inglaterra",             "Europa"},
    {"Atenas",              "Grecia",                 "Europa"},
    {"Tegucigalpa",         "Honduras",               "America"},
    {"Chicago",             "Estados Unidos",         "America"},
    {"Nueva Delhi",         "India",                  "Asia"},
    {"Reikavik",            "Islandia",               "Europa"},
    {"Roma",                "Italia",                 "Europa"},
    {"Ciudad de Mexico",    "Mexico",                 "America"},
    {"Tokio",               "Japon",                  "Asia"},
    {"Shangai",             "China",                  "Asia"},
    {"California",          "Estados Unidos",         "America"},
    {"Taipei",              "Taiwan",                 "Asia"},
    {"Managua",             "Nicaragua",              "America"},
    {"Montevideo",          "Uruguay",                "America"},
    {"Lima",                "Peru",                   "America"},
    {"Asuncion",            "Paraguay",               "America"},
    {"Santiago",            "Chile",                  "America"},
    {"La Habana",           "Cuba",                   "America"},
    {"Atlanta",             "Estados Unidos",         "America"},
    {"Seul",                "Corea del Sur",          "Asia"},
    {"Seattle",             "Estados Unidos",         "America"},
    {"Tel Aviv",            "Israel",                 "Asia"},
    {"Mauricio",            "Mauricio",               "Africa"},
    {"Istambul",            "Turquia",                "Asia"},
    {"Lagos",               "Nigeria",                "Africa"},
    {"Zurich",              "Suiza",                  "Europa"},
};

// ============================================================================
// Flight Network - 114 Routes
// PRESERVED: Original graph edge definitions
// ============================================================================

Nodo node[114] = {
    {0, 1, 315},  {0, 5, 620},  {0, 7, 56},   {0, 15, 125}, {0, 19, 181},
    {0, 24, 90},  {0, 25, 180}, {0, 28, 290}, {0, 31, 76},  {0, 33, 180},
    {0, 36, 60},  {0, 41, 135}, {0, 46, 55},  {0, 52, 214}, {1, 3, 955},
    {1, 8, 307},  {1, 17, 640}, {1, 19, 195}, {2, 0, 286},  {2, 6, 460},
    {3, 2, 345},  {3, 4, 160},  {3, 38, 250}, {4, 3, 23},   {5, 6, 170},
    {5, 7, 695},  {6, 5, 205},  {6, 20, 660}, {6, 32, 80},  {6, 43, 640},
    {7, 0, 55},   {8, 0, 295},  {8, 2, 83},   {8, 9, 241},  {8, 10, 415},
    {8, 37, 152}, {8, 39, 345}, {8, 40, 495}, {8, 59, 450}, {9, 8, 274},
    {10, 11, 185},{11, 12, 115},{12, 13, 370},{13, 14, 430},{14, 8, 500},
    {14, 56, 670},{15, 0, 126}, {15, 16, 431},{15, 22, 192},{15, 27, 414},
    {15, 47, 377},{15, 48, 219},{15, 50, 382},{15, 51, 155},{16, 15, 442},
    {17, 18, 355},{18, 1, 855}, {19, 0, 184}, {19, 8, 218}, {19, 20, 150},
    {19, 57, 700},{20, 19, 155},{20, 21, 95}, {21, 20, 95}, {22, 15, 195},
    {22, 23, 55}, {23, 22, 60}, {24, 0, 85},  {25, 0, 185}, {25, 26, 225},
    {25, 49, 330},{26, 25, 230},{27, 15, 419},{28, 0, 300}, {28, 6, 455},
    {28, 19, 223},{28, 30, 470},{28, 34, 420},{28, 55, 625},{29, 28, 550},
    {30, 29, 90}, {31, 0, 78},  {32, 28, 485},{33, 0, 180}, {34, 19, 640},
    {34, 35, 215},{35, 34, 245},{36, 0, 55},  {37, 3, 805}, {38, 8, 935},
    {39, 8, 370}, {40, 6, 130}, {41, 0, 130}, {41, 42, 880},{42, 41, 735},
    {42, 45, 250},{43, 44, 660},{44, 19, 230},{45, 42, 200},{46, 0, 55},
    {47, 15, 369},{48, 15, 227},{49, 25, 325},{50, 15, 395},{51, 15, 165},
    {52, 53, 865},{53, 54, 605},{54, 1, 154}, {55, 28, 725},{56, 34, 730},
    {57, 8, 690}, {57, 58, 430},{58, 57, 390},{59, 28, 530},
};

// ============================================================================
// Graph Engine Variables
// ============================================================================

static const int NUM_CITIES = 60;
static const int NUM_ROUTES = 114;
static const float COST_PER_MINUTE = 2.73f;

int V = 0;           // Number of vertices
list<Data>* adj = nullptr;  // Pointer to adjacency list array

// ============================================================================
// Function Prototypes
// ============================================================================

void agregarBorde(Nodo n[], int v);
void imprimirTodosLosCaminos(int s, int d);
void buscarCaminos(int, int, bool[], int[], int&, ruta*);
ruta comenzarBusqueda(int s, int d);
ruta imprimirMejorRuta();

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * Validates city index is within bounds
 */
inline bool ciudadValida(int idx) {
    return idx >= 0 && idx < NUM_CITIES;
}

/**
 * Clears the global routes queue
 */
inline void limpiarRutas() {
    while (!rutas.empty()) {
        rutas.pop();
    }
}

/**
 * Frees the adjacency list memory
 */
inline void liberarGrafo() {
    if (adj != nullptr) {
        delete[] adj;
        adj = nullptr;
    }
}

/**
 * Formats currency for display
 */
inline string formatearPrecio(float precio) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "$%.2f", precio);
    return string(buffer);
}

// ============================================================================
// Main Search Function
// PRESERVED: Original algorithm logic
// ENHANCED: Memory management, validation, formatting
// ============================================================================

/**
 * Initiates route search from source to destination
 * Returns the best outbound route
 */
ruta comenzarBusqueda(int s, int d) {
    using namespace RouteColors;

    // Validate indices
    if (!ciudadValida(s) || !ciudadValida(d)) {
        cerr << RED << "Error: Indice de ciudad invalido." << RESET << endl;
        return ruta();
    }

    if (s == d) {
        cout << YELLOW << "Origen y destino son iguales. No se requiere vuelo." << RESET << endl;
        return ruta();
    }

    // Reset state
    costoTotalFinal = 0;
    limpiarRutas();
    liberarGrafo();

    // Initialize graph
    V = NUM_CITIES;
    adj = new list<Data>[V];

    agregarBorde(node, NUM_ROUTES);

    // Display header for outbound route
    cout << "\n";
    cout << CYAN << BOLD << "┌─────────────────────────────────────────────────────────────────┐" << RESET << "\n";
    cout << CYAN << BOLD << "│" << WHITE << "                    RUTA DE IDA                                  " << CYAN << "│" << RESET << "\n";
    cout << CYAN << BOLD << "│" << DIM << "  " << ciudades[s].ciudad << " → " << ciudades[d].ciudad << RESET;
    // Pad to align
    int padding = 60 - (ciudades[s].ciudad.length() + ciudades[d].ciudad.length() + 5);
    for (int i = 0; i < padding; i++) cout << " ";
    cout << CYAN << BOLD << "│" << RESET << "\n";
    cout << CYAN << BOLD << "└─────────────────────────────────────────────────────────────────┘" << RESET << "\n\n";

    // Find all paths
    imprimirTodosLosCaminos(s, d);

    // Get and store best outbound route
    ruta RutaFinal = imprimirMejorRuta();
    viajeCompleto.ida = RutaFinal;

    // Display header for return route
    cout << "\n";
    cout << MAGENTA << BOLD << "┌─────────────────────────────────────────────────────────────────┐" << RESET << "\n";
    cout << MAGENTA << BOLD << "│" << WHITE << "                    RUTA DE VUELTA                               " << MAGENTA << "│" << RESET << "\n";
    cout << MAGENTA << BOLD << "│" << DIM << "  " << ciudades[d].ciudad << " → " << ciudades[s].ciudad << RESET;
    padding = 60 - (ciudades[s].ciudad.length() + ciudades[d].ciudad.length() + 5);
    for (int i = 0; i < padding; i++) cout << " ";
    cout << MAGENTA << BOLD << "│" << RESET << "\n";
    cout << MAGENTA << BOLD << "└─────────────────────────────────────────────────────────────────┘" << RESET << "\n\n";

    // Find return paths
    limpiarRutas();
    imprimirTodosLosCaminos(d, s);

    // Get and store best return route
    viajeCompleto.vuelta = imprimirMejorRuta();

    // Calculate total cost
    costoTotalFinal = COST_PER_MINUTE * (viajeCompleto.ida.peso + viajeCompleto.vuelta.peso);

    // Cleanup
    liberarGrafo();

    return RutaFinal;
}

// ============================================================================
// Graph Construction
// PRESERVED: Original adjacency list logic
// ============================================================================

/**
 * Builds adjacency list from edge array
 */
void agregarBorde(Nodo n[], int v) {
    if (adj == nullptr) return;

    for (int i = 0; i < v; i++) {
        if (ciudadValida(n[i].inicio) && ciudadValida(n[i].fin)) {
            Data data;
            data.fin = n[i].fin;
            data.peso = n[i].peso;
            adj[n[i].inicio].push_back(data);
        }
    }
}

// ============================================================================
// Best Route Display
// PRESERVED: Original queue-based selection logic
// ENHANCED: Visual formatting
// ============================================================================

/**
 * Finds and displays the best (shortest) route from the routes queue
 * Returns the best route
 */
ruta imprimirMejorRuta() {
    using namespace RouteColors;

    if (rutas.empty()) {
        cout << YELLOW << "  No se encontraron rutas disponibles." << RESET << "\n";
        return ruta();
    }

    ruta mejorRuta;
    float menor = numeric_limits<float>::max();

    // PRESERVED: Original queue-based algorithm
    queue<ruta> temp;

    // Find minimum weight
    while (!rutas.empty()) {
        if (rutas.front().peso < menor) {
            menor = rutas.front().peso;
        }
        temp.push(rutas.front());
        rutas.pop();
    }

    // Display the best route
    int segmento = 1;
    while (!temp.empty()) {
        if (temp.front().peso == menor) {
            mejorRuta = temp.front();

            // Make a copy for display
            queue<par> displayQueue = temp.front().pares;

            while (!displayQueue.empty()) {
                par p = displayQueue.front();
                displayQueue.pop();

                float costSegmento = p.peso * COST_PER_MINUTE;

                cout << GREEN << "  " << segmento++ << ". " << RESET;
                cout << WHITE << ciudades[p.origen].ciudad << RESET;
                cout << DIM << " (" << ciudades[p.origen].pais << ")" << RESET;
                cout << CYAN << " ──► " << RESET;
                cout << WHITE << ciudades[p.destino].ciudad << RESET;
                cout << DIM << " (" << ciudades[p.destino].pais << ")" << RESET;
                cout << "\n";
                cout << DIM << "     └── " << p.peso << " min | " << formatearPrecio(costSegmento) << RESET << "\n";
            }

            float costoTotal = temp.front().peso * COST_PER_MINUTE;
            cout << "\n";
            cout << BOLD << "  ════════════════════════════════════════" << RESET << "\n";
            cout << BOLD << "  Total: " << GREEN << formatearPrecio(costoTotal) << RESET;
            cout << DIM << " (" << (int)temp.front().peso << " minutos)" << RESET << "\n";
            cout << BOLD << "  ════════════════════════════════════════" << RESET << "\n";

            break;  // Only show the best route
        }
        temp.pop();
    }

    return mejorRuta;
}

// ============================================================================
// Pathfinding - DFS Implementation
// PRESERVED: Original recursive DFS algorithm with queue-based path storage
// ============================================================================

/**
 * Prints all paths from source s to destination d
 */
void imprimirTodosLosCaminos(int s, int d) {
    if (adj == nullptr) return;

    // Mark all vertices as not visited
    bool* visited = new bool[V];

    // Create array to store paths
    int* path = new int[V];

    // Initialize path[] as empty
    int path_index = 0;

    // Initialize all vertices as not visited
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }

    // Call recursive helper function
    ruta unaRuta;
    buscarCaminos(s, d, visited, path, path_index, &unaRuta);

    // Cleanup
    delete[] visited;
    delete[] path;
}

/**
 * Recursive DFS pathfinding
 * PRESERVED: Original recursive algorithm with queue-based path storage
 */
void buscarCaminos(int u, int d, bool visited[], int path[], int& path_index, ruta* r) {
    // Mark current node and store in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    // If current vertex is destination, process the path
    if (u == d) {
        int routeWeight = 0;

        for (int i = 0; i < path_index; i++) {
            if (i + 1 < path_index) {
                int pesoTemp = 0;

                // Find edge weight
                for (int j = 0; j < NUM_ROUTES; j++) {
                    if (node[j].inicio == path[i] && node[j].fin == path[i + 1]) {
                        pesoTemp = node[j].peso;
                        routeWeight += pesoTemp;
                        break;
                    }
                }

                // PRESERVED: Original par struct and queue usage
                par unPar;
                unPar.origen = path[i];
                unPar.destino = path[i + 1];
                unPar.peso = pesoTemp;
                r->pares.push(unPar);
            }
        }

        r->peso = routeWeight;

        // PRESERVED: Push route to global queue
        rutas.push(*r);

        // Clear route for next iteration
        while (!r->pares.empty()) {
            r->pares.pop();
        }
    } else {
        // If current vertex is not destination, recurse
        // PRESERVED: Original list iterator usage
        list<Data>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            if (!visited[i->fin]) {
                buscarCaminos(i->fin, d, visited, path, path_index, r);
            }
        }
    }

    // Remove current vertex from path[] and mark as unvisited
    path_index--;
    visited[u] = false;
}
