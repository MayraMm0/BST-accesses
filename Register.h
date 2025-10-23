/*
Esta clase encapsula la información de un registro de log incluyendo
la IP, el tipo de falla y la fecha del evento.
 */

#pragma once
#include <string>
#include <sstream>
#include "IP.h"
using namespace std;

class Register {

private:
    IP ip;        ///< Dirección IP del evento
    string falla; ///< Tipo de falla o evento de seguridad
    string fecha; ///< Fecha y hora del evento

public:
    // ===== CONSTRUCTORES Y DESTRUCTOR =====
    Register();

    Register(IP iP, string falla, string fecha);

    ~Register() = default;

    // ===== MÉTODOS GETTER =====

    //Obtiene la IP como string
    string get_iP() const;

    //Obtiene el objeto IP
    IP getIP() const;
    string get_falla() const;
    string get_fecha() const;

    // ===== MÉTODOS SETTER =====
    void set_iP(const string& _iP);
    void set_falla(const string& _falla);
    void set_fecha(const string& _fecha);

    // ===== MÉTODOS ESTÁTICOS =====

    //Crea un registro desde una línea de texto
    static Register fromLinea(const string& linea);

    // ===== SOBRECARGA DE OPERADORES =====
    bool operator<(const Register& R1) const;

    bool operator==(const Register& R1) const;

    friend std::ostream& operator<<(std::ostream& os, const Register& reg);

};
