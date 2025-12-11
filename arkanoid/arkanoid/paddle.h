#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle {
public:
    Paddle();

    void move(float dx);
    void setPosition(float x, float y);

    const sf::RectangleShape& getShape() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

private:
    sf::RectangleShape shape;
};

#endif