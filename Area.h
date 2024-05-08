#pragma once
#include <string>
#include "Ventanilla.h"
#include "DLinkedList.h"
#include "PriorityQueue.h"
#include "HeapPriorityQueue.h"
#include "List.h"

using std::string;
class Area
{
private:
	string codigo;
	int numVentana;
	string descripcion;
	int cantVentanas;
	DLinkedList<Ventanilla>* ventanillas;
	PriorityQueue<Tiquete>* tiquetes;
	int tiquetesDispensados;
	int tiquetesAtendidos;
	double tiempoEspera;

public:
	Area() {
		this->descripcion = "";
		this->codigo = "";
		this->cantVentanas = 0;
		this->numVentana = 0;
		this->tiquetesDispensados = 0;
		this->tiempoEspera = 0;
	}
	Area(string descripcion, string codigo, int cantVentanas) {
		this->descripcion = descripcion;
		this->codigo = codigo;
		this->cantVentanas = cantVentanas;
		this->numVentana = 0;
		this->tiquetesDispensados = 0;
		this->tiempoEspera = 0;
		this->tiquetes = new HeapPriorityQueue<Tiquete>();
		ventanillas = new DLinkedList<Ventanilla>();
		for (int i = 0; i < cantVentanas; i++) {
			numVentana++;
			Ventanilla ventanaNueva(this->codigo, numVentana);
			ventanillas->append(ventanaNueva);
		}
		ventanillas->print("Ventanillas");
	}
	string getCodigo() {
		return this->codigo;
	}
	string getDescripcion() {
		return this->descripcion;
	}
	DLinkedList<Ventanilla>* getVentanillas() {
		return ventanillas;
	}
	PriorityQueue<Tiquete>* getTiquetes() {
		return tiquetes;
	}
	void setCantVentanillas(int cantVentanas) {
		this->numVentana = 0;
		ventanillas->clear();
		this->cantVentanas = cantVentanas;
		for (int i = 0; i < cantVentanas; i++) {
			numVentana++;
			Ventanilla ventanaNueva(this->codigo, numVentana);
			ventanillas->append(ventanaNueva);
		}
		ventanillas->print("Ventanillas");
	}

	void agregarTiquete(Tiquete tiquete, int prioridad) {
		this->tiquetes->insert(tiquete, prioridad);
		tiquetesDispensados++;
	}

	//incremente el contador de tiquetes atendidos
	void agregarTiquetesAtendidos() {
		tiquetesAtendidos++;
	}

	//incrementa el contador de tiquetes dispensados
	int getTiquetesDispensados() {
		return tiquetesDispensados;
	}

	void setCodigo() {
		this->codigo = "Z";
	}

	//realiza una sumatoria de todos los tiempos de espera de los tiquetes atendidos
	void agregarTiempoEspera(double tiempo) {
		this->tiempoEspera += tiempo;
	}

	//calcula el tiempo promedio de espera
	double getTiempoPromedioEspera() {
		if (this->tiempoEspera == 0.0) {
			return 0;
		}
		return this->tiempoEspera / this-> tiquetesAtendidos;
	}

	//reiniciar valores
	void reiniciarArea() {
		this->tiempoEspera = 0;
		this->tiquetesAtendidos = 0;
		this->tiquetesDispensados = 0;
		this->tiquetes = new HeapPriorityQueue<Tiquete>();

		//reinicia las ventanillas del area
		//recorre la lista de ventanillas
		ventanillas->goToStart();
		for (int i = 0; i < ventanillas->getSize(); ++i) {
			Ventanilla& current = ventanillas->getElement();
			current.reiniciarVentanilla();
			ventanillas->next();
		}
	}
	friend ostream& operator<<(ostream& os, const Area& area) {
		os << "Descripción: " << area.descripcion << ", Codigo: " << area.codigo << ", Cant.Ventanillas: " << area.cantVentanas;
		return os;
	}

};

