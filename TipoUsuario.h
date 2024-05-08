#pragma once
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::ostream;

class TipoUsuario
{
private:
	string descripcion;
	int prioridad;
	int tiquetesSolicitados;

public:
	TipoUsuario(){
		this->descripcion = "";
		this->prioridad = 99;
		this->tiquetesSolicitados = 0;
	}
	TipoUsuario(string descripcion, int prioridad) {
		this->descripcion = descripcion;
		this->prioridad = prioridad;
		this->tiquetesSolicitados = 0;
	}
	~TipoUsuario() {
	}

	string getDescripcion() {
		return descripcion;
	}

	int getPrioridad() {
		return prioridad;
	}

	void agregarTiqueteSolicitado() {
		tiquetesSolicitados++;
	}

	int getTiquetesSolicitados() {
		return tiquetesSolicitados;
	}

	//reiniciar valores
	void reiniciarUsuario() {
		this->tiquetesSolicitados = 0;
	}

	friend ostream& operator<<(ostream& os, const TipoUsuario& usuario) {
		os << "Descripción: " << usuario.descripcion << ", Prioridad: " << usuario.prioridad;
		return os;
	}

};