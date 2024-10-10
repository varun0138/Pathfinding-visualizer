#include "Game.hpp"

#include <iostream>

unsigned int closeDivider(unsigned int width, unsigned int height, unsigned int size) {
    unsigned int right = size;
    while(++right) {
        if(width % right == 0 && height % right == 0) return right;
    }
    return size;
}


Game::Game() {
    init();
}

void Game::run() {
    while(m_running) {

        handleInput();
        update();
        render();
    }

}

void Game::init() {
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "", sf::Style::None);
    m_window.setPosition(sf::Vector2i(0, 0));

    if(!m_font.loadFromFile("Hack.ttf")) {
        std::cerr << "ERROR: loading fonts!!" << std::endl;
    }

    // MAZE
    m_mazeBounds = { 0.0f, 0.0f, 1400.0f, 900.f };
    m_mazeBackground.setPosition(m_mazeBounds.getPosition());
    m_mazeBackground.setSize(m_mazeBounds.getSize());
    m_mazeBackground.setFillColor(sf::Color::White);

    // SLIDER
    m_slider = std::make_unique<Slider>(sf::Vector2f(10.0f, 920.0f), sf::Vector2f(1400.0f, 20.0f));
    m_slider->setRange(MIN_VALUE, MAX_VALUE);

    m_size = closeDivider(m_mazeBounds.width, m_mazeBounds.height, std::max(MIN_VALUE, MAX_VALUE - m_slider->getCurrentValue()));
    m_rows = m_mazeBounds.height / m_size;
    m_cols = m_mazeBounds.width / m_size;

    m_maze = std::make_unique<Maze>(m_mazeBounds.getPosition(), sf::Vector2i(m_rows, m_cols), m_size);

    // BUTTONS
    m_buttons.push_back(std::make_unique<Button>(m_font, sf::Vector2f(70.0f, 970.0f), sf::Vector2f(300.0f, 80.0f), "Clear Grid"));
    m_buttons.push_back(std::make_unique<Button>(m_font, sf::Vector2f(400.0f, 970.0f), sf::Vector2f(300.0f, 80.0f), "Light Noise"));
    m_buttons.push_back(std::make_unique<Button>(m_font, sf::Vector2f(730.0f, 970.0f), sf::Vector2f(300.0f, 80.0f), "Heavy Noise"));
    m_buttons.push_back(std::make_unique<Button>(m_font, sf::Vector2f(1060.0f, 970.0f), sf::Vector2f(300.0f, 80.0f), "Clear Path"));

    m_buttons.push_back(std::make_unique<Button>(m_font, sf::Vector2f(1430.0f, 200.0f), sf::Vector2f(450.0f, 60.0f), "Breadth First Search"));
    m_buttons.push_back(std::make_unique<Button>(m_font, sf::Vector2f(1430.0f, 280.0f), sf::Vector2f(450.0f, 60.0f), "Depth First Search"));
    m_buttons.push_back(std::make_unique<Button>(m_font, sf::Vector2f(1430.0f, 360.0f), sf::Vector2f(450.0f, 60.0f), "Greedy Best First Search"));

    m_buttons.push_back(std::make_unique<Button>(m_font, sf::Vector2f(1430.0f, 600.0f), sf::Vector2f(300.0f, 55.0f), "Change Framerate"));

    m_buttons.push_back(std::make_unique<Button>(m_font, sf::Vector2f(1430.0f, 700.0f), sf::Vector2f(150.0f, 80.0f), "START"));
    m_buttons.push_back(std::make_unique<Button>(m_font, sf::Vector2f(1590.0f, 700.0f), sf::Vector2f(150.0f, 80.0f), "PAUSE"));
    m_buttons.push_back(std::make_unique<Button>(m_font, sf::Vector2f(1750.0f, 700.0f), sf::Vector2f(150.0f, 80.0f), "RESET"));

    m_buttons.push_back(std::make_unique<Button>(m_font, sf::Vector2f(1750.0f, 980.0f), sf::Vector2f(150.0f, 80.0f), "EXIT"));
    m_buttons[m_buttons.size() - 1]->setMode(LIGHT);

    // LABEL
    m_titleLabel = std::make_unique<Label>(m_font, sf::Vector2f(1430.0f, 30.0f), 60.0f, "Pathfinding");
    m_framerateLabel = std::make_unique<Label>(m_font, sf::Vector2f(1740.0f, 590.0f), 55.0f, std::to_string(m_framerate));

    // ALGORITHMS
    m_algorithms.push_back(std::make_unique<BFS>(*m_maze));
    m_algorithms.push_back(std::make_unique<DFS>(*m_maze));
    m_algorithms.push_back(std::make_unique<GBeFS>(*m_maze));
}

void Game::handleInput() {
    sf::Event event;
    while(m_window.pollEvent(event)) {}
}

void Game::update() {

    if(m_slider->isMoved() && !m_startSimulation) {
        m_size = closeDivider(m_mazeBounds.width, m_mazeBounds.height, std::max(MIN_VALUE, MAX_VALUE - m_slider->getCurrentValue()));
        m_rows = m_mazeBounds.height / m_size;
        m_cols = m_mazeBounds.width / m_size;
        m_maze->init(sf::Vector2i(m_rows, m_cols), m_size);
    }
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
    if(!m_startSimulation) {
        m_maze->update(mousePos);
    }   

    std::string clickedButton = "";
    for(unsigned int i = 0; i < m_buttons.size(); i++) {
        if(m_buttons[i]->buttonClicked((sf::Vector2f)mousePos)) {
            clickedButton = m_buttons[i]->getLabel();
            break;
        }
    }

    if(clickedButton == "Clear Grid" && !m_startSimulation) { m_maze->clearGrid(); }
    else if(clickedButton == "Light Noise" && !m_startSimulation) {
        m_maze->clearGrid();
        m_maze->addNoise(LIGHT_NOISE);
    }
    else if(clickedButton == "Heavy Noise" && !m_startSimulation) {
        m_maze->clearGrid();
        m_maze->addNoise(HEAVY_NOISE);
    }
    else if(clickedButton == "Clear Path" && !m_startSimulation)               { m_maze->clearPath(); }
    else if(clickedButton == "Breadth First Search" && !m_startSimulation)     { m_currentAlgo = 0; }
    else if(clickedButton == "Depth First Search" && !m_startSimulation)       { m_currentAlgo = 1; }
    else if(clickedButton == "Greedy Best First Search" && !m_startSimulation) { m_currentAlgo = 2; }
    else if(clickedButton == "Change Framerate" && !m_startSimulation) {
        m_framerate = (m_framerate == 30) ? 60 : 30;
        m_framerateLabel->setLabel(std::to_string(m_framerate));
        m_window.setFramerateLimit(m_framerate);
    }
    else if(clickedButton == "START" && !m_startSimulation) {
        m_startSimulation = true;
        m_pauseSimulation = false;
        m_algorithms[m_currentAlgo]->init(*m_maze);
        m_algorithms[m_currentAlgo]->setStatus(ONGOING);
    }
    else if(clickedButton == "PAUSE") {
        m_pauseSimulation = !m_pauseSimulation;
    }
    else if(clickedButton == "RESET" && (!m_startSimulation || m_pauseSimulation)) {
        m_maze->init(sf::Vector2i(m_rows, m_cols), m_size);
        m_algorithms[m_currentAlgo]->init(*m_maze);
        m_startSimulation = false;
        m_pauseSimulation = false;
    }
    else if(clickedButton == "EXIT") {
        quit();
    }

    
    if(m_algorithms[m_currentAlgo]->getStatus() == ONGOING && !m_pauseSimulation) {
        m_algorithms[m_currentAlgo]->search();
    }
    else if(m_algorithms[m_currentAlgo]->getStatus() == READY) {
        m_startSimulation = false;
    }
}

void Game::render() {

    m_window.clear(m_backgroundColor);

    m_window.draw(m_mazeBackground);
    m_maze->draw(m_window);

    m_titleLabel->draw(m_window);
    m_framerateLabel->draw(m_window);

    m_slider->draw(m_window);

    for(unsigned int i = 0; i < m_buttons.size(); i++) {
        m_buttons[i]->draw(m_window);
    }

    m_window.display();
}


void Game::quit() {
    m_running = false;
    m_window.close();
}