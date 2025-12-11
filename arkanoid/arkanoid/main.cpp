#include "Menu.h"
#include "Game.h"
#include "Rulesscreen.h"
#include <cstdlib>
#include <ctime>

// Definicja stanów
enum GameState {
    MENU,
    PLAYING,
    RULES,
    EXIT
};

int main()
{
    std::srand(std::time(nullptr));

    GameState state = MENU;
    bool shouldLoadGame = false;

    while (state != EXIT)
    {
        if (state == MENU)
        {
            sf::RenderWindow menuWindow(sf::VideoMode(800, 600), "Menu - Arkanoid");
            Menu menu(menuWindow.getSize().x, menuWindow.getSize().y);
            const sf::Color backgroundColor(50, 50, 50);

            while (menuWindow.isOpen() && state == MENU)
            {
                sf::Event event;
                while (menuWindow.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        state = EXIT;

                    if (event.type == sf::Event::KeyPressed)
                    {
                        if (event.key.code == sf::Keyboard::Up) {
                            //obs³uga klawiszy
                            myDelay(250); menu.przesunG();
                        }
                        if (event.key.code == sf::Keyboard::Down) {
                            //obs³uga klawiszy
                            myDelay(250); menu.przesunD();
                        }

                        if (event.key.code == sf::Keyboard::Enter)
                        {
                            int selected = menu.getSelectedItem();

                            switch (selected) {
                            case 0: // Nowa Gra
                                shouldLoadGame = false;
                                state = PLAYING;
                                menuWindow.close();
                                break;
                            case 1: // Wczytaj Grê
                                shouldLoadGame = true;
                                state = PLAYING;
                                menuWindow.close();
                                break;
                            case 2: // Zasady
                                state = RULES;
                                menuWindow.close();
                                break;
                            case 3: // Wyjœcie
                                state = EXIT;
                                menuWindow.close();
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }

                menuWindow.clear(backgroundColor);
                menu.draw(menuWindow);
                menuWindow.display();
            }
        }

		//Zasady gry 
        if (state == RULES)
        {
            RulesScreen rulesScreen(800, 600);
            int nextState = rulesScreen.run();
            if (nextState == 3) {
                state = EXIT;
            }
            else {
                state = MENU;
            }
        }

        //Gra
        if (state == PLAYING)
        {
            Game game;

            bool shouldReturnToMenu = game.run(shouldLoadGame);

            if (shouldReturnToMenu) {
                state = MENU;
            }
            else {
                state = EXIT;
            }

            shouldLoadGame = false;
        }
    }

    return 0;
}