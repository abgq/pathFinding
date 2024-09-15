#ifndef GUARD_CELL_H
#define GUARD_CELL_H

#include <SFML/Graphics.hpp>
#include "misc.h"

class Cell {
private:
    sf::RectangleShape shape;
    CellType type;
    int x, y;
public:
    Cell();
    Cell(int x, int y, float size, CellType type = Empty);

    CellType get_type() const;
    void set_type(CellType new_type);
    void draw(sf::RenderWindow &window) const;
};

#endif // GUARD_CELL_H