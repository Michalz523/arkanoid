#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Blad: Nie udalo sie zaladowac czcionki arial.ttf!" << std::endl;
	}

	// U¿ywamy float do obliczeñ pozycji
	const float Divisor = (float)(MAX_LICZBA_POZIOMOW + 1);

	//Nowa Gra - 0
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Nowa Gra");
	menu[0].setStyle(sf::Text::Bold);
	menu[0].setPosition(sf::Vector2f(width / 3.0f, height / Divisor * 1.0f));
	menu[0].setCharacterSize(40);
	menu[0].setOutlineColor(sf::Color::Black);
	menu[0].setOutlineThickness(2.f);

	//Wczytaj Grê - 1
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Wczytaj Gre");
	menu[1].setPosition(sf::Vector2f(width / 3.0f, height / Divisor * 2.0f));
	menu[1].setCharacterSize(40);
	menu[1].setOutlineColor(sf::Color::Black);
	menu[1].setOutlineThickness(2.f);
	menu[1].scale(1.0f, 1.0f);

	//Zasady - 2
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Zasady");
	menu[2].setPosition(sf::Vector2f(width / 3.0f, height / Divisor * 3.0f));
	menu[2].setCharacterSize(40);
	menu[2].setOutlineColor(sf::Color::Black);
	menu[2].setOutlineThickness(2.f);
	menu[2].scale(1.0f, 1.0f);

	//Wyjœcie - 3
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Wyjscie");
	menu[3].setPosition(sf::Vector2f(width / 3.0f, height / Divisor * 4.0f));
	menu[3].setCharacterSize(40);
	menu[3].setOutlineColor(sf::Color::Black);
	menu[3].setOutlineThickness(2.f);
	menu[3].scale(1.0f, 1.0f);
}

// Rysowanie menu
void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
	{
		window.draw(menu[i]);
	}
}

// Przesuniecie wyboru do gory
void Menu::przesunG()
{
	menu[selectedItem].setFillColor(sf::Color::White);
	menu[selectedItem].setStyle(sf::Text::Regular);

	selectedItem--;
	if (selectedItem < 0)
		selectedItem = MAX_LICZBA_POZIOMOW - 1;

	menu[selectedItem].setFillColor(sf::Color::Cyan);
	menu[selectedItem].setStyle(sf::Text::Bold);
}

// Przesuniecie wyboru w dol
void Menu::przesunD()
{
	menu[selectedItem].setFillColor(sf::Color::White);
	menu[selectedItem].setStyle(sf::Text::Regular);

	selectedItem++;
	if (selectedItem >= MAX_LICZBA_POZIOMOW)
		selectedItem = 0;

	menu[selectedItem].setFillColor(sf::Color::Cyan);
	menu[selectedItem].setStyle(sf::Text::Bold);
}

void myDelay(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (true)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}
	}
}