#ifndef GUARD_MISC_H
#define GUARD_MISC_H

#include <string>

enum CellType {
    Empty,
    Obstacle,
    Start,
    Finish,
    Current,
    Visited,
    Path
};

struct Misc {
    CellType drawType;
    float cellSize;
    int gridSize;
    bool mousePressed = false;
};

std::string temp(const CellType &type);

#endif // GUARD_MISC_H