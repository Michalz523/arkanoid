#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>
#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Brick : public sf::RectangleShape {
private:
    int hitsRequired;
    bool destroyed;
    static const std::array<sf::Color, 4> ColorLUT;


    void updateColor();

public:
    // konstruktor domyślny dla wczytywania (loadGame)
    Brick() : hitsRequired(1), destroyed(false) {
        setSize(sf::Vector2f(70.f, 30.f));
        setOutlineThickness(1.f);
        setOutlineColor(sf::Color(0, 0, 0));
        updateColor();
    }

    // tworzenie cegieł na planszy (new game)
    Brick(sf::Vector2f startPos, sf::Vector2f rozmiar);

    void hit();
    bool isDestroyed() const { return destroyed; }
    int getHits() const { return hitsRequired; }

    // metody do zapisu/odczytu
    void setHits(int h) { hitsRequired = h; updateColor(); }
    void setDestroyed(bool d) { destroyed = d; if (d) hitsRequired = 0; updateColor(); }
};

#endif