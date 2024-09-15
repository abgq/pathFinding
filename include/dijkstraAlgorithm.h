// DijkstraAlgorithm.h
#ifndef DIJKSTRA_ALGORITHM_H
#define DIJKSTRA_ALGORITHM_H

#include "pathFindingAlgorithm.h"
#include "grid.h"
#include <queue>
#include <vector>

std::pair<int,int> vertexToPixel(int v, int gridDim);

// Structure to represent a vertex and its distance from the source
struct Vertex {
    int index;
    int distance;

    Vertex(int i, int d);

    // Overloading the comparison operator for priority queue
    bool operator<(const Vertex& other) const;
};

class DijkstraAlgorithm : public PathFindingAlgorithm{
private:
    std::vector<std::vector<int>> adj_matrix;
    int start;
    int finish;
    int n;
    int gridDim;
    std::vector<int> distance;
    std::vector<int> previous;
    std::priority_queue<Vertex> pq;
    int prev = -1;
    bool finished = false;
public:
    DijkstraAlgorithm();
    void reset() override;
    void initialize(const Grid& grid) override;
    bool iterate(Grid& grid) override;
    bool isFinished() const override;
    std::vector<std::pair<int,int>> shortestPath() override;
};

#endif // DIJKSTRA_ALGORITHM_H