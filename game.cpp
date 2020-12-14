#include "HeaderFiles/game.h"

// Constructor
Game::Game(int width, int height, string name) {
	videoMode.width = width; // Set width
	videoMode.height = height; // Set height
	
	// Initialize window
	this->window = new RenderWindow(this->videoMode, name, Style::Titlebar | Style::Close);
}

// Destructor
Game::~Game() {
	delete this->window;
}

// Event handler
void Game::pollEvents() {
	currentKey = Keyboard::Key::Unknown;
	while (this->window->pollEvent(event)) {
		switch (event.type) {
			case Event::Closed: // Window closed
				this->window->close();
				break;
			case Event::KeyPressed: // Key pressed
				if (event.key.code == Keyboard::Escape) // Escape pressed
					this->window->close();
				else if (event.key.code == Keyboard::Up)
					music.setVolume(music.getVolume() + 10);
				else if (event.key.code == Keyboard::Down)
					music.setVolume(music.getVolume() - 10);
				currentKey = event.key.code;
				break;
			default:
				break;
		}
	}
}

//
// Metodos publicos
//

// Get is Game Running
const bool Game::running() const {
	return this->window->isOpen();
}

// Update window
void Game::update() {
	this->pollEvents();
}

// Render window
void Game::render(Color winColor) {
	this->window->clear(winColor); // Clear old frames
	
	// Draw sprites
	for (Sprite sprite : sprites)
		this->window->draw(sprite);
	
	// Draw texts
	for (Text text : texts)
		this->window->draw(text);
	
	this->window->display(); // Display frame in window
}

// Close window
void Game::endGame() {
	this->window->close();
}

// Set icon image
void Game::setIcon(string relPath) {
	if (!icon.loadFromFile(resourcePath() + relPath)) {
		// Failed to load icon image
	}
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

// Load and play music file
void Game::playMusic(string relPath, int vol) {
	if (!music.openFromFile(resourcePath() + relPath)) {
		// Failed to load music file
	}
	music.setVolume(vol);
	music.setLoop(true);
	music.play();
}

// Load font file
void Game::loadFont(string relPath) {
	if (!font.loadFromFile(resourcePath() + relPath)) {
		// Failed to load font file
	}
}


//
// Vector methods
//

void Game::clearGraphics() {
	sprites.clear();
	texts.clear();
}

void Game::setHeaderText(string contents, Color color) {
	Text headerText(contents, font, 36);
	headerText.setPosition(20, 20);
	headerText.setFillColor(color);
	texts.push_back(headerText);
}

void Game::setSubHeaderText(string contents, Color color) {
	Text headerText(contents, font, 30);
	headerText.setPosition(40, 70);
	headerText.setFillColor(color);
	texts.push_back(headerText);
}

void Game::setBottomText(string contents, Color color) {
	Text headerText(contents, font, 22);
	headerText.setPosition(20, 600);
	headerText.setFillColor(color);
	texts.push_back(headerText);
}

void Game::setChooseListText(vector<string> list, int posX, int posY) {
	for (int i = 0; i < list.size(); i++) {
		char index = (i > 9) ? i + 55 : i + 48;
		Text indexText("[ " + string(1, index) + " ] - ", font, 18);
		indexText.setPosition(posX, posY + (i * 25));
		indexText.setFillColor(Color(230, 230, 230));
		texts.push_back(indexText);
		
		Text itemText(list[i], font, 22);
		itemText.setPosition(posX + 70, posY + (i * 25));
		texts.push_back(itemText);
	}
}
