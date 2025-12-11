#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

class Game {
public:
    Game();
    bool run(bool shouldLoadGame = false);
    bool saveGame() const;
    bool loadGame();

    void initializeNewGame();

private:
    sf::RenderWindow window;

    Ball ball;
    Paddle paddle;
    std::vector<Brick> bricks;

    // Stan gry
    bool isPaused = false;
    bool shouldExitToMenu = false;

    int lives = 3;
    bool gameOver = false;
    const int MAX_LIVES = 3;

    sf::Clock clock;
    const float paddleSpeed = 400.f;

    sf::Font font;
    bool fontLoaded = false;

    void processEvents();
    void update(float dt);
    void render();

    void handlePaddleMovement(float dt);
    void handleBallMovement(float dt);
    void handleWallCollisions();
    void handlePaddleCollision();
    void handleBrickCollisions();

    void resetBall();
    void handleGameOver();

    void drawOverlay(const std::string& text);
    void drawHUD();
};

#endif