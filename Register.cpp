//Implementacion de la clase 'Registro'.
#include "Register.h"
#include <sstream>

// ===== CONSTRUCTORES =====

/*
Constructor por defecto
Inicializa con valores vacíos
*/
Register::Register(): ip(IP()), falla(" "), fecha(" "){}

/*
Constructor con parámetros
Inicializa con los valores proporcionados
*/
Register::Register(IP _ip, string _falla, string _fecha){
    ip = _ip;
    falla = _falla;
    fecha = _fecha;
}

// ===== MÉTODOS GETTER =====

// Obtiene la IP como string
string Register::get_iP() const{
    return ip.original();
}

// Obtiene el objeto IP
IP Register::getIP() const{
    return ip;
}

// Obtiene el tipo de falla
string Register::get_falla() const{
    return falla;
}

// Obtiene la fecha del evento
string Register::get_fecha() const{
    return fecha;
}

// ===== MÉTODOS SETTER =====

// Establece la IP desde string
void Register::set_iP(const string& _iP){
    ip = _iP;
}

// Establece el tipo de falla
void Register::set_falla(const string& _falla){
    falla = _falla;
}

// Establece la fecha del evento
void Register::set_fecha(const string& _fecha){
    fecha = _fecha;
}

// ===== MÉTODOS ESTÁTICOS =====

/*
Crea un registro desde una línea de texto
Parsea una línea con formato: mes día hora IP mensaje_falla
*/
Register Register::fromLinea(const std::string& linea){
    // Realiza la lectura de la línea de texto
    stringstream iss(linea);

    // Declara las variables necesarias
    string mesStr,dia, horaStr, iP, falla;

    // Leer valores iniciales (mes, día, hora, IP)
    iss >> mesStr >> dia >> horaStr >> iP;

    // Convierte fecha y hora en uno solo
    string fecha = mesStr +" "+ dia +" "+ horaStr;

    // Leer el mensaje de falla (resto de la línea)
    getline(iss, falla);
    if (!falla.empty() && falla[0] == ' ') {
        falla.erase(0, 1); // Eliminar espacio inicial si existe
    }

    // Retorna el registro creado
    return Register(IP(iP), falla, fecha);
}

// ===== SOBRECARGA DE OPERADORES =====
/*
Operador menor que
Compara registros basándose en la IP
*/
bool Register::operator<(const Register& R1) const{
    // Utiliza el operador < de la clase IP
    return ip < R1.ip;
}

/*
Operador menor o igual
Compara registros basándose en la IP
*/
bool Register::operator==(const Register& R1) const{
    return (ip == R1.ip);
}

/*
Operador de inserción de flujo
Imprime el registro en formato legible
*/
ostream& operator<<(ostream& os, const Register& reg) {
    // Formato de salida: fecha IP - mensaje_falla
    os << reg.get_fecha() << " "
       << reg.get_iP() << " - "
       << reg.get_falla();

    return os;
}