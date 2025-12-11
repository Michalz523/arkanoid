#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball(float radius = 10.f);

    void setPosition(float x, float y);
    void move(const sf::Vector2f& delta);
    void setVelocity(const sf::Vector2f& vel);
    void invertX();
    void invertY();
    void reset(float x, float y);

    const sf::Vector2f& getVelocity() const;
    const sf::CircleShape& getShape() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    float getRadius() const;

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

#endif