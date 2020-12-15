#include "HeaderFiles/pokemones.h"

Pokemon::Pokemon(string nombre, const int vidaOrig, int velocidad, int defensaF, int defensaE, Tipo tipo) : nombre(nombre), vidaOrig(vidaOrig), vidaActual(vidaOrig), velocidad(velocidad), defensaF(defensaF), defensaE(defensaE), tipo(tipo) {
	switch (tipo) {
		case Tipo::fight:
			movimientos.push_back(Ataque("Karate Chop", 15, 50, Tipo::fight, "Fis"));
			movimientos.push_back(Ataque("Focus Blast", 5, 120, Tipo::fight, "Esp"));
			break;
		case Tipo::flying:
			movimientos.push_back(Ataque("Fly", 15, 50, Tipo::flying, "Esp"));
			movimientos.push_back(Ataque("Air Slash", 15, 75, Tipo::flying, "Esp"));
			break;
		case Tipo::ground:
			movimientos.push_back(Ataque("Earthquake", 5, 100, Tipo::ground, "Fis"));
			movimientos.push_back(Ataque("Mud Bomb", 15, 65, Tipo::ground, "Esp"));
			break;
		case Tipo::rock:
			movimientos.push_back(Ataque("Rock Slide", 10, 80, Tipo::rock, "Fis"));
			movimientos.push_back(Ataque("Power Gem", 15, 80, Tipo::rock, "Esp"));
			break;
		case Tipo::fire:
			movimientos.push_back(Ataque("Fire Fang", 15, 65, Tipo::fire, "Fis"));
			movimientos.push_back(Ataque("Fire Blast", 5, 110, Tipo::fire, "Esp"));
			break;
		case Tipo::water:
			movimientos.push_back(Ataque("Waterfall", 10, 80, Tipo::water, "Fis"));
			movimientos.push_back(Ataque("Surf", 10, 90, Tipo::water, "Esp"));
			break;
		case Tipo::electr:
			break;
		default:
			movimientos.push_back(Ataque("Spark", 15, 60, Tipo::electr, "Fis"));
			movimientos.push_back(Ataque("Thunder", 5, 110, Tipo::electr, "Esp"));
			break;
	}
}

void Pokemon::agregarMov(Movimiento movimiento) {
	movimientos.push_back(movimiento);
}

string Pokemon::get_nombre() {
	return nombre;
}

int Pokemon::get_vidaActual () {
	return vidaActual;
}

int Pokemon::get_velocidad () {
	return velocidad;
}

int Pokemon::get_defensaF () {
	return defensaF;
}

int Pokemon::get_defensaE () {
	return defensaE;
}

Tipo Pokemon::get_tipo() {
	return tipo;
}

double Pokemon::get_bonus() {
	return bonus;
}

void Pokemon::quitarVida(int cant) {
	vidaActual -= cant;
}

void Pokemon::aumentarVida(int cant) {
	vidaActual += cant;
}

void Pokemon::aumentarDefensaF(int cant) {
	defensaF += cant;
}

void Pokemon::aumentarDefensaE(int cant) {
	defensaE += cant;
}

void Pokemon::aumentarVelocidad(int cant) {
	velocidad += cant;
}

void Pokemon::masBonus(double cant) {
	bonus *= cant;
}

void Pokemon::restartBonus() {
	bonus = 1.0;
}

