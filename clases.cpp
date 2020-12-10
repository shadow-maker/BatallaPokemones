// Clase padre de Movimientos
class Movimiento {
   protected:
	string nombre;
	int pp;

	Movimiento(string nombre, int pp) : nombre(nombre), pp(pp) {}
};

// Clase de movimientos de ataque
class Ataque : Movimiento {
	int danio;
	Tipo tipo;
	string fis_esp;

	Ataque(string nombre, int pp, int danio, Tipo tipo, string fis_esp) : Movimiento(nombre, pp), danio(danio), tipo(tipo), fis_esp(fis_esp) {}
};

// Clase de movimientos de status
class Status : Movimiento {
	int mejoraAtaque;
	int mejoraDefensaF;
	int mejoraDefensaE;
	int mejoraVelocidad;
	int curaVida;

	Status(string nombre, int pp, int mejoraAtaque, int mejoraDefensaF, int mejoraDefensaE, int mejoraVelocidad, int curaVida) : Movimiento(nombre, pp), mejoraAtaque(mejoraAtaque), mejoraDefensaF(mejoraDefensaF), mejoraDefensaE(mejoraDefensaE), mejoraVelocidad(mejoraVelocidad), curaVida(curaVida) {}
};

// Clase padre de Pokemones
class Pokemon {
   protected:
	string nombre;
	const int vidaOrig;
	int vidaActual;
	int velocidad;
	int defensa_fis;
	int defensa_esp;
	vector<Movimiento> movimientos;

	Pokemon(string nombre, const int vidaOrig, int velocidad, int defensa_fis, int defensa_esp, vector<Movimiento> movimientos) : nombre(nombre), vidaOrig(vidaOrig), vidaActual(vidaOrig), velocidad(velocidad), defensa_fis(defensa_fis), defensa_esp(defensa_esp), movimientos(movimientos) {}

	void quitarVida(int cant) {
		vidaActual -= cant;
	}

	void aumentarDefensaF(int cant) {
		defensa_fis += cant;
	}

	void aumentarDefensaE(int cant) {
		defensa_esp += cant;
	}
	void aumentarVelocidad(int cant) {
		velocidad += cant;
	}
};

// Clases hijas de tipos de pokemones
class tFight : Pokemon {
	tFight(string nombre, const int vidaOrig, int velocidad, int defensa_fis, int defensa_esp, vector<Movimiento> movimientos) : Pokemon(nombre, vidaOrig, velocidad, defensa_fis, defensa_esp, movimientos) {
		//TODO: Agregar movimientos unicos para el tipo
		//this->movimientos.push_back();
	}
};

class tFlying : Pokemon {
	tFlying(string nombre, const int vidaOrig, int velocidad, int defensa_fis, int defensa_esp, vector<Movimiento> movimientos) : Pokemon(nombre, vidaOrig, velocidad, defensa_fis, defensa_esp, movimientos) {
		//TODO: Agregar movimientos unicos para el tipo
		//this->movimientos.push_back();
	}
};

class tGround : Pokemon {
	tGround(string nombre, const int vidaOrig, int velocidad, int defensa_fis, int defensa_esp, vector<Movimiento> movimientos) : Pokemon(nombre, vidaOrig, velocidad, defensa_fis, defensa_esp, movimientos) {
		//TODO: Agregar movimientos unicos para el tipo
		//this->movimientos.push_back();
	}
};

class tRock : Pokemon {
	tRock(string nombre, const int vidaOrig, int velocidad, int defensa_fis, int defensa_esp, vector<Movimiento> movimientos) : Pokemon(nombre, vidaOrig, velocidad, defensa_fis, defensa_esp, movimientos) {
		//TODO: Agregar movimientos unicos para el tipo
		//this->movimientos.push_back();
	}
};

class tFire : Pokemon {
	tFire(string nombre, const int vidaOrig, int velocidad, int defensa_fis, int defensa_esp, vector<Movimiento> movimientos) : Pokemon(nombre, vidaOrig, velocidad, defensa_fis, defensa_esp, movimientos) {
		//TODO: Agregar movimientos unicos para el tipo
		//this->movimientos.push_back();
	}
};

class tElectr : Pokemon {
	tElectr(string nombre, const int vidaOrig, int velocidad, int defensa_fis, int defensa_esp, vector<Movimiento> movimientos) : Pokemon(nombre, vidaOrig, velocidad, defensa_fis, defensa_esp, movimientos) {
		//TODO: Agregar movimientos unicos para el tipo
		//this->movimientos.push_back();
	}
};