// LogManager.cpp
#include "LogManager.h"
#include "Register.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

// ----------------------------------------------------------------------
// Implementación del método principal para procesar el archivo de log
// ----------------------------------------------------------------------

/*
 * Procesa el archivo de log, contando la frecuencia de cada IP 
 * (aprovechando el pre-ordenamiento por IP) y construye el BST de frecuencias.
 */
void LogManager::processLogFile(const std::string& filename) {
    
    // Contenedor temporal para los pares (Frecuencia, IP)
    // Usa el nombre CORRECTO: AccessRecord
    vector<AccessRecord> frequencyList; 
    
    // Variables para el conteo lineal
    ifstream inputFile(filename);
    string line;
    IP currentIP;
    int currentCount = 0;
    bool first = true;

    if (!inputFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << endl;
        return;
    }

    // FASE 1: LECTURA, PARSEO Y CONTEO (O(n))
    cout << "1. Procesando archivo y contando frecuencias..." << endl;

    while (getline(inputFile, line)) {
        Register newReg = Register::fromLinea(line);
        IP newIP = newReg.getIP();

        if (first) {
            currentIP = newIP;
            currentCount = 1;
            first = false;
            continue;
        }

        if (newIP == currentIP) {
            currentCount++;
        } else {
            // Inserta el registro completo (Conteo e IP) en la lista temporal
            frequencyList.emplace_back(currentCount, currentIP);

            // Reinicia el conteo para la nueva IP
            currentIP = newIP;
            currentCount = 1;
        }
    }
    
    // Al finalizar el archivo, almacenar el último conteo
    if (currentCount > 0) {
        frequencyList.emplace_back(currentCount, currentIP);
    }

    inputFile.close();

    cout << "   -> Se encontraron " << frequencyList.size() << " IPs únicas." << endl;

    // FASE 2: CONSTRUCCIÓN DEL BST (O(m log m))
    cout << "2. Insertando registros en el BinarySearchTree..." << endl;
    
    // Insertar cada AccessRecord en el BST
    for (const auto& record : frequencyList) {
        frequencyBST.insert(record);
    }
    
    cout << "   -> BST de frecuencias construido exitosamente." << endl;
}

// ----------------------------------------------------------------------
// METODO PARA ENCONTRAR TOP K ELEMENTOS
// ----------------------------------------------------------------------

/*
 * Encuentra y muestra las K IP's con mayor número de accesos.
 */
void LogManager::findTopK(int k) const {
    // ... Lógica de recorrido In-Orden Inverso para Top K ...
    
    cout << "\n3. Buscando las " << k << " IPs con más accesos (Top " << k << ")..." << endl;
    cout << "   -> Esta operación requiere un método de recorrido In-Orden Inverso en BinarySearchTree.h." << endl;
}