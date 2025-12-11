#include "Brick.h"
#include <iostream>
//3 ¿ycia (index 0), 2 ¿ycia (index 1), 1 ¿ycie (index 2), 0 ¿yæ (index 3 - przezroczysty)
const std::array<sf::Color, 4> Brick::ColorLUT = {
    sf::Color(148, 67, 240), // Fioletowy (3 uderzenia)
    sf::Color(67, 133, 240), // Niebieski (2 uderzenia)
    sf::Color(67, 240, 174), // Turkusowy (1 uderzenie)
    sf::Color::Transparent   // Przezroczysty (0 uderzeñ/zniszczony)
};

//metoda aktualizujaca kolor hitsRequired = 3 -> ColorLUT[0]; hitsRequired = 2 -> ColorLUT[1]; hitsRequired = 1 -> ColorLUT[2]; hitsRequired = 0 -> ColorLUT[3]
void Brick::updateColor() {
    if (hitsRequired >= 1 && hitsRequired <= 3) {
        setFillColor(ColorLUT[3 - hitsRequired]);
    }
    else if (hitsRequired == 0) {
        setFillColor(ColorLUT[3]);
    }
}

// tworzenia cegie³ na planszy
Brick::Brick(sf::Vector2f startPos, sf::Vector2f rozmiar)
{
    setPosition(startPos);
    setSize(rozmiar);

    // Losowa liczba ¿yæ 1–3
    hitsRequired = (std::rand() % 3) + 1;

    destroyed = false;

    updateColor();
    setOutlineThickness(1.f);
    setOutlineColor(sf::Color(0, 0, 0));
}

// Zmiana stanu po uderzeniu
void Brick::hit() {
    if (destroyed) return;

    if (hitsRequired > 0)
        hitsRequired--;

    if (hitsRequired == 0) {
        destroyed = true;
    }

    updateColor();
}