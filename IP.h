/*
Clase para manejo de direcciones IP como objetos
 */

#pragma once
#include <string>
using namespace std;

class IP {
public:
    // ===== CONSTRUCTORES =====

    IP();

    /*
    Constructor desde string
     text String con formato "A.B.C.D:puerto" o "A.B.C.D"
     Parsea el string y extrae los octetos y puerto
     */
    IP(const string& text);

    // ===== MÉTODOS GETTER =====

    unsigned short port() const;

    // Obtiene el texto original de la IP

    const string& original() const;

    // ===== OPERADORES DE COMPARACIÓN =====

    bool operator==(const IP& rhs) const;


    bool operator<(const IP& rhs) const;

private:
    // Extrae los octetos y puerto del string
    void parse(const string& text);

    // ===== MIEMBROS PRIVADOS =====
    string original_;                  ///< Texto original "A.B.C.D:puerto"
    unsigned short port_ = 0;          ///< Puerto numérico, 0 si no existe
    unsigned int octets_[4] = {0, 0, 0, 0}; ///< Octetos de la IP
};