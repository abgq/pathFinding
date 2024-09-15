#include "../include/cell.h"

Cell::Cell(){}

Cell::Cell(int x, int y, float size, CellType type) {
    this->x = x;
    this->y = y;
    shape = sf::RectangleShape(sf::Vector2f(size, size));
    shape.setPosition(x*size, y*size);
    shape.setOutlineColor(sf::Color(128, 128, 128));
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color::White);
    this->type = type;
}

CellType Cell::get_type() const{
    return type;
}

void Cell::set_type(CellType new_type) {
    type = new_type;
    if (type == Empty) {
        shape.setFillColor(sf::Color::White);
    }
    if (type == Obstacle) {
        shape.setFillColor(sf::Color::Black);
    }
    if (type == Start) {
        shape.setFillColor(sf::Color::Green);
    }
    if (type == Finish) {
        shape.setFillColor(sf::Color::Red);
    }
    if (type == Path) {
        shape.setFillColor(sf::Color::Blue);
    }
    if(type == Visited){
        shape.setFillColor(sf::Color::Cyan);

    }
    if(type == Current) {
        shape.setFillColor(sf::Color::Magenta);
    }
}

void Cell::draw(sf::RenderWindow &window) const{
    window.draw(shape);
}