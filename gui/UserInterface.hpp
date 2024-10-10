#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Config.hpp>

enum Mode {
    LIGHT, DARK, SEPIA
};


inline sf::Color convertMode(const sf::Color& color, Mode mode=DARK) {
    sf::Color result = color;  

    if(mode == LIGHT) {
        result = { sf::Uint8(255 - color.r),
                   sf::Uint8(255 - color.g), 
                   sf::Uint8(255 - color.b), 
                   color.a };
    }
    else if(mode == SEPIA) {
        result = { sf::Uint8(0.393 * color.r + 0.769 * color.g + 0.189 * color.b), 
                   sf::Uint8(0.349 * color.r + 0.686 * color.g + 0.168 * color.b), 
                   sf::Uint8(0.272 * color.r + 0.534 * color.g + 0.131 * color.b), 
                   color.a };
    }         
    return result;
}


class UserInterface {
public:
    virtual void setMode(Mode mode) = 0;
    virtual void draw(sf::RenderWindow& surface) = 0;
};