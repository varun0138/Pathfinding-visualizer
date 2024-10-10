#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Random.hpp"

enum State: unsigned int {
    EMPTY = 0,
    WALL = 1,
    START = 2,
    END = 3,
    ROUTE = 4,
    OPEN = 5,
    CLOSED = 6
};

enum NoiseIntensity {
    LIGHT_NOISE,
    HEAVY_NOISE
};

typedef std::vector<std::vector<State>> Grid;


class Maze {
private:
    sf::Vector2f m_pos; // position of the maze on the screen

    sf::Vector2i m_dimensions; // rows and columns
    sf::Vector2i m_start; // starting row and col
    sf::Vector2i m_end; // ending row and col
    float m_size; // size of the cell

    Grid m_grid;
    sf::Color m_colors[7] = {
        {200, 200, 180, 255},
        {57, 62, 67, 255},
        {50, 235, 40, 255},
        {255, 1, 1, 255},
        {200 ,0, 255, 255},
        {195, 220, 240, 255},
        {161, 161, 145, 255}
    };

    sf::RectangleShape m_cell;
    sf::RectangleShape m_fadedCell;

    bool m_startDrag = false;
    bool m_endDrag = false;
    bool m_wallDrag = false;
    sf::Vector2i m_prevMousePos;
    bool m_wasMousePressed = false;

    Random m_random;

public:
    Maze();
    Maze(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const float size);

    void init(const sf::Vector2i& dimensions, const float size);

    sf::Vector2i getMazeCoords(const sf::Vector2i& pos) const;
    sf::Vector2f getPixelCoords(const sf::Vector2i& coords) const;
    bool validMazeCoords(const sf::Vector2i& coords) const;
    State getMazeState(const sf::Vector2i& coords) const;

    Grid getGrid() const;
    sf::Vector2i getMazeDimensions() const;
    sf::Vector2i getStartCoords() const;
    sf::Vector2i getEndCoords() const;

    void setStartCoords(const sf::Vector2i& coords);
    void setEndCoords(const sf::Vector2i& coords);
    void setMazeState(const sf::Vector2i& coords, State state);
    void setGrid(const Grid& grid);

    void clearGrid();
    void clearPath();
    void update(const sf::Vector2i& mousePos);
    void draw(sf::RenderWindow& surface);

    void DEBUG() const;
    void addNoise(NoiseIntensity intensity);
};