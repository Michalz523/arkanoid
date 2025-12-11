#include "Ball.h"

Ball::Ball(float radius) : shape(radius), velocity(200.f, -200.f) {
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(400.f, 300.f);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color(0, 0, 0));
}

void Ball::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

void Ball::move(const sf::Vector2f& delta) {
    shape.move(delta);
}

void Ball::setVelocity(const sf::Vector2f& vel) {
    velocity = vel;
}

void Ball::invertX() {
    velocity.x = -velocity.x;
}

void Ball::invertY() {
    velocity.y = -velocity.y;
}

void Ball::reset(float x, float y) {
    shape.setPosition(x, y);
    velocity = sf::Vector2f(200.f, -200.f); // Pocz¹tkowa prêdkoœæ
}

const sf::Vector2f& Ball::getVelocity() const {
    return velocity;
}

const sf::CircleShape& Ball::getShape() const {
    return shape;
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}

float Ball::getRadius() const {
    return shape.getRadius();
}