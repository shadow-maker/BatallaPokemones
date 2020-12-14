#include "HeaderFiles/getJson.h"

int getMatrixValue(int iDefend, int iAtack) {
	string line;
	ifstream file("JSON/interacciones.json");

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

vector<string> getPokemones() {
	ifstream file(resourcePath() + "pokemones.json");
	json j = json::parse(file);
	
	vector<string> pokemones;
	
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		pokemones.push_back(it.key());
	}
	
	return pokemones;
}

/*
Pokemon crearPokemon(string nombre) {
	ifstream file(resourcePath() + "pokemones.json");
	json j = json::parse(file);
	
	return Pokemon(nombre, j[nombre]["vidaOrig"], j[nombre]["velocidad"], j[nombre]["defensa_fis"], j[nombre]["defensa_esp"], static_cast<Tipo>(j[nombre]["tipo"]));
}*/

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
