#pragma once 

#include <vector>
#include <deque>

#include "PathFinding.hpp"
#include "Maze.hpp"


class DFS: public PathFinding {
private:
    std::deque<sf::Vector2i>  m_openlist; 
    std::vector<sf::Vector2i> m_closedlist;
    
public:
    DFS(Maze& maze);

    void init(Maze& maze) override;
    void search() override;
};