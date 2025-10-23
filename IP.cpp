#include "IP.h"
#include <stdexcept>

/*
Constructor por defecto
Inicializa todos los octetos en 0 y el puerto en 0
*/
IP::IP() : port_(0) {
    for (unsigned int & octet : octets_) octet = 0;
}

/*
Constructor desde string
Inicializa los octetos en 0 y parsea el string de entrada
*/
IP::IP(const string& text) : port_(0) {
    for (unsigned int & octet : octets_) octet = 0;
    parse(text);
}

// Obtiene el puerto asociado a la IP
unsigned short IP::port() const {
    return port_;
}

// Obtiene el texto original de la IP
const string& IP::original() const {
    return original_;
}

/*
Operador de igualdad
Compara octeto por octeto y el puerto
*/
bool IP::operator==(const IP& rhs) const {
    for (int i = 0; i < 4; ++i) {
        if (octets_[i] != rhs.octets_[i]) return false;
    }
    return port_ == rhs.port_;
}

/*
Operador menor que
Compara octeto por octeto de izquierda a derecha
*/
bool IP::operator<(const IP& rhs) const {
    for (int i = 0; i < 4; ++i) {
        if (octets_[i] < rhs.octets_[i]) return true;
        if (octets_[i] > rhs.octets_[i]) return false;
    }
    return port_ < rhs.port_;
}

/*
Función para parsear un string de IP
Extrae los octetos y puerto del string de entrada
*/
void IP::parse(const string& text) {
    original_ = text;

    string ipPart = text;
    string portPart;
    size_t colonPos = text.find(':');

    // Detecta el puerto si la cadena contiene un ':'
    if (colonPos != string::npos) {
        ipPart = text.substr(0, colonPos);
        portPart = text.substr(colonPos + 1);
    }

    // Parsea cada octeto de la IP
    size_t position = 0;
    for (unsigned int & index : octets_) {
        size_t dotPos = ipPart.find('.', position);
        string piece;

        if (dotPos == string::npos) {
            piece = ipPart.substr(position);
            position = ipPart.size();
        } else {
            piece = ipPart.substr(position, dotPos - position);
            position = dotPos + 1;
        }

        // Si el bloque está vacío, usar 0
        if (piece.empty()) {
            index = 0;
        } else {
            unsigned int octet = 0;
            try {
                octet = static_cast<unsigned int>(stoi(piece));
            } catch (const std::invalid_argument& e) {
                octet = 0; // En caso de error, usar 0
            }
            index = octet;
        }
    }

    // Convierte el puerto si venía en el texto; de lo contrario queda en cero
    if (!portPart.empty()) {
        try {
            port_ = static_cast<unsigned short>(stoi(portPart));
        } catch (const std::invalid_argument& e) {
            port_ = 0; // En caso de error, usar 0
        }
    } else {
        port_ = 0;
    }
}