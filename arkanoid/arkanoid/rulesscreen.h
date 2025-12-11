#ifndef RULESSCREEN_H
#define RULESSCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class RulesScreen
{
public:
    RulesScreen(float width, float height);
    int run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text textToDisplay;

    void loadResources();
    void setupText(float width, float height);
    void handleEvents(sf::Event& event, bool& isRunning);
};

#endif