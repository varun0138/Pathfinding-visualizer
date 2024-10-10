#include "PathFinding.hpp"

Status PathFinding::getStatus() const { return m_status; }

void PathFinding::setStatus(Status status) { m_status = status; }

void PathFinding::findPath() {
    
    sf::Vector2i current = m_end;
    while(current != m_start) {
        current = m_parents[current.x][current.y];
        m_grid[current.x][current.y] = ROUTE;
    }
    m_grid[m_start.x][m_start.y] = START;

    m_maze.setGrid(m_grid);
}