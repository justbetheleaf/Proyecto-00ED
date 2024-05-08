#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::time_t;
using std::ostringstream;

class TipoUsuarioClientes
{
private:
    string descripcion;
    int prioridad;
    std::chrono::system_clock::time_point fechaCreacion;

public:
    TipoUsuarioClientes() {
        this->descripcion = "";
        this->prioridad = 99;
    }
    TipoUsuarioClientes(string descripcion, int prioridad) {
        this->descripcion = descripcion;
        this->prioridad = prioridad;
        this->fechaCreacion = std::chrono::system_clock::now();
    }
    ~TipoUsuarioClientes() {
    }

    string obtenerFechaComoCadena() const {
        std::time_t tiempo_actual = std::chrono::system_clock::to_time_t(fechaCreacion);
        std::tm tiempo;
        localtime_s(&tiempo, &tiempo_actual); // Utiliza localtime_s para evitar la advertencia
        const int buffer_size = 9; // Tamaño suficiente para la hora (HH:MM:SS) + el carácter nulo
        char buffer[buffer_size];
        std::strftime(buffer, buffer_size, "%H:%M:%S", &tiempo); // Formatear la hora en formato de 24 horas con minutos y segundos
        return string(buffer);
    }

    string getDescripcion() {
        return descripcion;
    }

    int getPrioridad() {
        return prioridad;
    }

    friend ostream& operator<<(ostream& os, const TipoUsuarioClientes& usuario) {
        os << "Descripción: " << usuario.descripcion << ", Prioridad: " << usuario.prioridad << ", Fecha de Creación: " << usuario.obtenerFechaComoCadena();
        return os;
    }

};
