// DijkstraAlgorithm.h
#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include "grid.h"
#include "pathFindingAlgorithm.h"
#include <set>
#include <vector>

typedef std::pair<int, int> Coords;
typedef std::pair<double, Coords> pCoords;

std::pair<int, int> vertexToPixel(int v, int gridDim);

// Structure to represent a vertex and its distance from the source
struct VertexAStar {
    Coords parentCoords;
    double f, g, h;
    VertexAStar(Coords parentCoords, double f, double g, double h);
};

class AStarAlgorithm : public PathFindingAlgorithm {
private:
    Coords start;
    Coords finish;
    Coords prev = {-1, -1};
    int gridDim;
    std::vector<std::vector<bool>> closedList;
    std::set<pCoords> openList;
    std::vector<std::vector<VertexAStar>> vertexMatrix;
    bool finished = false;
public:
    AStarAlgorithm();
    void reset() override;
    void initialize(const Grid &grid) override;
    bool iterate(Grid &grid) override;
    bool isFinished() const override;
    std::vector<std::pair<int, int>> shortestPath() override;
    double calculateHValue(int x, int y);
};

#endif // DIJKSTRA_ALGORITHM_H