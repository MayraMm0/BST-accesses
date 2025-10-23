#pragma once

#include "IP.h"
#include <string>

class AccessRecord {
public:
    int accessCount;    // La CLAVE principal: número de accesos
    IP ipAddress;       // El VALOR asociado: la dirección IP

    // Constructor por defecto/parámetros
    AccessRecord(int count = 0, const IP& ip = IP())
        : accessCount(count), ipAddress(ip) {}

    // --- OPERADOR DE COMPARACIÓN PARA EL BST ---
    bool operator<(const AccessRecord& other) const {
        // 1. Criterio de Ordenamiento Principal (CLAVE): Frecuencia
        if (accessCount != other.accessCount) {
            // Si las frecuencias son distintas, ordena por frecuencia
            return accessCount < other.accessCount;
        }

        // 2. Manejo de "Repetidos": IP
        // Si las frecuencias son iguales, usa la IP para desempatar.
        // Esto garantiza que dos AccessRecord sean considerados distintos
        // permitiendo la inserción de ambos en un BST estándar.
        return ipAddress < other.ipAddress;
    }

    // Operador > (Útil para la lógica del BST)
    bool operator>(const AccessRecord& other) const {
        // Se puede definir así para simplicidad, asumiendo que no hay igualdad
        // perfecta si el operador < es bien implementado.
        return !(*this < other) && (accessCount != other.accessCount || ipAddress.original() != other.ipAddress.original());
    }
};