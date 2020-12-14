#pragma once

#include <iostream>
#include "getJson.h"

using namespace std;

enum Tipo {fight, flying, ground, rock, fire, water, electr, normal};

// Clase padre de Movimientos
class Movimiento {
	protected:
	string nombre;
	int pp;
	string clase;

	public:
	Movimiento(string nombre, int pp);

	//template <typename T> void movAtaque(T &jugador);
	//template <typename T> void movStatus(T &jugador);

	string get_nombre();
};

// Clase de movimientos de ataque
class Ataque : public Movimiento {
	int danio;
	Tipo tipo;
	string f_orE;

	public:
	Ataque(string nombre, int pp, int danio, Tipo tipo, string f_orE);

	template <typename T> void movAtaque(T &jugador);

	void masBonus(double cant);
	string get_clase();
	int get_danio();
	Tipo get_tipo();
	string get_f_orE();
};

// Clase de movimientos de status
class Status : public Movimiento {
	double mejoraAtaque;
	int mejoraDefensaF;
	int mejoraDefensaE;
	int mejoraVelocidad;
	int curaVida;
  
	public:
	Status(string nombre, int pp, double mejoraAtaque, int mejoraDefensaF, int mejoraDefensaE, int mejoraVelocidad, int curaVida);
	
	template <typename T> void movStatus(T &jugador);
	string get_clase();
	int get_mejoraAtaque();
	int get_mejoraDefensaF();
	int get_mejoraDefensaE();
	int get_mejoraVelocidad();
	int get_curaVida();
};
