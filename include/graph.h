#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
public:
    Graph();
    Graph(int numVertices);
    void reset();
    void addEdge(int source, int destination, int weight);
    std::vector<int> getNeighbors(int vertex) const;
    int getWeight(int source, int destination) const;
    int getNumVertices() const;
    void displayGraph() const;
    std::vector<std::vector<int>> getAdjacencyMatrix() const;
private:
    std::vector<std::vector<int>> adjacencyMatrix;
    std::pair<int, int> start = std::make_pair(-1, -1);
    std::pair<int, int> finish = std::make_pair(-1, -1);
};

#endif // GRAPH_H
