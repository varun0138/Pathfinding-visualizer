#include "Maze.hpp"

#include <iostream>
#include <stdexcept>

Maze::Maze()
    :Maze(sf::Vector2f(0.0f, 0.0f), sf::Vector2i(20, 15), 40.0f) {}

Maze::Maze(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const float size) 
    : m_pos(pos), m_dimensions(dimensions), m_size(size) {

    init(dimensions, size);
}

void Maze::init(const sf::Vector2i& dimensions, const float size) {
    m_dimensions = dimensions;
    m_size = size;
    m_grid = Grid(m_dimensions.x, std::vector<State>(m_dimensions.y, EMPTY));
    m_start = sf::Vector2i(0, 0);
    m_end = sf::Vector2i(dimensions.x - 1, m_dimensions.y - 1);

    m_grid[m_start.x][m_start.y] = START;
    m_grid[m_end.x][m_end.y] = END;
}

sf::Vector2i Maze::getMazeCoords(const sf::Vector2i& pos) const {
    return sf::Vector2i(pos.y / m_size, pos.x / m_size);
}

sf::Vector2f Maze::getPixelCoords(const sf::Vector2i& dimensions) const {
    return sf::Vector2f(dimensions.y * m_size, dimensions.x * m_size);
}

bool Maze::validMazeCoords(const sf::Vector2i& coords) const {
    if(coords.x >= 0 && coords.x < m_dimensions.x) {
        if(coords.y >= 0 && coords.y < m_dimensions.y) {
            return true;
        }
    }
    return false;
}

State Maze::getMazeState(const sf::Vector2i& coords) const {
    if(validMazeCoords(coords)) {
        return m_grid[coords.x][coords.y];
    }
    throw std::runtime_error("Given Coordinates are out of bounds!!");
}

void Maze::setStartCoords(const sf::Vector2i& coords) {
    if(coords != m_end && m_grid[coords.x][coords.y] == EMPTY) {
        m_grid[m_start.x][m_start.y] = EMPTY;
        m_start = coords;
        m_grid[m_start.x][m_start.y] = START;
    }
}

void Maze::setEndCoords(const sf::Vector2i& coords) {
    if(coords != m_start && m_grid[coords.x][coords.y] == EMPTY) {
        m_grid[m_end.x][m_end.y] = EMPTY;
        m_end = coords;
        m_grid[m_end.x][m_end.y] = END;
    } 
}

void Maze::setMazeState(const sf::Vector2i& coords, State state) {
    if(validMazeCoords(coords)) {
        m_grid[coords.x][coords.y] = state;
    }
    throw std::runtime_error("Given Coordinates are out of bounds!!");
}

void Maze::setGrid(const Grid& grid) {
    m_grid = grid;
}

void Maze::clearGrid() {
    for(int x = 0; x < m_dimensions.x; x++) {
        for(int y = 0; y < m_dimensions.y; y++) {
            if(m_grid[x][y] == START || m_grid[x][y] == END) { continue; }
            m_grid[x][y] = EMPTY;
        }
    }
}

void Maze::clearPath() {
    for(int x = 0; x < m_dimensions.x; x++) {
        for(int y = 0; y < m_dimensions.y; y++) {
            if(m_grid[x][y] == START || m_grid[x][y] == END || m_grid[x][y] == WALL) { continue; }
            m_grid[x][y] = EMPTY;
        }
    }
}

void Maze::update(const sf::Vector2i& mousePos) {
    sf::Vector2i coords = getMazeCoords(mousePos);
    bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if(validMazeCoords(coords)) {
        if(mousePressed && !m_wasMousePressed) {
            if(getMazeState(coords) == START) {
                m_startDrag = true;
            }
            else if(getMazeState(coords) == END) {
                m_endDrag = true;
            }
            else if(getMazeState(coords) == EMPTY) {
                m_wallDrag = true;
            }
        }
        else if(!mousePressed && m_wasMousePressed) {
            if(m_startDrag && getMazeState(coords) == EMPTY) {
                setStartCoords(coords);
            }
            else if(m_endDrag && getMazeState(coords) == EMPTY) {
                setEndCoords(coords);
            }

            m_startDrag = false;
            m_endDrag = false;
            m_wallDrag = false;
        }
        m_wasMousePressed = mousePressed;
    }
}

void Maze::draw(sf::RenderWindow& surface) {
    for(int x = 0; x < m_dimensions.x; x++) {
        for(int y = 0; y < m_dimensions.y; y++) {
            m_cell.setPosition(sf::Vector2f(y * m_size, x * m_size));
            m_cell.setSize(sf::Vector2f(m_size - 1, m_size - 1));
            m_cell.setFillColor(m_colors[m_grid[x][y]]);
            m_cell.setOutlineThickness(0.0f);
            surface.draw(m_cell);
        }
    }

    for(int x = 0; x < m_dimensions.x; x++) {
        for(int y = 0; y < m_dimensions.y; y++) {
            if(m_grid[x][y] == START || m_grid[x][y] == END || m_grid[x][y] == OPEN) {
                m_cell.setPosition(sf::Vector2f(y * m_size, x * m_size));
                m_cell.setSize(sf::Vector2f(m_size - 1, m_size - 1));
                m_cell.setFillColor(m_colors[m_grid[x][y]]);
                m_cell.setOutlineColor(sf::Color::Black);
                m_cell.setOutlineThickness(3.0f);
                surface.draw(m_cell);
            } 
        }
    }

    sf::Vector2i mousePos = sf::Mouse::getPosition(surface);
    if(m_startDrag || m_endDrag) {
        sf::Vector2i coords = getMazeCoords(mousePos);
        if(validMazeCoords(coords)) {
            m_fadedCell.setPosition(getPixelCoords(coords) + m_pos);
            m_fadedCell.setSize(sf::Vector2f(m_size - 1, m_size - 1));

            m_fadedCell.setFillColor(m_startDrag ? sf::Color(0, 255, 0, 128) : sf::Color(255, 0, 0, 128));
            surface.draw(m_fadedCell);
        }
    }
    else if(m_wallDrag) {
        sf::Vector2i coords = getMazeCoords(mousePos);
        if(validMazeCoords(coords) && getMazeState(coords) != START && getMazeState(coords) != END) {
            m_grid[coords.x][coords.y] = WALL;
        }
    }
}

void Maze::DEBUG() const {
    for(int x = 0; x < m_dimensions.x; x++) {
        for(int y = 0; y < m_dimensions.y; y++) {

            std::cout << x << " " << y << " " << y * m_size << " " << x * m_size << std::endl;
        }
    }
}


Grid Maze::getGrid() const {
    return m_grid;
}

sf::Vector2i Maze::getMazeDimensions() const {
    return m_dimensions;
}

sf::Vector2i Maze::getStartCoords() const {
    return m_start;
}

sf::Vector2i Maze::getEndCoords() const {
    return m_end;
}

void Maze::addNoise(NoiseIntensity intensity) {
    int numWallsToAdd = 0;

    // Determine number of walls to add based on intensity
    switch (intensity) {
        case LIGHT_NOISE:
            numWallsToAdd = (m_dimensions.x * m_dimensions.y) / 10; // Add walls for 10% of cells
            break;
        case HEAVY_NOISE:
            numWallsToAdd = (m_dimensions.x * m_dimensions.y) / 5; // Add walls for 20% of cells
            break;
    }

    for (int i = 0; i < numWallsToAdd; ++i) {
        int row = m_random.randint(0, m_dimensions.x - 1); // Assuming getRandomInt is defined in Random
        int col = m_random.randint(0, m_dimensions.y - 1);

        // Only place a wall if it's not the start or end point
        if (m_grid[row][col] == EMPTY) {
            m_grid[row][col] = WALL;
        }
    }
}
