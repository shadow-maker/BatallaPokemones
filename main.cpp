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
	elegirMovimientos1A,
	elegirMovimientos1B,
	elegirMovimientos2A,
	elegirMovimientos2B,
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

void movimiento(Pokemon &jugador, Pokemon &jugador2, int &opcion) {
  if (jugador.movimientos[opcion-1].get_clase() == "ataque") {
	  cout << "El " << jugador.get_nombre() << " utilizó " << jugador.movimientos[opcion-1].get_nombre() << "!" << endl;
	  jugador.movimientos[opcion-1].movAtaque<Pokemon> (jugador2);
  } else if (jugador.movimientos[opcion-1].get_clase() == "status") {
	  cout << "El " << jugador.get_nombre() << " utilizó " << jugador.movimientos[opcion-1].get_nombre() << "!" << endl;
	  jugador.movimientos[opcion-1].movStatus<Pokemon> (jugador);
	}
}

void ronda(Pokemon &jugador1, Pokemon &jugador2) {
  int opcion1, opcion2;
  cout << "Jugador 1, elija su movimiento!" << endl;
  for (int i=0;i<4;i++) {
	  cout << i+1 << ": " << jugador1.movimientos[i].get_nombre() << endl;
  }
  while (true) {
	  cin >> opcion1;
	  if (opcion1 >= 1 && opcion1 <= 4) {
		break;
	  } else {
		  cout << "Ingrese opción válida" << endl;
		  
	  }
  }
  cout << "Jugador 2, elija su movimiento!" << endl;
  for (int i=0;i<4;i++) {
	  cout << i+1 << ": " << jugador2.movimientos[i].get_nombre() << endl;
  }
  while (true) {
	  cin >> opcion2;
	  if (opcion2 >= 1 && opcion2 <= 4) {
		break;
	  } else {
		  cout << "Ingrese opción válida" << endl;
		  
	  }
  }
  if (jugador1.movimientos[opcion1-1].get_nombre() == "Quick Attack") {
	movimiento(jugador1, jugador2, opcion1);
  }

  if (jugador2.movimientos[opcion2-1].get_nombre() == "Quick Attack") {
	movimiento(jugador2, jugador1, opcion2);
  }

  if (jugador1.get_velocidad() > jugador2.get_velocidad()) {
	  movimiento(jugador1, jugador2, opcion1);
  } else if (jugador1.get_velocidad() < jugador2.get_velocidad()) {
	  movimiento(jugador2, jugador1, opcion2);
  } else {
		srand(time(NULL));
		int opcionR = rand() % 2;
		if (opcionR == 0) {
		  movimiento(jugador1, jugador2, opcion1);
		} else {
		  movimiento(jugador2, jugador1, opcion2);
		}
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
				vector<string> pokemones = getDictKeys("pokemones.json");

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
				vector<string> pokemones = getDictKeys("pokemones.json");

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
					stage = gameStage::elegirMovimientos1A;
				}
				
				break;
			}
			case gameStage::elegirMovimientos1A: {
				vector<string> movimientos = getDictKeys("movimientos.json");

				if (!stageInit) {
					game.clearGraphics();
					
					game.setHeaderText("JUGADOR 1:", Color::Red);
					game.setSubHeaderText("Elige tu primer movimiento extra!", Color::White);
					
					selec = movimientos[0];
					
					game.setChooseListText(movimientos, 20, 120);
					
					game.setBottomText("PRESIONA -ESPACIO- PARA COMFIRMAR", Color::Black);
					
					Text selected("SELECCIONADO: " + movimientos[0], game.font, 18);
					selected.setPosition(350, 450);
					selected.setFillColor(Color(50, 50, 50));
					game.texts.push_back(selected);
					
					stageInit = true;
				}
				
				if (getIndexByKey(game.currentKey) < movimientos.size() && game.currentKey >= 0 && game.currentKey != Keyboard::Key::Space) {
					
					selec = movimientos[getIndexByKey(game.currentKey)];
					
					game.texts.pop_back();
					Text selected("SELECCIONADO: " + movimientos[getIndexByKey(game.currentKey)], game.font, 18);
					selected.setPosition(350, 450);
					selected.setFillColor(Color(50, 50, 50));
					game.texts.push_back(selected);
				} else if (game.currentKey == Keyboard::Key::Space) {
					vector<int> datosSelec = getDatosMovimiento(selec);

					switch (datosSelec[0]) {
						case 0:
							jugadores[0]->agregarMov(Status(selec, datosSelec[1], double(datosSelec[2] / 2.0), datosSelec[3], datosSelec[4], datosSelec[5], datosSelec[6]));
							break;
						case 1:
							if (datosSelec[3] == 1)
								jugadores[0]->agregarMov(Ataque(selec, datosSelec[1], datosSelec[2], Tipo::normal, "Fis"));
							else
								jugadores[0]->agregarMov(Ataque(selec, datosSelec[1], datosSelec[2], Tipo::normal, "Esp"));
							break;
						default:
							break;
					}

					stageInit = false;
					stage = gameStage::elegirMovimientos1B;
				}
				
				break;
			}
			case gameStage::elegirMovimientos1B: {
				vector<string> movimientos = getDictKeys("movimientos.json");
				
				for (int i = 0; i < movimientos.size(); i++) {
					if (movimientos[i] == selec) {
						movimientos.erase(movimientos.begin() + i);
						break;
					}
				}

				if (!stageInit) {
					game.clearGraphics();
					
					game.setHeaderText("JUGADOR 1:", Color::Red);
					game.setSubHeaderText("Elige tu segundo movimiento extra!", Color::White);
					
					selec = movimientos[0];
					
					game.setChooseListText(movimientos, 20, 120);
					
					game.setBottomText("PRESIONA -ESPACIO- PARA COMFIRMAR", Color::Black);
					
					Text selected("SELECCIONADO: " + movimientos[0], game.font, 18);
					selected.setPosition(350, 450);
					selected.setFillColor(Color(50, 50, 50));
					game.texts.push_back(selected);
					
					stageInit = true;
				}
				
				if (getIndexByKey(game.currentKey) < movimientos.size() && game.currentKey >= 0 && game.currentKey != Keyboard::Key::Space) {
					
					selec = movimientos[getIndexByKey(game.currentKey)];
					
					game.texts.pop_back();
					Text selected("SELECCIONADO: " + movimientos[getIndexByKey(game.currentKey)], game.font, 18);
					selected.setPosition(350, 450);
					selected.setFillColor(Color(50, 50, 50));
					game.texts.push_back(selected);
				} else if (game.currentKey == Keyboard::Key::Space) {
					vector<int> datosSelec = getDatosMovimiento(selec);

					switch (datosSelec[0]) {
						case 0:
							jugadores[0]->agregarMov(Status(selec, datosSelec[1], double(datosSelec[2] / 2.0), datosSelec[3], datosSelec[4], datosSelec[5], datosSelec[6]));
							break;
						case 1:
							if (datosSelec[3] == 1)
								jugadores[0]->agregarMov(Ataque(selec, datosSelec[1], datosSelec[2], Tipo::normal, "Fis"));
							else
								jugadores[0]->agregarMov(Ataque(selec, datosSelec[1], datosSelec[2], Tipo::normal, "Esp"));
							break;
						default:
							break;
					}

					stageInit = false;
					stage = gameStage::elegirMovimientos2A;
				}
				
				break;
			}
			case gameStage::elegirMovimientos2A: {
				vector<string> movimientos = getDictKeys("movimientos.json");

				if (!stageInit) {
					game.clearGraphics();
					
					game.setHeaderText("JUGADOR 2:", Color::Red);
					game.setSubHeaderText("Elige tu primer movimiento extra!", Color::White);
					
					selec = movimientos[0];
					
					game.setChooseListText(movimientos, 20, 120);
					
					game.setBottomText("PRESIONA -ESPACIO- PARA COMFIRMAR", Color::Black);
					
					Text selected("SELECCIONADO: " + movimientos[0], game.font, 18);
					selected.setPosition(350, 450);
					selected.setFillColor(Color(50, 50, 50));
					game.texts.push_back(selected);
					
					stageInit = true;
				}
				
				if (getIndexByKey(game.currentKey) < movimientos.size() && game.currentKey >= 0 && game.currentKey != Keyboard::Key::Space) {
					
					selec = movimientos[getIndexByKey(game.currentKey)];
					
					game.texts.pop_back();
					Text selected("SELECCIONADO: " + movimientos[getIndexByKey(game.currentKey)], game.font, 18);
					selected.setPosition(350, 450);
					selected.setFillColor(Color(50, 50, 50));
					game.texts.push_back(selected);
				} else if (game.currentKey == Keyboard::Key::Space) {
					vector<int> datosSelec = getDatosMovimiento(selec);

					switch (datosSelec[0]) {
						case 0:
							jugadores[1]->agregarMov(Status(selec, datosSelec[1], double(datosSelec[2] / 2.0), datosSelec[3], datosSelec[4], datosSelec[5], datosSelec[6]));
							break;
						case 1:
							if (datosSelec[3] == 1)
								jugadores[1]->agregarMov(Ataque(selec, datosSelec[1], datosSelec[2], Tipo::normal, "Fis"));
							else
								jugadores[1]->agregarMov(Ataque(selec, datosSelec[1], datosSelec[2], Tipo::normal, "Esp"));
							break;
						default:
							break;
					}

					stageInit = false;
					stage = gameStage::elegirMovimientos2B;
				}
				
				break;
			}
			case gameStage::elegirMovimientos2B: {
				vector<string> movimientos = getDictKeys("movimientos.json");
				
				for (int i = 0; i < movimientos.size(); i++) {
					if (movimientos[i] == selec) {
						movimientos.erase(movimientos.begin() + i);
						break;
					}
				}

				if (!stageInit) {
					game.clearGraphics();
					
					game.setHeaderText("JUGADOR 2:", Color::Red);
					game.setSubHeaderText("Elige tu segundo movimiento extra!", Color::White);
					
					selec = movimientos[0];
					
					game.setChooseListText(movimientos, 20, 120);
					
					game.setBottomText("PRESIONA -ESPACIO- PARA COMFIRMAR", Color::Black);
					
					Text selected("SELECCIONADO: " + movimientos[0], game.font, 18);
					selected.setPosition(350, 450);
					selected.setFillColor(Color(50, 50, 50));
					game.texts.push_back(selected);
					
					stageInit = true;
				}
				
				if (getIndexByKey(game.currentKey) < movimientos.size() && game.currentKey >= 0 && game.currentKey != Keyboard::Key::Space) {
					
					selec = movimientos[getIndexByKey(game.currentKey)];
					
					game.texts.pop_back();
					Text selected("SELECCIONADO: " + movimientos[getIndexByKey(game.currentKey)], game.font, 18);
					selected.setPosition(350, 450);
					selected.setFillColor(Color(50, 50, 50));
					game.texts.push_back(selected);
				} else if (game.currentKey == Keyboard::Key::Space) {
					vector<int> datosSelec = getDatosMovimiento(selec);

					switch (datosSelec[0]) {
						case 0:
							jugadores[1]->agregarMov(Status(selec, datosSelec[1], double(datosSelec[2] / 2.0), datosSelec[3], datosSelec[4], datosSelec[5], datosSelec[6]));
							break;
						case 1:
							if (datosSelec[3] == 1)
								jugadores[1]->agregarMov(Ataque(selec, datosSelec[1], datosSelec[2], Tipo::normal, "Fis"));
							else
								jugadores[1]->agregarMov(Ataque(selec, datosSelec[1], datosSelec[2], Tipo::normal, "Esp"));
							break;
						default:
							break;
					}

					stageInit = false;
					stage = gameStage::elegirMovimientos2A;
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
