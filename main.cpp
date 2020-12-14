#include <iostream>
#include <string>
#include "HeaderFiles/game.h"
#include "HeaderFiles/getJson.h"
#include "HeaderFiles/pokemones.h"
#include "HeaderFiles/movimientos.h"

#include "ResourcePath.hpp" // Helper

using namespace std;


enum gameStage {
	splashscreen,
	elegirPokemon1,
	elegirPokemon2,
	elegirMovimientos1,
	elegirMovimientos2,
	iniciaJuego,
	finJuego
};

int getIndexByKey(Keyboard::Key key) {
	if (key > 25 && key < 36) {
		return key - 26;
	} else if (key > -1 && key < 26) {
		return key + 10;
	} else {
		return 0;
	}
}

int main() {
	
	Pokemon **jugadores = new Pokemon*[2];
	
	// Init game
	Game game(705, 645, "Batalla Pokemon");
	
	gameStage stage;
	stage = gameStage::splashscreen;

	game.setIcon("icon.png");
	game.loadFont("RetroGaming.ttf");
	game.playMusic("opening.ogg", 50);
	
	bool stageInit = false;
	string selec;
	
	// Game loop
	while (game.running()) {
		switch (stage) {
			case gameStage::splashscreen: { // Splashscreen
				if (!stageInit) {
					game.clearGraphics();
					
					Texture logoTexture;
					if (!logoTexture.loadFromFile(resourcePath() + "logo.png"))
						return EXIT_FAILURE;
					game.textures.push_back(logoTexture);
					Sprite logo(game.textures[game.textures.size() - 1]);
					logo.setScale(0.5, 0.5);
					logo.setPosition(20, 20);
					game.sprites.push_back(logo);
					
					game.setBottomText("PRESIONA -ESPACIO- PARA EMPEZAR", Color::Black);
					
					stageInit = true;
				}
				
				if (game.currentKey == Keyboard::Key::Space) {
					stageInit = false;
					stage = gameStage::elegirPokemon1;
				}
				break;
			}
			case gameStage::elegirPokemon1: {
				vector<string> pokemones = getPokemones();

				if (!stageInit) {
					game.clearGraphics();
					
					game.setHeaderText("JUGADOR 1:", Color::Red);
					game.setSubHeaderText("Elige tu pokemon!", Color::White);
					
					selec = pokemones[0];
					
					game.setChooseListText(pokemones, 20, 120);
					
					game.setBottomText("PRESIONA -ESPACIO- PARA COMFIRMAR", Color::Black);
					
					Text selected("SELECCIONADO: " + pokemones[0], game.font, 18);
					selected.setPosition(350, 450);
					selected.setFillColor(Color(50, 50, 50));
					game.texts.push_back(selected);
					
					stageInit = true;
				}
				
				if (getIndexByKey(game.currentKey) < pokemones.size() && game.currentKey >= 0 && game.currentKey != Keyboard::Key::Space) {
					selec = pokemones[getIndexByKey(game.currentKey)];
					game.texts.pop_back();
					Text selected("SELECCIONADO: " + pokemones[getIndexByKey(game.currentKey)], game.font, 18);
					selected.setPosition(350, 450);
					selected.setFillColor(Color(50, 50, 50));
					game.texts.push_back(selected);
				} else if (game.currentKey == Keyboard::Key::Space) {
					vector<int> datosSelec = getDatosPokemon(selec);
					jugadores[0] = new Pokemon(selec, datosSelec[0], datosSelec[1], datosSelec[2], datosSelec[3], static_cast<Tipo>(datosSelec[4]));
					stageInit = false;
					stage = gameStage::elegirPokemon2;
				}
				
				
				break;
			}
			case gameStage::elegirPokemon2: {
				vector<string> pokemones = getPokemones();

				if (!stageInit) {
					game.clearGraphics();
					
					game.setHeaderText("JUGADOR 2:", Color::Red);
					game.setSubHeaderText("Elige tu pokemon!", Color::White);
					
					selec = pokemones[0];
					
					game.setChooseListText(pokemones, 20, 120);
					
					game.setBottomText("PRESIONA -ESPACIO- PARA COMFIRMAR", Color::Black);
					
					Text selected("SELECCIONADO: " + pokemones[0], game.font, 18);
					selected.setPosition(350, 450);
					selected.setFillColor(Color(50, 50, 50));
					game.texts.push_back(selected);
					
					stageInit = true;
				}
				
				if (getIndexByKey(game.currentKey) < pokemones.size() && game.currentKey >= 0 && game.currentKey != Keyboard::Key::Space) {
					
					selec = pokemones[getIndexByKey(game.currentKey)];
					
					game.texts.pop_back();
					Text selected("SELECCIONADO: " + pokemones[getIndexByKey(game.currentKey)], game.font, 18);
					selected.setPosition(350, 450);
					selected.setFillColor(Color(50, 50, 50));
					game.texts.push_back(selected);
				} else if (game.currentKey == Keyboard::Key::Space) {
					vector<int> datosSelec = getDatosPokemon(selec);
					jugadores[1] = new Pokemon(selec, datosSelec[0], datosSelec[1], datosSelec[2], datosSelec[3], static_cast<Tipo>(datosSelec[4]));
					stageInit = false;
					stage = gameStage::elegirMovimientos1;
				}
				
				
				break;
			}
			default: {
				game.endGame();
				break;
			}
		}
		
		game.currentKey = Keyboard::Key::Unknown;
		
		// Update
		game.update();
		
		// Render
		game.render(Color(140, 200, 240));
	}
	
	cout<<jugadores[0]->get_nombre()<<endl;
	cout<<jugadores[0]->get_velocidad()<<endl;
	cout<<jugadores[1]->get_nombre()<<endl;
	cout<<jugadores[1]->get_velocidad()<<endl;
	
	// End of application
	return EXIT_SUCCESS;
}
