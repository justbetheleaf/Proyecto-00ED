#pragma once
#include <string>
#include "Tiquete.h"

using std::string;
using std::ostream;

class Ventanilla
{
private:
	string nombre;
	Tiquete currentTiquete;
	int tiquetesAtendidos;
public:
	Ventanilla() {
		this->nombre = "";
		this->currentTiquete = Tiquete();
		this->tiquetesAtendidos = 0;
	}
	Ventanilla(string codeArea, int numVentana) {
		string intStr = std::to_string(numVentana);
		this->nombre = codeArea + intStr;
		this->currentTiquete = Tiquete();
		this->tiquetesAtendidos = 0;
	}

	string getNombre() {
		return nombre;
	}

	Tiquete getCurrentTiquete() {
		return currentTiquete;
	}

	//cada vez que un tiquete es atendido se incrementa el contador de tiquetes atendidos
	void atenderTiquete(Tiquete tiquete) {
		this->currentTiquete = tiquete;
		tiquetesAtendidos++;
	}

	//reiniciar valores
	void reiniciarVentanilla() {
		this->tiquetesAtendidos = 0;
		this->currentTiquete = Tiquete();
	}

	bool operator==(const Ventanilla& other) const {
		// Compare the 'nombre' attribute of the Ventanilla objects
		return this->nombre == other.nombre;
	}

	friend ostream& operator<<(ostream& os, const Ventanilla& ventanilla) {
		os << "Nombre: " << ventanilla.nombre;
		return os;
	}
};

