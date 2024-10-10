#include "GBeFS.hpp"

#include <iostream>

GBeFS::GBeFS(Maze& maze): PathFinding(maze) {
    init(maze);
}

void GBeFS::init(Maze& maze) {
    m_status = READY;

    m_dimensions = maze.getMazeDimensions();
    m_start = maze.getStartCoords();
    m_end = maze.getEndCoords();
    m_grid = maze.getGrid();

    m_parents = std::vector<std::vector<sf::Vector2i>>(m_dimensions.x, std::vector<sf::Vector2i>(m_dimensions.y, sf::Vector2i(-1, -1)));
    m_closedlist.clear();

    m_openlist.clear();
    m_openlist.push_back(m_start);
    
    m_parents[m_start.x][m_start.y] = m_start;
}


void GBeFS::search() {
    if(m_openlist.empty()) {
        m_status = READY;
        return;
    }
    
    const unsigned int index = evaluationIndex(m_openlist);
    const sf::Vector2i parent = m_openlist[index];
    m_openlist.erase(m_openlist.begin() + index);
    m_closedlist.push_back(parent);

    if(parent == m_end) {
        findPath();
        m_status = READY;
        return;
    }

    for(const auto& [dr, dc]: m_directions) {
        const sf::Vector2i child = { parent.x + dr, parent.y + dc };
        if(m_maze.validMazeCoords(child) && m_grid[child.x][child.y] != WALL && m_parents[child.x][child.y] == sf::Vector2i(-1, -1)) {
            m_openlist.push_back(child);
            m_parents[child.x][child.y] = parent;
        }  
    }


    for(unsigned int i = 0; i < m_openlist.size(); i++) {
        m_grid[m_openlist[i].x][m_openlist[i].y] = OPEN;
    }

    for(unsigned int i = 0; i < m_closedlist.size(); i++) {
        m_grid[m_closedlist[i].x][m_closedlist[i].y] = CLOSED;
    }
    
    m_grid[m_start.x][m_start.y] = START;
    m_grid[m_end.x][m_end.y] = END;
    
    m_maze.setGrid(m_grid);
}

unsigned int GBeFS::evaluationIndex(const std::vector<sf::Vector2i>& list) const {
    unsigned int result = 0;
    unsigned int minDistance = manhattanDistance(list[0], m_end);

    for(unsigned int i = 1; i < list.size(); i++) {
        unsigned int dist = manhattanDistance(list[i], m_end);
        if(minDistance > dist) {
            minDistance = dist;
            result = i;
        }
    }
    return result;
}

unsigned int GBeFS::manhattanDistance(const sf::Vector2i& lhs, const sf::Vector2i& rhs) const {
    return std::abs(rhs.x - lhs.x) + std::abs(rhs.y - lhs.y);
}