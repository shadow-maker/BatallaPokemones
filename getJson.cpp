#include "HeaderFiles/getJson.h"

int getMatrixValue(int iDefend, int iAtack) {
	string line;
	ifstream file(resourcePath() + "interacciones.json");

	int countY = -1;
	int countX = -1;
	while (getline(file, line)) {
		countY++;
		if (countY == iAtack) {
			countX = -1;
			for (int i = 0; i < line.size(); i++) {
				if (line[i] != '[' && line[i] != ']' && line[i] != ' ' && line[i] != ',') {
					countX++;
					if (countX == iDefend) {
						return line[i] - '0';
					}
				}
			}
		}
	}
	return 0;
}

vector<string> getDictKeys(string relPath) {
	ifstream file(resourcePath() + relPath);
	json j = json::parse(file);
	
	vector<string> pokemones;
	
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		pokemones.push_back(it.key());
	}
	
	return pokemones;
}

vector<int> getDatosPokemon(string nombre) {
	ifstream file(resourcePath() + "pokemones.json");
	json j = json::parse(file);
	
	vector<int> datos {
		int(j[nombre]["vida"]),
		int(j[nombre]["velocidad"]),
		int(j[nombre]["defensaF"]),
		int(j[nombre]["defensaE"]),
		int(j[nombre]["tipo"])
	};
	
	return datos;
}

vector<int> getDatosMovimiento(string nombre) {
	ifstream file(resourcePath() + "movimientos.json");
	json j = json::parse(file);
	
	vector<int> datos;
	
	switch (int(j[nombre]["ataque"])) {
		case 0:
			datos = {
				int(j[nombre]["ataque"]),
				int(j[nombre]["pp"]),
				int(j[nombre]["mejoraAtaque"]),
				int(j[nombre]["mejoraDefensaF"]),
				int(j[nombre]["mejoraDefensaE"]),
				int(j[nombre]["mejoraVelocidad"]),
				int(j[nombre]["curaVida"])
			};
			break;
		case 1:
			datos = {
				int(j[nombre]["ataque"]),
				int(j[nombre]["pp"]),
				int(j[nombre]["danio"]),
				int(j[nombre]["fis"])
			};
			break;
		default:
			break;
	}

	return datos;
}
