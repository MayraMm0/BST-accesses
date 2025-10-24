// A01736199 Mayra Miranda Moreno
// A0 Juan Pablo Gavidia Alvarez
// 20 Oct 2025
// Act 3.4 - Actividad Integral de BST (Evidencia Competencia)

#include <iostream>
#include <string>
#include "LogManager.h" // Incluye la clase controladora

using namespace std;

// Nombre del archivo de bitácora
const string FILENAME = "bitacora_ordenada.txt";
// Constante para el requerimiento del Top 5
const int TOP_K = 5;

int main() {

    // 1. Crear una instancia de LogManager
    LogManager manager;

    try {
        // 2. Procesar el archivo: Contar frecuencias y construir el BST
        manager.processLogFile(FILENAME);

        // 3. Encontrar y mostrar las K IPs con más accesos
        // Esta llamada utilizará el método ReverseInOrder que modificaste.
        manager.findTopK(TOP_K);

    } catch (const std::exception& e) {
        cerr << "\nOcurrió un error crítico: " << e.what() << endl;
        return 1;
    }

    return 0;
}