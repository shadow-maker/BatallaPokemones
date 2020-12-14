#include "HeaderFiles/movimientos.h"

Movimiento::Movimiento(string nombre, int pp) : nombre(nombre), pp(pp) {}


string Movimiento::get_nombre() {
	return nombre;
}

string Movimiento::get_clase() {
	return clase;
}

template <typename T> void Movimiento::movAtaque(T &jugador) {}
template <typename T> void Movimiento::movStatus(T &jugador) {}


Ataque::Ataque(string nombre, int pp, int danio, Tipo tipo, string f_orE) : Movimiento(nombre, pp), danio(danio), tipo(tipo), f_orE(f_orE) {
	clase = "ataque";
}

int Ataque::get_danio() {
  return danio;
}

Tipo Ataque::get_tipo() {
  return tipo;
}

string Ataque::get_f_orE() {
  return f_orE;
}

template <typename T> void Ataque::movAtaque(T &jugador) {
	double multiplicador = getMatrixValue(jugador.get_tipo(), get_tipo()) / 2.0;
  if (get_f_orE() == "Fis") {
	jugador.quitarVida(get_danio()*multiplicador*jugador.get_bonus() - jugador.get_defensaF());

  } else if (get_f_orE() == "Esp") {
	jugador.quitarVida(get_danio()*multiplicador*jugador.get_bonus() - jugador.get_defensaE());
  }
  jugador.restartBonus();
  if (multiplicador == 2) {
	  cout << "Fue super efectivo!" << endl;
	}
  else if (multiplicador == 0.5) {
	  cout << "No fue tan efectivo..." << endl;
	}
}



Status::Status(string nombre, int pp, double mejoraAtaque, int mejoraDefensaF, int mejoraDefensaE, int mejoraVelocidad, int curaVida) : Movimiento(nombre, pp), mejoraAtaque(mejoraAtaque), mejoraDefensaF(mejoraDefensaF),  mejoraDefensaE(mejoraDefensaE), mejoraVelocidad(mejoraVelocidad), curaVida(curaVida) {
	clase = "status";
}

template <typename T> void Status::movStatus(T &jugador) {
	jugador.aumentarVida(curaVida);
	jugador.aumentarVelocidad(mejoraVelocidad);
	jugador.aumentarDefensaF(mejoraDefensaF);
	jugador.aumentarDefensaE(mejoraDefensaE);
	jugador.masBonus(mejoraAtaque);
}

int Status::get_mejoraAtaque () {
  return mejoraAtaque;
}

int Status::get_mejoraDefensaF () {
  return mejoraDefensaF;
}

int Status::get_mejoraDefensaE () {
  return mejoraDefensaE;
}

int Status::get_mejoraVelocidad () {
  return mejoraVelocidad;
}

int Status::get_curaVida () {
  return curaVida;
}
