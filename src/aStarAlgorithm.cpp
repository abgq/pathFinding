#include "../include/aStarAlgorithm.h"
#include <float.h>
#include <cmath>

// Constructor for Vertex
VertexAStar::VertexAStar(Coords parentCoords, double f, double g, double h) : parentCoords(parentCoords), f(f), g(g), h(h) {}

// Constructor for AStarAlgorithm
AStarAlgorithm::AStarAlgorithm() {}

// Calculate the heuristic value, Manhattan distance or Euclidean distance
double AStarAlgorithm::calculateHValue(int x, int y) {
    // Euclidean distanc
    return (double)sqrt((x - finish.first) * (x - finish.first) + (y - finish.second) * (y - finish.second));

    //Manhattan distance
    //return (double)(abs(x - finish.first) + abs(y - finish.second));
}

// Reset the algorithm
void AStarAlgorithm::reset() {
    closedList.clear();
    openList.clear();
    vertexMatrix.clear();
    finished = false;
}

// Initialize the algorithm
void AStarAlgorithm::initialize(const Grid &grid) {
    // Initialize the grid
    gridDim = grid.getSize();
    closedList = std::vector<std::vector<bool>>(gridDim, std::vector<bool>(gridDim, false));
    vertexMatrix = std::vector<std::vector<VertexAStar>>(gridDim, std::vector<VertexAStar>(gridDim, VertexAStar({-1, -1}, FLT_MAX, FLT_MAX, FLT_MAX)));

    // Initialize the start and finish
    start = grid.getStart();
    finish = grid.getFinish();

    // Initialize the start vertex
    int x = start.first, y = start.second;
    vertexMatrix[x][y].f = 0.0;
    vertexMatrix[x][y].g = 0.0;
    vertexMatrix[x][y].h = 0.0;
    vertexMatrix[x][y].parentCoords = start;

    // Put the starting cell on the open list and set its 'f' as 0
    openList.insert(std::make_pair(0.0, start));

    // We set this boolean value as false as initially the destination is not reached
    finished = false;
}

// Iterate the algorithm
bool AStarAlgorithm::iterate(Grid &grid) {
    
    if (prev != start && prev != Coords(-1, -1)) {
        Cell &temp = grid.at(prev);
        temp.set_type(Visited);
    }
    
    if (openList.empty()) {
        finished = true;
        return false;
    }

    pCoords p = *openList.begin();
    openList.erase(openList.begin());

    Coords currentCoords = p.second;
    prev = currentCoords;
    int x = currentCoords.first, y = currentCoords.second;
    closedList[x][y] = true;

    // Check if the destination is reached
    if (currentCoords == finish) {
        finished = true;
        return true;
    }

    if (currentCoords != start) {
        Cell &temp = grid.at(currentCoords);
        temp.set_type(Current);
    }

    // Generate all the 4 successors of this cell
    for (int row = -1; row <= 1; row++) {
        for (int col = -1; col <= 1; col++) {
            if ((row == 0 && col == 0) || (row == -1 && col == -1) || (row == -1 && col == 1) || (row == 1 && col == -1) || (row == 1 && col == 1)) {
                continue;
            }

            int successor_x = x + col;
            int successor_y = y + row;

            // Only process this cell if this is a valid one
            if (successor_x >= 0 && successor_x < gridDim && successor_y >= 0 && successor_y < gridDim) {
                // If the successor is already on the closed list or if it is blocked, then ignore it
                if (closedList[successor_x][successor_y] == false && grid.at(successor_x, successor_y).get_type() != Obstacle) {
                    // Calculate the 'g', 'h' and 'f' of the 4 successors
                    double gNew = vertexMatrix[x][y].g + 1.0;
                    double hNew = calculateHValue(successor_x, successor_y);
                    double fNew = gNew + hNew;

                    // If it isn't on the open list, add it to the open list
                    // Make the current square the parent of this square
                    // Record the f, g, and h costs of the square cell
                    if (vertexMatrix[successor_x][successor_y].f == FLT_MAX || vertexMatrix[successor_x][successor_y].f > fNew) {
                        openList.insert(std::make_pair(fNew, std::make_pair(successor_x, successor_y)));

                        // Update the details of this cell
                        vertexMatrix[successor_x][successor_y].f = fNew;
                        vertexMatrix[successor_x][successor_y].g = gNew;
                        vertexMatrix[successor_x][successor_y].h = hNew;
                        vertexMatrix[successor_x][successor_y].parentCoords = currentCoords;
                    }
                }
            }
        }
    }

    return false;
}

// Get the path
std::vector<Coords> AStarAlgorithm::shortestPath() {
    std::vector<Coords> path;
    Coords currentCoords = finish;

    while (currentCoords != start) {
        path.push_back(currentCoords);
        currentCoords = vertexMatrix[currentCoords.first][currentCoords.second].parentCoords;
    }

    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}

// Get the finished status
bool AStarAlgorithm::isFinished() const {
    return finished;
}