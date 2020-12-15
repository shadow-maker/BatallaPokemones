//
//	Por:
//		- Eduardo Arrospide Gonzales
//		- Carlos Andrés Montoro Torres
//

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

void movAtaque(Pokemon &jugador, Movimiento ataque) {
	double multiplicador = getMatrixValue(jugador.get_tipo(), ataque.get_tipo())/2.0;
  if (ataque.get_f_orE() == "Fis") {
	jugador.quitarVida(ataque.get_danio()*multiplicador*jugador.get_bonus() - jugador.get_defensaF());

  } else if (ataque.get_f_orE() == "Esp") {
	jugador.quitarVida(ataque.get_danio()*multiplicador*jugador.get_bonus() - jugador.get_defensaE());
  }
  jugador.restartBonus();
  if (multiplicador == 2) {
	  cout << "Fue super efectivo!" << endl;
	}
  else if (multiplicador == 0.5) {
	  cout << "No fue tan efectivo..." << endl;
	} }

void movStatus(Pokemon &jugador, Movimiento status) {
	jugador.aumentarVida(status.get_curaVida());
	jugador.aumentarVelocidad(status.get_mejoraVelocidad());
	jugador.aumentarDefensaF(status.get_mejoraDefensaF());
	jugador.aumentarDefensaE(status.get_mejoraDefensaE());
	jugador.masBonus(status.get_mejoraAtaque());
  }


void movimiento(Pokemon &jugador, Pokemon &jugador2, int opcion) {
  if (jugador.movimientos[opcion-1].get_clase() == "ataque") {
	  cout << "El " << jugador.get_nombre() << " utilizó " << jugador.movimientos[opcion-1].get_nombre() << "!" << endl;
	  movAtaque(jugador2, jugador.movimientos[opcion-1]);
  } else if (jugador.movimientos[opcion-1].get_clase() == "status") {
	  cout << "El " << jugador.get_nombre() << " utilizó " << jugador.movimientos[opcion-1].get_nombre() << "!" << endl;
	  movStatus(jugador, jugador.movimientos[opcion-1]);
	}
}



int main() {
	
	Pokemon **jugadores = new Pokemon*[2];
	
	// Init game
	Game game(705, 645, "Batalla Pokemon");
	
	gameStage stage;
	stage = gameStage::splashscreen;
	
	int subStage = 0;

	game.setIcon("icon.png");
	game.loadFont("RetroGaming.ttf");
	game.playMusic("opening.ogg", 30);
	
	bool stageInit = false;
	string selec;
	string prevSelec;
	
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
					cout<<getIndexByKey(game.currentKey)<<endl;
					
					game.texts.pop_back();
					Text selected("SELECCIONADO: " + selec, game.font, 18);
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
					
					prevSelec = selec;

					stageInit = false;
					stage = gameStage::elegirMovimientos1B;
				}
				
				break;
			}
			case gameStage::elegirMovimientos1B: {
				vector<string> movimientos = getDictKeys("movimientos.json");
				
				for (int i = 0; i < movimientos.size(); i++) {
					if (movimientos[i] == prevSelec) {
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
					cout<<getIndexByKey(game.currentKey)<<endl;
					
					game.texts.pop_back();
					Text selected("SELECCIONADO: " + selec, game.font, 18);
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
					Text selected("SELECCIONADO: " + selec, game.font, 18);
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
					
					prevSelec = selec;

					stageInit = false;
					stage = gameStage::elegirMovimientos2B;
				}
				
				break;
			}
			case gameStage::elegirMovimientos2B: {
				vector<string> movimientos = getDictKeys("movimientos.json");
				
				for (int i = 0; i < movimientos.size(); i++) {
					if (movimientos[i] == prevSelec) {
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
					Text selected("SELECCIONADO: " + selec, game.font, 18);
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
					stage = gameStage::iniciaJuego;
				}
				
				break;
			}
			case gameStage::iniciaJuego: {
				// Mientras que los jugadores sigan vivos
				if (jugadores[0]->get_vidaActual() > 0 && jugadores[1]->get_vidaActual() > 0) {
					
					int opcion1, opcion2;
					vector<string> nombresMovimientos;

					switch (subStage) {
						case 0: {
							for (int i = 0; i < (jugadores[0]->movimientos).size() ; i++) {
								nombresMovimientos.push_back((jugadores[0]->movimientos)[i].get_nombre());
							}
							if (!stageInit) {
								game.clearGraphics();
								game.setHeaderText("JUGADOR 1:", Color::Red);
								game.setSubHeaderText("Juega tu primer movimiento!", Color::White);
								
								Text vida1("Vida del jugador 1: " + to_string(jugadores[0]->get_vidaActual()), game.font, 18);
								vida1.setPosition(20, 500);
								game.texts.push_back(vida1);
								
								Text vida2("Vida del jugador 2: " + to_string(jugadores[1]->get_vidaActual()), game.font, 18);
								vida2.setPosition(20, 540);
								game.texts.push_back(vida2);
								
								selec = nombresMovimientos[0];
								
								game.setChooseListText(nombresMovimientos, 20, 120);
								
								game.setBottomText("PRESIONA -ESPACIO- PARA COMFIRMAR", Color::Black);
								
								Text selected("SELECCIONADO: " + nombresMovimientos[0], game.font, 18);
								selected.setPosition(350, 450);
								selected.setFillColor(Color(50, 50, 50));
								game.texts.push_back(selected);
							}
							
							if (getIndexByKey(game.currentKey) < nombresMovimientos.size() && game.currentKey >= 0 && game.currentKey != Keyboard::Key::Space) {
								
								selec = nombresMovimientos[getIndexByKey(game.currentKey)];
								cout<<selec<<endl;
								
								game.texts.pop_back();
								Text selected("SELECCIONADO: " + selec, game.font, 18);
								selected.setPosition(350, 450);
								selected.setFillColor(Color(50, 50, 50));
								game.texts.push_back(selected);
							} else if (game.currentKey == Keyboard::Key::Space) {
								for (int i = 0; i < nombresMovimientos.size(); i++) {
									if (nombresMovimientos[i] == selec) {
										opcion1 = i + 1;
										break;
									}
								}
								
								stageInit = false;
								subStage++;
							}
							
							break;
						}
						case 1: {
							for (int i = 0; i < (jugadores[1]->movimientos).size() ; i++) {
								nombresMovimientos.push_back((jugadores[1]->movimientos)[i].get_nombre());
							}
							if (!stageInit) {
								game.clearGraphics();
								game.setHeaderText("JUGADOR 2:", Color::Red);
								game.setSubHeaderText("Juega tu primer movimiento!", Color::White);
								
								Text vida1("Vida del jugador 1: " + to_string(jugadores[0]->get_vidaActual()), game.font, 18);
								vida1.setPosition(20, 500);
								game.texts.push_back(vida1);
								
								Text vida2("Vida del jugador 2: " + to_string(jugadores[1]->get_vidaActual()), game.font, 18);
								vida2.setPosition(20, 540);
								game.texts.push_back(vida2);
								
								selec = nombresMovimientos[0];
								
								game.setChooseListText(nombresMovimientos, 20, 120);
								
								game.setBottomText("PRESIONA -ESPACIO- PARA COMFIRMAR", Color::Black);
								
								Text selected("SELECCIONADO: " + nombresMovimientos[0], game.font, 18);
								selected.setPosition(350, 450);
								selected.setFillColor(Color(50, 50, 50));
								game.texts.push_back(selected);
							}
							
							if (getIndexByKey(game.currentKey) < nombresMovimientos.size() && game.currentKey >= 0 && game.currentKey != Keyboard::Key::Space) {
								
								selec = nombresMovimientos[getIndexByKey(game.currentKey)];
								cout<<selec<<endl;
								
								game.texts.pop_back();
								Text selected("SELECCIONADO: " + selec, game.font, 18);
								selected.setPosition(350, 450);
								selected.setFillColor(Color(50, 50, 50));
								game.texts.push_back(selected);
							} else if (game.currentKey == Keyboard::Key::Space) {
								for (int i = 0; i < nombresMovimientos.size(); i++) {
									if (nombresMovimientos[i] == selec) {
										opcion2 = i + 1;
										break;
									}
								}
								
								stageInit = false;
								subStage++;
							}

							break;
						}
						case 2: {
							game.clearGraphics();
							if (jugadores[0]->movimientos[opcion1 - 1].get_nombre() == "Quick Attack") {
							  movimiento(*(jugadores[0]), *(jugadores[1]), opcion1);
							} else if (jugadores[1]->movimientos[opcion2 - 1].get_nombre() == "Quick Attack") {
							  movimiento(*(jugadores[1]), *(jugadores[0]), opcion2);
							} else {
								if (jugadores[0]->get_velocidad() > jugadores[1]->get_velocidad()) {
									movimiento(*(jugadores[0]), *(jugadores[1]), opcion1);
								} else if (jugadores[0]->get_velocidad() < jugadores[1]->get_velocidad()) {
									movimiento(*(jugadores[1]), *(jugadores[0]), opcion2);
								} else {
									  srand(time(NULL));
									  int opcionR = rand() % 2;
									  if (opcionR == 0) {
										movimiento(*(jugadores[0]), *(jugadores[1]), opcion1);
									  } else {
										movimiento(*(jugadores[1]), *(jugadores[0]), opcion2);
									  }
								  }
							}
							subStage = 0;
							break;
						}
					}
				} else {
					stageInit = false;
					stage = gameStage::finJuego;
				}

				break;
			}
			case gameStage::finJuego: {
				if (!stageInit) {
					game.clearGraphics();
					if (jugadores[0]->get_vidaActual() == 0) {
						game.setHeaderText("JUGADOR 2 HA GANADO", Color::Red);
					} else {
						game.setHeaderText("JUGADOR 1 HA GANADO", Color::Red);
					}
				}
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
