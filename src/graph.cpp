#include "../include/graph.h"

Graph::Graph() {}

Graph::Graph(int numVertices) {
    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
}

void Graph::addEdge(int source, int destination, int weight) {
    adjacencyMatrix[source][destination] = weight;
}

std::vector<std::vector<int>> Graph::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}

std::vector<int> Graph::getNeighbors(int vertex) const {
    std::vector<int> neighbors;
    for (int i = 0; i < adjacencyMatrix[vertex].size(); i++) {
        if (adjacencyMatrix[vertex][i] != 0) {
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

int Graph::getWeight(int source, int destination) const {
    return adjacencyMatrix[source][destination];
}

int Graph::getNumVertices() const {
    return adjacencyMatrix.size();
}

void Graph::reset() {
    adjacencyMatrix.clear();
    start = std::make_pair(-1, -1);
    finish = std::make_pair(-1, -1);
}