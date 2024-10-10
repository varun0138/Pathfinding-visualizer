#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "Maze.hpp"

#include "PathFinding.hpp"
#include "BFS.hpp"
#include "DFS.hpp"
#include "GBeFS.hpp"

#include "gui/Slider.hpp"
#include "gui/Button.hpp"
#include "gui/Label.hpp"

const unsigned int MIN_VALUE = 10;
const unsigned int MAX_VALUE = 80;

class Game {
private:
    const float m_windowWidth = 1920.0f;
    const float m_windowHeight = 1080.0f;
    unsigned int m_framerate = 60;
    sf::RenderWindow m_window;
    sf::Font m_font;

    unsigned int m_rows;
    unsigned int m_cols;
    unsigned int m_size;
    sf::FloatRect m_mazeBounds;
    std::string m_theme = "Light";

    sf::RectangleShape m_mazeBackground;

    sf::Color m_backgroundColor = { 220, 220, 220, 255 };
    bool m_running = true;
    bool m_startSimulation = false;
    bool m_pauseSimulation = false;

    std::unique_ptr<Maze> m_maze;

    std::vector<std::unique_ptr<PathFinding>> m_algorithms;
    unsigned int m_currentAlgo = 0;

    std::unique_ptr<Slider> m_slider;
    std::vector<std::unique_ptr<Button>> m_buttons;

    std::unique_ptr<Label> m_titleLabel;
    std::unique_ptr<Label> m_framerateLabel;

    void init();
    void handleInput();
    void update();
    void render();
    void quit();

public:
    Game();
    void run();
};