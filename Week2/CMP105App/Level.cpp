#include "Level.h"
#include <iostream>
#include <string>
using namespace std;

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	drag = false;
	mouseX = 0;
	mouseY = 0;
	old_mousex = 0;
	old_mousey = 0;
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cout << "Error loading arial\n";
	}

	mousepos.setPosition(10, 10);
	mousepos.setFont(font);
	mousepos.setFillColor(sf::Color::Black);

	rclick.setPosition(0, 0);
	rclick.setRadius(10);
	rclick.setFillColor(sf::Color::Red);
	rclick.setOrigin(10, 10);

}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	mouseX = input->getMouseX();
	mouseY = input->getMouseY();

	if (input->isKeyDown(sf::Keyboard::W)) { //test if w key pressed
		cout << "W key pressed" << endl;
		input->setKeyUp(sf::Keyboard::W);
	}
	if (input->isKeyDown(sf::Keyboard::J) && input->isKeyDown(sf::Keyboard::K) && input->isKeyDown(sf::Keyboard::L)) { //test if j, k, l pressed at same time
		cout << "You pressed a buncha keys at the same time" << endl;
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
	}
	
	if (input->isKeyDown(sf::Keyboard::Escape)) { //closes window (might have meant close console as well?)
		window->close();
	}

	if (input->isMouseLDown() && drag == false) {
		old_mousex = input->getMouseX();
		old_mousey = input->getMouseY();
		drag = true;
	}

	if (!input->isMouseLDown() && drag == true) {
		int mousex_change = mouseX - old_mousex;
		int mousey_change = mouseY - old_mousey;
		double drag_distance = sqrt((mousex_change * mousex_change) + (mousey_change * mousey_change));
		cout << "Total drag distance:" << drag_distance << endl;
		drag = false;
	}

	if (input->isMouseRDown()) {
		rclick.setPosition(mouseX, mouseY);
		input->setMouseRDown(false);
	}

	
}

// Update game objects
void Level::update()
{
	string mousepos_text("x:" + to_string(mouseX) + " y:" + to_string(mouseY));
	mousepos.setString(mousepos_text);
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(mousepos);
	window->draw(rclick);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}