#include "../include/windowHandler.h"
#include "../include/dijkstraAlgorithm.h"
#include "../include/aStarAlgorithm.h"

void handleEvent(sf::RenderWindow &window, tgui::Gui &gui, sf::Event &event, Grid &grid, Misc &misc) {
    if (event.type == sf::Event::Closed)
        window.close();
    // Detect key press O, E, S, F, R
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::E) {
            misc.drawType = Empty;
        }
        if (event.key.code == sf::Keyboard::O) {
            misc.drawType = Obstacle;
        }
        if (event.key.code == sf::Keyboard::S) {
            misc.drawType = Start;
        }
        if (event.key.code == sf::Keyboard::F) {
            misc.drawType = Finish;
        }
        if (event.key.code == sf::Keyboard::R) {
            misc.drawType = Empty;
            // Reset grid
            grid.reset();
        }
    }

    // Detect mouse button press
    if (event.type == sf::Event::MouseButtonPressed) {
        misc.mousePressed = true;
    }

    // Detect mouse button release
    if (event.type == sf::Event::MouseButtonReleased) {
        misc.mousePressed = false;
    }

    // Detect mouse click
    if (misc.mousePressed && grid.algorithmFlag() == false) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int i = mousePos.x / misc.cellSize;
        int j = mousePos.y / misc.cellSize;
        if (i >= 0 && i < misc.gridSize && j >= 0 && j < misc.gridSize) {
            if (misc.drawType == Obstacle) {
                if (grid.at(i, j).get_type() == Start) {
                    grid.setStart(std::make_pair(-1, -1));
                }
                if (grid.at(i, j).get_type() == Finish) {
                    grid.setFinish(std::make_pair(-1, -1));
                }
                grid.at(i, j).set_type(Obstacle);
            }
            if (misc.drawType == Empty) {
                if (grid.at(i, j).get_type() == Start) {
                    grid.setStart(std::make_pair(-1, -1));
                }
                if (grid.at(i, j).get_type() == Finish) {
                    grid.setFinish(std::make_pair(-1, -1));
                }
                grid.at(i, j).set_type(Empty);
            }
            if (misc.drawType == Start) {
                if (grid.at(i, j).get_type() == Finish) {
                    grid.setFinish(std::make_pair(-1, -1));
                }
                if (grid.getStart() != std::make_pair(-1, -1)) {
                    grid.at(grid.getStart()).set_type(Empty);
                }
                grid.at(i, j).set_type(Start);
                grid.setStart(std::make_pair(i, j));
            }
            if (misc.drawType == Finish) {
                if (grid.at(i, j).get_type() == Start) {
                    grid.setStart(std::make_pair(-1, -1));
                }
                if (grid.getFinish() != std::make_pair(-1, -1)) {
                    grid.at(grid.getFinish()).set_type(Empty);
                }
                grid.at(i, j).set_type(Finish);
                grid.setFinish(std::make_pair(i, j));
            }
        }
    }
    gui.handleEvent(event);
}

void updateText(Grid &grid, sf::Text &text, Misc &misc) {
    text.setString("O: Obstacle\nE: Empty\nS: Start\nF: Finish\n"
                   "R: Reset\nCurrent Mode: " +
                   temp(misc.drawType) +
                   "\n\nStart:   (" + std::to_string(grid.getStart().first) + "," + std::to_string(grid.getStart().second) + ")" +
                   "\nFinish: (" + std::to_string(grid.getFinish().first) + "," + std::to_string(grid.getFinish().second) + ")");
}

void render(sf::RenderWindow &window, Grid &grid, sf::Text &text, tgui::Gui &gui) {
    window.clear();
    grid.draw(window);
    window.draw(text);
    gui.draw();
    window.display();
}

void onStartButtonPressed(Grid *grid, PathFindingAlgorithm *&alg, const std::string &algName) {
    grid->startAlgorithm();
    if (algName == "Dijkstra") {
        alg = new DijkstraAlgorithm();
    }
    if (algName == "A*") {
        alg = new AStarAlgorithm();
    }
    alg->initialize(*grid);
}

void onStopButtonPressed(Grid *grid, PathFindingAlgorithm *alg) {
    std::cout << "Stop button pressed\n";
    grid->stopAlgorithm();
    grid->clearAlgorithm();
    delete alg;
    alg = nullptr;
}