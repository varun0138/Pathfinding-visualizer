#include "Checkbox.hpp"

Checkbox::Checkbox(const sf::Font& font) {
    m_text.setFont(font);
}

Checkbox::Checkbox(const sf::Font& font, const sf::Vector2f& pos, const float size, const std::string& label)
    : m_pos(pos), m_size(size), m_label(label) {

    m_text.setFont(font);
}

void Checkbox::setLabel(const std::string& label) {
    m_label = label;
}

void Checkbox::setMode(Mode mode) {
    m_fillColor    = convertMode(m_colors[0], mode);
    m_checkColor   = convertMode(m_colors[1], mode);
    m_outlineColor = convertMode(m_colors[2], mode);
    m_labelColor   = convertMode(m_colors[3], mode);
}

void Checkbox::setCheck(bool check) {
    m_checked = check;
}

void Checkbox::updateCheckState(const sf::Vector2f& mousePos) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(!m_mousePressed) {
            if(mousePos.x >= m_pos.x && mousePos.x <= m_pos.x + m_size) {
                if(mousePos.y >= m_pos.y && mousePos.y <= m_pos.y + m_size) {
                    m_checked = !m_checked;
                    m_mousePressed = true;
                }
            }
        } 
    }
    else if(m_mousePressed) {
        m_mousePressed = false;
    }
}

bool Checkbox::buttonChecked() const {
    return m_checked;
}

void Checkbox::draw(sf::RenderWindow& surface) {
    m_box.setPosition(m_pos);
    m_box.setSize(sf::Vector2f(m_size, m_size));
    m_box.setFillColor(m_fillColor);
    m_box.setOutlineColor(m_outlineColor);
    m_box.setOutlineThickness(m_thickness);

    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(surface);
    updateCheckState(mousePos);

    surface.draw(m_box);

    const float PADDING = 3.0f;

    if(m_checked) {
        m_checkbox.setPosition(m_pos + sf::Vector2f(m_size / (PADDING * 2.0f), m_size / (PADDING * 2.0f)));
        m_checkbox.setSize(sf::Vector2f(m_size - m_size / PADDING, m_size - m_size / PADDING));
        m_checkbox.setFillColor(m_checkColor);
        surface.draw(m_checkbox);
    } 

    m_text.setString(m_label);
    m_text.setFillColor(m_labelColor);
    m_text.setCharacterSize(m_size / 2.0f);

    const sf::FloatRect bounds = m_text.getLocalBounds();
    const sf::Vector2f labelPos = { m_pos.x + m_size + m_size / PADDING, m_pos.y + m_size / 2.0f - bounds.height / 2.0f - bounds.top };
    m_text.setPosition(labelPos);

    surface.draw(m_text);
}