#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

#define MAX_LICZBA_POZIOMOW 4 // Nowa Gra, Wczytaj Grê, Wyniki, Wyjœcie

class Menu
{
private:
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW];
	int selectedItem = 0;

public:
	Menu(float width, float height);
	~Menu() {};

	void przesunG();
	void przesunD();
	int getSelectedItem() const { return selectedItem; }
	void draw(sf::RenderWindow& window);
};

void myDelay(int opoznienie);

#endif