#include "Game.h"
#include <cmath>
#include <iostream>
#include <sstream>

void Game::initializeNewGame() {
    bricks.clear();

    lives = MAX_LIVES;
    gameOver = false;

    ball.reset(400.f, 300.f);
    paddle.setPosition(350.f, 550.f);

    const sf::Vector2f brickSize(70.f, 30.f);
    // Tworzenie cegieł (5 rzędów, 10 kolumn)
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 10; ++col) {
            Brick brick(
                sf::Vector2f(10 + col * 75.f, 50 + row * 35.f),
                brickSize
            );
            bricks.push_back(brick);
        }
    }
}

Game::Game()
    : window(sf::VideoMode(800, 600), "Arkanoid")
{
    window.setFramerateLimit(60);

    fontLoaded = font.loadFromFile("arial.ttf");
    if (!fontLoaded) {
        std::cerr << "Blad w Game.cpp: Nie udalo sie zaladowac czcionki arial.ttf!" << std::endl;
    }

    lives = MAX_LIVES;
    gameOver = false;
}

bool Game::run(bool shouldLoadGame) {
    shouldExitToMenu = false;
    isPaused = false;

    if (shouldLoadGame) {
        if (!loadGame()) {
            std::cerr << "Blad: Nie udalo sie wczytac gry! Rozpoczynam nowa gre." << std::endl;
            initializeNewGame();
        }
    }
    else {
        initializeNewGame();
    }

    if (!shouldLoadGame) {
        isPaused = true;
    }

    clock.restart();

    while (window.isOpen() && !shouldExitToMenu) {
        float dt = clock.restart().asSeconds();

        processEvents();

        if (!isPaused) {
            update(dt);
        }

        render();

        // Rysowanie nakładki
        if (isPaused) {
            if (gameOver) {
                drawOverlay("Porazka");
            }
            else {
                drawOverlay("PAUZA\n\nWcisnij P, by wznowic\n\nESC, by zapisac i wyjsc do menu.");
            }
        }

        window.display();
    }

    return shouldExitToMenu;
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                if (!gameOver) {
                    isPaused = !isPaused;
                    if (!isPaused) { clock.restart(); }
                }
            }

            if (event.key.code == sf::Keyboard::Escape) {
                if (isPaused && !gameOver) {
                    // Zapisz i wyjdź
                    if (saveGame()) {
                        shouldExitToMenu = true;
                        window.close();
                    }
                }
                else if (gameOver || isPaused) {
                    // W stanie GameOver lub Pauza (jeśli użytkownik nie chce zapisać)
                    shouldExitToMenu = true;
                    window.close();
                }
            }
        }
    }
}

bool Game::saveGame() const {
    std::ofstream file("savegame.txt");
    if (!file.is_open()) {
        std::cerr << "Blad: Nie mozna otworzyc pliku savegame.txt do zapisu." << std::endl;
        return false;
    }

    //Stan gry (Lives, GameOver)
    file << lives << "\n";
    file << (gameOver ? 1 : 0) << "\n";

    //Piłka (Position x, y, Velocity vx, vy)
    file << ball.getPosition().x << " " << ball.getPosition().y << " "
        << ball.getVelocity().x << " " << ball.getVelocity().y << "\n";

    //Paletka (Position x)
    file << paddle.getPosition().x << "\n";

    //Cegły (liczba, a potem x, y, hitsRequired dla każdej)
    size_t activeBricks = 0;
    for (const auto& brick : bricks) {
        if (!brick.isDestroyed()) activeBricks++;
    }
    file << activeBricks << "\n";
    for (const auto& brick : bricks) {
        if (!brick.isDestroyed()) {
            file << brick.getPosition().x << " "
                << brick.getPosition().y << " "
                << brick.getHits() << "\n";
        }
    }

    file.close();
    std::cout << "Gra zapisana pomyslnie! Powrot do menu..." << std::endl;
    return true;
}

bool Game::loadGame() {
    std::ifstream file("savegame.txt");
    if (!file.is_open()) {
        std::cerr << "Blad: Brak pliku zapisu 'savegame.txt'." << std::endl;
        return false;
    }

    float x, y, vx, vy;
    size_t brickCount;
    float pX;
    int isOverInt;

    //Stan gry
    if (!(file >> lives >> isOverInt)) return false;
    gameOver = (isOverInt == 1);

    //Piłka
    if (!(file >> x >> y >> vx >> vy)) return false;
    ball.setPosition(x, y);
    ball.setVelocity({ vx, vy });

    //Paletka 
    if (!(file >> pX)) return false;
    paddle.setPosition(pX, 550.f);

    //Cegły
    if (!(file >> brickCount)) return false;

    bricks.clear();
    const sf::Vector2f brickSize(70.f, 30.f);

    for (size_t i = 0; i < brickCount; ++i) {
        float bX, bY;
        int hits; 
        if (!(file >> bX >> bY >> hits)) return false;

        Brick loadedBrick;
        loadedBrick.setPosition(bX, bY);
        loadedBrick.setHits(hits); 

        bricks.push_back(loadedBrick);
    }

    file.close();
    std::cout << "Gra wczytana pomyslnie! Ustawiam pauze..." << std::endl;
    isPaused = true;
    return true;
}

void Game::drawOverlay(const std::string& text) {
    if (!fontLoaded) return;

    sf::Text overlayText;
    overlayText.setFont(font);
    overlayText.setString(text);
    overlayText.setCharacterSize(32);
    overlayText.setFillColor(sf::Color::White);
	overlayText.setOutlineColor(sf::Color(0, 0, 0));
	overlayText.setOutlineThickness(1);
	overlayText.setStyle(sf::Text::Bold);
	overlayText.setLineSpacing(1.2f);
	overlayText.setScale(1.f, 1.f);

    sf::FloatRect bounds = overlayText.getLocalBounds();
    overlayText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    overlayText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    window.draw(overlayText);
}

void Game::drawHUD() {
    if (!fontLoaded) return;

    sf::Text hudText;
    hudText.setFont(font);

    hudText.setString("Zycia: " + std::to_string(lives));
    hudText.setCharacterSize(20);
    hudText.setFillColor(sf::Color::White);
    hudText.setPosition(10.f, 10.f);
    hudText.setOutlineColor(sf::Color(0, 0, 0));
    hudText.setOutlineThickness(1);
    window.draw(hudText);
	hudText.setString("Klocki pozostale: " + std::to_string(bricks.size()));
    hudText.setPosition(200.f, 10.f);
	hudText.setFillColor(sf::Color::White);
	hudText.setCharacterSize(20);
	hudText.setFont(font);
	hudText.setOutlineColor(sf::Color(0, 0, 0));
	hudText.setOutlineThickness(1);
	window.draw(hudText);
}

void Game::update(float dt)
{
    if (gameOver) return;

    handlePaddleMovement(dt);
    handleBallMovement(dt);
    handleWallCollisions();
    handlePaddleCollision();
    handleBrickCollisions();

    if (bricks.empty()) {
        std::cout << "Wygrana!" << std::endl;
        initializeNewGame();
        isPaused = true;
    }
}

void Game::render() {
    window.clear(sf::Color(158, 231, 255));

    for (const auto& brick : bricks) {
        if (!brick.isDestroyed()) {
            window.draw(brick);
        }
    }

    window.draw(paddle.getShape());
    window.draw(ball.getShape());

    drawHUD();

 
}

void Game::handlePaddleMovement(float dt) {
    float dx = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        dx -= paddleSpeed * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        dx += paddleSpeed * dt;
    }

    float newX = paddle.getPosition().x + dx;
    float windowWidth = (float)window.getSize().x;
    float paddleWidth = paddle.getSize().x;

    if (newX < 0.f) {
        newX = 0.f;
    }
    else if (newX + paddleWidth > windowWidth) {
        newX = windowWidth - paddleWidth;
    }

    paddle.setPosition(newX, paddle.getPosition().y);
}

void Game::handleBallMovement(float dt) {
    ball.move(ball.getVelocity() * dt);
}

void Game::handleWallCollisions() {
    sf::FloatRect bounds = ball.getBounds();
    float windowWidth = (float)window.getSize().x;
    float windowHeight = (float)window.getSize().y;

    if (bounds.top < 0.f) {
        ball.invertY();
        ball.setPosition(ball.getPosition().x, 0.f + ball.getRadius());
    }

    if (bounds.left < 0.f) {
        ball.invertX();
        ball.setPosition(0.f + ball.getRadius(), ball.getPosition().y);
    }
    else if (bounds.left + bounds.width > windowWidth) {
        ball.invertX();
        ball.setPosition(windowWidth - bounds.width, ball.getPosition().y);
    }

    if (bounds.top > windowHeight) {
        if (!gameOver) {
            lives--;
            handleGameOver();
        }
    }
}

void Game::handlePaddleCollision() {
    sf::FloatRect ballBounds = ball.getBounds();
    sf::FloatRect paddleBounds = paddle.getBounds();

    if (ballBounds.intersects(paddleBounds) && ball.getVelocity().y > 0) {
        ball.invertY();

        ball.setPosition(ball.getPosition().x, paddleBounds.top - ballBounds.height);

        float centerBall = ballBounds.left + ballBounds.width / 2.f;
        float centerPaddle = paddleBounds.left + paddleBounds.width / 2.f;
        float relativeImpact = centerBall - centerPaddle;

        float maxDeflection = paddleBounds.width / 2.f;
        float normalizedImpact = relativeImpact / maxDeflection;

        float newVX = normalizedImpact * 300.f;

        ball.setVelocity({ newVX, -std::abs(ball.getVelocity().y) }); // Upewniamy się, że piłka leci w górę
    }
}

void Game::handleBrickCollisions() {
    sf::FloatRect ballBounds = ball.getBounds();
    bool collisionOccurred = false;

    for (size_t i = 0; i < bricks.size(); ++i) {
        if (bricks[i].isDestroyed()) continue;

        sf::FloatRect brickBounds = bricks[i].getGlobalBounds();

        if (ballBounds.intersects(brickBounds)) {
            bricks[i].hit();
            collisionOccurred = true;

            float ballLeft = ballBounds.left;
            float ballTop = ballBounds.top;
            float ballRight = ballBounds.left + ballBounds.width;
            float ballBottom = ballBounds.top + ballBounds.height;

            float brickLeft = brickBounds.left;
            float brickTop = brickBounds.top;
            float brickRight = brickBounds.left + brickBounds.width;
            float brickBottom = brickBounds.top + brickBounds.height;

           
            ball.invertY();

          
            if (ball.getVelocity().y > 0) { 
                ball.setPosition(ball.getPosition().x, brickBottom + ball.getRadius() + 0.1f);
            }
            else {
                ball.setPosition(ball.getPosition().x, brickTop - ball.getRadius() * 2.f - 0.1f);
            }

            break; 
        }
    }


    bricks.erase(std::remove_if(bricks.begin(), bricks.end(), [](const Brick& b) {
        return b.isDestroyed();
        }), bricks.end());
}

void Game::resetBall() {
    ball.reset(400.f, 300.f);
    paddle.setPosition(350.f, 550.f);
    isPaused = true;
}

void Game::handleGameOver() {
    if (lives <= 0) {
        gameOver = true;
        isPaused = true;
        std::cout << "KONIEC GRY!" << std::endl;
    }
    else {
        resetBall();
    }
}