#pragma once

#include <SFML/Graphics.hpp>

#include "UserInterface.hpp"

class Checkbox: public UserInterface {
private:
    sf::RectangleShape m_box;
    sf::RectangleShape m_checkbox;
    sf::Text m_text;

    sf::Vector2f m_pos = { 10.0f, 10.0f };
    float m_size = 40.0f;

    sf::Color m_colors[4] = { {0, 0, 0, 128}, {255, 255, 255, 200}, {255, 255, 255, 128}, {57, 62, 67, 255} };

    sf::Color m_fillColor    = m_colors[0];
    sf::Color m_checkColor   = m_colors[1];
    sf::Color m_outlineColor = m_colors[2];
    sf::Color m_labelColor   = m_colors[3];

    float m_thickness = 2.0f;
    std::string m_label = "";
    bool m_checked = false;
    bool m_mousePressed = false;

    void updateCheckState(const sf::Vector2f& mousePos);

public:
    Checkbox(const sf::Font& font);
    Checkbox(const sf::Font& font, const sf::Vector2f& pos, const float size, const std::string& label);

    void setLabel(const std::string& label);
    void setMode(Mode mode) override;
    void setCheck(bool check);

    bool buttonChecked() const;

    void draw(sf::RenderWindow& surface) override;
};