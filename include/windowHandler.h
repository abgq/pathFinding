#ifndef GUARD_WINDOWHANDLER_H
#define GUARD_WINDOWHANDLER_H

#include "grid.h"
#include "misc.h"
#include "pathFindingAlgorithm.h"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

void handleEvent(sf::RenderWindow &window, tgui::Gui &gui, sf::Event &event, Grid &grid, Misc &misc);
void updateText(Grid &grid, sf::Text &text, Misc &misc);
void render(sf::RenderWindow &window, Grid &grid, sf::Text &text, tgui::Gui &gui);
void onStartButtonPressed(Grid *grid, PathFindingAlgorithm *&alg, const std::string &algName);
void onStopButtonPressed(Grid *grid, PathFindingAlgorithm *alg);

#endif // GUARD_WINDOWHANDLER_H