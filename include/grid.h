#ifndef GUARD_GRID_H
#define GUARD_GRID_H

#include "cell.h"
#include "graph.h"
#include <vector>

class Grid {
private:
    std::vector<std::vector<Cell>> cells;
    int gridSize;
    std::pair<int, int> start = std::make_pair(-1, -1);
    std::pair<int, int> finish = std::make_pair(-1, -1);
    bool iterateAlgorithm = false;
public:
    int emptyCellCount = 0;
    int obstacleCellCount = 0;

    Grid(int gridSize, int cellSize);

    void draw(sf::RenderWindow &window) const;

    void reset();
    void clearAlgorithm();

    std::pair<int, int> getStart() const;
    void setStart(std::pair<int, int> x);

    std::pair<int, int> getFinish() const;
    void setFinish(std::pair<int, int> x);

    int getSize() const;

    Cell &at(int i, int j);
    Cell &at(std::pair<int, int> x);

    void countCells();

    Graph getGraph() const;

    void startAlgorithm();
    void stopAlgorithm();

    bool algorithmFlag();
};

#endif // GUARD_GRID_H