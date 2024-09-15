#include "../include/grid.h"

Grid::Grid(int gridSize, int cellSize) {
    this->gridSize = gridSize;
    cells.resize(gridSize, std::vector<Cell>(gridSize));
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            cells[i][j] = Cell(i, j, cellSize);
        }
    }
}

Graph Grid::getGraph() const{
    Graph graph = Graph(gridSize * gridSize);
    // cells[x][y] : x is the column, y is the row.
    /*
        -------> x
        |
        |
        |
        |
        v
        y
    */

    // i : column, j : row on the image
    //  vertexes are ordered from top to bottom, left to right
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (cells[i][j].get_type() == Obstacle) {
                continue;
            }
            if (i > 0 && cells[i - 1][j].get_type() != Obstacle) {
                graph.addEdge(i * gridSize + j, (i - 1) * gridSize + j, 1);
            }
            if (i < gridSize - 1 && cells[i + 1][j].get_type() != Obstacle) {
                graph.addEdge(i * gridSize + j, (i + 1) * gridSize + j, 1);
            }
            if (j > 0 && cells[i][j - 1].get_type() != Obstacle) {
                graph.addEdge(i * gridSize + j, i * gridSize + j - 1, 1);
            }
            if (j < gridSize - 1 && cells[i][j + 1].get_type() != Obstacle) {
                graph.addEdge(i * gridSize + j, i * gridSize + j + 1, 1);
            }
        }
    }
    return graph;
}

void Grid::draw(sf::RenderWindow &window) const{
    for (auto &row : cells) {
        for (auto &cell : row) {
            cell.draw(window);
        }
    }
}

void Grid::countCells() {
    emptyCellCount = 0;
    obstacleCellCount = 0;
    for (auto &row : cells) {
        for (auto &cell : row) {
            if (cell.get_type() == Empty) {
                emptyCellCount++;
            }
            if (cell.get_type() == Obstacle) {
                obstacleCellCount++;
            }
        }
    }
}

void Grid::reset() {
    start = std::make_pair(-1, -1);
    finish = std::make_pair(-1, -1);
    for (auto &row : cells) {
        for (auto &cell : row) {
            cell.set_type(Empty);
        }
    }
}

void Grid::clearAlgorithm() {
    for (auto &row : cells) {
        for (auto &cell : row) {
            if (cell.get_type() == Path) {
                cell.set_type(Empty);
            }
            if (cell.get_type() == Current) {
                cell.set_type(Empty);
            }
            if (cell.get_type() == Visited) {
                cell.set_type(Empty);
            }
        }
    }
}

Cell &Grid::at(int i, int j) {
    return cells[i][j];
}

Cell &Grid::at(std::pair<int, int> x) {
    return cells[x.first][x.second];
}

std::pair<int, int> Grid::getStart() const{
    return start;
}

void Grid::setStart(std::pair<int, int> x) {
    start = x;
}

std::pair<int, int> Grid::getFinish() const{
    return finish;
}

void Grid::setFinish(std::pair<int, int> x) {
    finish = x;
}

int Grid::getSize() const{
    return gridSize;
}

void Grid::startAlgorithm() {
    iterateAlgorithm = true;
}

void Grid::stopAlgorithm() {
    iterateAlgorithm = false;
}

bool Grid::algorithmFlag() {
    return iterateAlgorithm;
}

// void Grid::dijkstra() {
//     int start = std::get<0>(this->start) * this->gridSize + std::get<1>(this->start);
//     int finish = std::get<0>(this->finish) * this->gridSize + std::get<1>(this->finish);
//     std::vector<int> answer_path = ::dijkstra(this->graph, start, finish);
//     for (int i = 0; i < answer_path.size(); i++) {
//         int x = answer_path[i] / this->gridSize;
//         int y = answer_path[i] % this->gridSize;
//         if (std::make_tuple(x, y) != this->start && std::make_tuple(x, y) != this->finish) {
//             this->at(x, y).set_type(Path);
//         }
//     }
// }