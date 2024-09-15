#include "../include/dijkstraAlgorithm.h"
#include <limits>

// Constructor for Vertex
Vertex::Vertex(int i, int d) : index(i), distance(d) {}

// Overloading the comparison operator for priority queue
bool Vertex::operator<(const Vertex &other) const {
    return distance > other.distance;
}

std::pair<int, int> vertexToPixel(int v, int gridDim) {
    int x = v / gridDim;
    int y = v % gridDim;
    return std::make_pair(x, y);
}

DijkstraAlgorithm::DijkstraAlgorithm(){
    
}

void DijkstraAlgorithm::reset(){
    adj_matrix.clear();
    distance.clear();
    previous.clear();
    pq = std::priority_queue <Vertex>(); // reset it
    prev = -1;
}

void DijkstraAlgorithm::initialize(const Grid &grid){
    Graph graph = grid.getGraph();
    adj_matrix = graph.getAdjacencyMatrix();
    n = adj_matrix.size();
    gridDim = grid.getSize();
    distance = std::vector<int>(n, std::numeric_limits<int>::max());
    previous = std::vector<int>(n, -1);
    // Initialize the start vertex
    auto tempS = grid.getStart();
    auto tempF = grid.getFinish();
    start = tempS.first * gridDim + tempS.second;
    finish = tempF.first * gridDim + tempF.second;
    distance[start] = 0;
    pq.push(Vertex(start, 0));
}

bool DijkstraAlgorithm::iterate(Grid &grid) {
    if (prev != start && prev != -1) {
        Cell &temp = grid.at(vertexToPixel(prev, gridDim));
        temp.set_type(Visited);
    }
    // Dijkstra's algorithm
    if (!pq.empty()) {
        Vertex current = pq.top();
        pq.pop();

        // If the current vertex is the end vertex, break the loop
        if (current.index == finish) {
            finished = true;
            return true;
        }

        if (current.index != start) {
            Cell &temp = grid.at(vertexToPixel(current.index, gridDim));
            temp.set_type(Current);
        }

        // Explore the neighbors of the current vertex
        for (int i = 0; i < n; i++) {
            int dist = adj_matrix[current.index][i];
            if (dist != 0) {
                int newDistance = current.distance + dist;
                // If a shorter path is found, update the distance and previous vertex
                if (newDistance < distance[i]) {
                    distance[i] = newDistance;
                    previous[i] = current.index;
                    pq.push(Vertex(i, newDistance));
                }
            }
        }
        prev = current.index;
    }
    if (pq.empty()){
        finished = true;
        return true;
    }
    else
        return false;
}

std::vector<std::pair<int, int>> DijkstraAlgorithm::shortestPath() {
    // Reconstruct the shortest path
    std::vector<int> path;
    std::vector<std::pair<int, int>> pixels;
    int current = finish;
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }

    // Reverse the path to get the correct order
    std::reverse(path.begin(), path.end());
    for (auto x : path) {
        pixels.push_back(vertexToPixel(x, gridDim));
    }
    return pixels;
}

bool DijkstraAlgorithm::isFinished() const {
    return finished;
}