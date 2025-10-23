#pragma once
#include <iostream>
#include <string>
#include "AccessRecord.h"
#include "BinarySearchTree.h"


class LogManager {
private:
    BinarySearchTree<AccessRecord> frequencyBST; // Lista que almacena todos los registros y sus frecuencias

public:
    // ===== CONSTRUCTORES Y DESTRUCTOR =====
    LogManager() = default;

    ~LogManager() = default;

    /*
    Metodo principal para procesar el archivo, contar frecuencias
    y construir el BST de AccessRecord.
    */
    void processLogFile(const std::string& filename);

    /*
    Metodo para encontrar y mostrar el Top K de IP's.
    */
    void findTopK(int k) const;
};