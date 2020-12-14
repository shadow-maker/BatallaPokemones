#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include<unistd.h>

#include "ResourcePath.hpp" // Helper

using namespace sf;
using namespace std;

class Game {
	RenderWindow* window;
	VideoMode videoMode;
	Event event;
	
	Music music; // Music object
	Image icon; // Game icon
	
	void pollEvents();
	
public:
	Game(int width, int height, string name); // Constructor
	virtual ~Game(); // Destructor
	
	Keyboard::Key currentKey; // Current key being pressed
	
	// Metodos publicos
	const bool running() const;
	void update();
	void render(Color winColor);
	void endGame();
	
	void setIcon(string relPath);
	void playMusic(string relPath, int vol);
	void loadFont(string relPath);
	
	void clearGraphics();
	
	Font font; // Font object
	vector<Sprite> sprites; // Vector of Sprite objects
	vector<Text> texts; // Vector of Text objects
	vector<Texture> textures; // Vector of Image objects
	
	void setHeaderText(string contents, Color color);
	void setSubHeaderText(string contents, Color color);
	void setBottomText(string contents, Color color);
	
	void setChooseListText(vector<string> list, int posX, int posY);
};
