#pragma once

#include "DLinkedList.h"
#include "DLinkedList.h"
#include "Servicio.h"

using std::string;

class Servicio {
private:
	string descripcion;
	int prioridad;
	Area* area;
	int tiquetesSolicitados;

public:
	Servicio() {

	}
	Servicio(string descripcion, int prioridad, Area* area) {
		this->area = area;
		this->descripcion = descripcion;
		this->prioridad = prioridad;
		this->tiquetesSolicitados = 0;
	}
	~Servicio() {

	}
	int getPrioridad() {
		return this->prioridad;
	}
	Area* getArea() {
		return this->area;
	}
	string getDescripcion() {
		return this->descripcion;
	}
	void agregarTiqueteSolicitado() {
		tiquetesSolicitados++;
	}
	int getTiquetesSolicitados() {
		return tiquetesSolicitados;
	}
	//reiniciar valores
	void reiniciarServicio() {
		this->tiquetesSolicitados = 0;
	}
	friend ostream& operator<<(ostream& os, const Servicio& servicio) {
		os << "Descripción: " << servicio.descripcion << ", Prioridad: " << servicio.prioridad <<", Código de área: " << servicio.area->getCodigo();
		return os;
	}
};