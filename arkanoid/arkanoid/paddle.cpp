#include "Paddle.h"

Paddle::Paddle() : shape(sf::Vector2f(100.f, 20.f)) {
    shape.setFillColor(sf::Color(250,170,31));
    shape.setPosition(350.f, 550.f);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color(0, 0, 0));
}

void Paddle::move(float dx) {
    shape.move(dx, 0.f);
}

void Paddle::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

const sf::RectangleShape& Paddle::getShape() const {
    return shape;
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Paddle::getPosition() const {
    return shape.getPosition();
}

sf::Vector2f Paddle::getSize() const {
    return shape.getSize();
}