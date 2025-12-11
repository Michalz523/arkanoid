#include "RulesScreen.h"

// Metoda ³adowanie czcionki
void RulesScreen::loadResources() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Blad w RulesScreen: Nie udalo sie zaladowac czcionki arial.ttf!" << std::endl;
    }
}
void RulesScreen::setupText(float width, float height) {

    std::string rulesText =
        "ZASADY GRY ARKANOID\n\n"
        "1. Cel: Zniszcz wszystkie kolorowe klocki, uzywajac pilki.\n"
        "2. Sterowanie: Paletka jest sterowana strzalkami LEWO/PRAWO.\n"
        "3. Zycia: Masz 3 zycia. Jesli pilka wypadnie za dolna krawedz, tracisz zycie.\n"
        "4. Klocki: Klocki maja losowo 1, 2 lub 3 punkty zycia (rozne kolory).\n"
        "5. Pauza: Wcisnij 'P', aby zatrzymac/wznowic gre.\n"
        "6. Zapis: W trakcie pauzy wcisnij 'ESC', aby zapisac i wrocic do menu.\n\n"
        "Wcisnij ESC lub ENTER, aby wrocic do Menu.";

    textToDisplay.setFont(font);
    textToDisplay.setString(rulesText);
    textToDisplay.setCharacterSize(24);
    textToDisplay.setFillColor(sf::Color::White);
	textToDisplay.setStyle(sf::Text::Bold);
	textToDisplay.setLineSpacing(1.5f);
	textToDisplay.setOutlineColor(sf::Color::Black);
	textToDisplay.setOutlineThickness(2.f);
	textToDisplay.scale(0.8f, 0.8f); 

    // Centrowanie tekstu
    sf::FloatRect bounds = textToDisplay.getLocalBounds();
    textToDisplay.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    textToDisplay.setPosition(width / 2.f, height / 2.f);
}

RulesScreen::RulesScreen(float width, float height)
    : window(sf::VideoMode(width, height), "Zasady Gry")
{
    loadResources();
    setupText(width, height);
}

void RulesScreen::handleEvents(sf::Event& event, bool& isRunning) {
    if (event.type == sf::Event::Closed) {
        isRunning = false; // Zamykamy okno zasad
    }
    if (event.type == sf::Event::KeyPressed &&
        (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape))
    {
        isRunning = false; // Powrót do menu
    }
}

// G³ówna pêtla ekranu zasad
int RulesScreen::run() {
    bool isRunning = true;
    while (window.isOpen() && isRunning) {
        sf::Event event;
        while (window.pollEvent(event)) {
            handleEvents(event, isRunning);
        }

        window.clear(sf::Color(50, 50, 50));
        window.draw(textToDisplay);
        window.display();
    }

    if (isRunning) {
        return 0; //Wracamy do MENU
    }
    else if (window.isOpen()) {
        return 0; //Esc/Enter - wracamy do MENU
    }
    else {
        return 3; //Krzy¿yk - wychodzimy z gry
    }
}