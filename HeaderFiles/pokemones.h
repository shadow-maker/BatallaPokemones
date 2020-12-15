#pragma once

#include <iostream>
#include <vector>
#include "movimientos.h"

using namespace std;

// Clase de Pokemones
class Pokemon {
	protected:
	string nombre;
	const int vidaOrig;
	int vidaActual;
	int velocidad;
	int defensaF;
	int defensaE;
	double bonus;
	Tipo tipo;

	public:
	Pokemon(string nombre, const int vidaOrig, int velocidad, int defensaF, int defensaE, Tipo tipo);
	
	vector<Movimiento> movimientos;

	void agregarMov(Movimiento movimiento);

	string get_nombre();
  
	int get_vidaActual ();
  
	int get_velocidad ();
  
	int get_defensaF ();
  
	int get_defensaE ();

	Tipo get_tipo();
	
	double get_bonus();

	void quitarVida(int cant);

	void aumentarVida(int cant);

	void aumentarDefensaF(int cant);
  
	void aumentarDefensaE(int cant);
	void aumentarVelocidad(int cant);

	void masBonus(double cant);

	void restartBonus();
};
