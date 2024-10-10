#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

#include "Maze.hpp"

enum Status {
    READY = 0,
    ONGOING = 1,
};


class PathFinding {
protected:
    Maze& m_maze;

    sf::Vector2i m_dimensions;
    sf::Vector2i m_start;
    sf::Vector2i m_end;
    Grid m_grid;

    std::vector<std::vector<sf::Vector2i>> m_parents;
    const std::vector<sf::Vector2i> m_directions = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

    Status m_status;

public:
    PathFinding(Maze& maze): m_maze(maze) {}

    virtual Status getStatus() const;
    virtual void setStatus(Status status);
    virtual void findPath();
    
    virtual void init(Maze& maze) = 0;
    virtual void search() = 0;
};