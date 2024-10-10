#pragma once 

#include <vector>

#include "PathFinding.hpp"
#include "Maze.hpp"


class GBeFS: public PathFinding {
private:
    std::vector<sf::Vector2i> m_openlist; 
    std::vector<sf::Vector2i> m_closedlist;
    
    unsigned int evaluationIndex(const std::vector<sf::Vector2i>& list) const;
    unsigned int manhattanDistance(const sf::Vector2i& lhs, const sf::Vector2i& rhs) const;

public:
    GBeFS(Maze& maze);

    void init(Maze& maze) override;
    void search() override;
};