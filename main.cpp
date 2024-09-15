#include "include/windowHandler.h"
#include <iostream>

int main() {
    // Parameters
    int windowWidth = 800;
    int windowHeight = 600;
    int gridSize = 20;
    int cellSize = windowHeight / gridSize;
    int algorithmCount = 2;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "ABG's Window");
    tgui::Gui gui(window); // Create a GUI object tied to the window

    Grid grid(gridSize, cellSize);
    PathFindingAlgorithm *alg;

    Misc misc;
    misc.cellSize = cellSize;
    misc.drawType = Empty;
    misc.gridSize = gridSize;
    misc.mousePressed = false;

    // Load a font
    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }
    // Create a text
    sf::Text text;
    text.setFont(font);
    text.setString("");
    text.setCharacterSize(18); // in pixels
    text.setFillColor(sf::Color::White);
    text.setPosition(gridSize * cellSize + 10, 10); // adjust as needed

    auto comboBox = tgui::ComboBox::create();
    comboBox->setPosition(gridSize * cellSize + 10, windowHeight - 30 - algorithmCount * 30);
    comboBox->setSize("180", "30");
    comboBox->addItem("A*");
    comboBox->addItem("Dijkstra");
    gui.add(comboBox);

    auto startButton = tgui::Button::create();
    startButton->setPosition(gridSize * cellSize + 10, windowHeight - 30);
    startButton->setSize("80", "20");
    startButton->setText("Start");
    gui.add(startButton, "StarButton");
    // Connect the callback function to the "Start" button's onClick signal using a lambda function
    startButton->onClick([&grid, &alg, comboBox]() {
        std::string selectedAlgorithm = comboBox->getSelectedItem().toStdString();
        onStartButtonPressed(&grid, alg, selectedAlgorithm);
        std::cout << "Start button pressed\n";
    });

    auto stopButton = tgui::Button::create();
    stopButton->setPosition(gridSize * cellSize + 110, windowHeight - 30);
    stopButton->setSize("80", "20");
    stopButton->setText("Stop");
    gui.add(stopButton, "StopButton");
    // Connect the callback function to the "Stop" button's onClick signal
    stopButton->onClick([&grid, &alg]() {
        onStopButtonPressed(&grid, alg);
    });

    bool initializeFlag = false;
    bool pathFlag = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            handleEvent(window, gui, event, grid, misc);
        }
        if (grid.algorithmFlag()) {
            std::cout << "Run...\n";
            //sf::sleep(sf::milliseconds(10));
            if (!alg->isFinished()) {
                alg->iterate(grid);
            } else {
                auto ans = alg->shortestPath();
                for (auto t : ans) {
                    if (t != grid.getStart() && t != grid.getFinish()) {
                        Cell &temp = grid.at(t);
                        temp.set_type(Path);
                    }
                }
                grid.stopAlgorithm();
            }
        }
        updateText(grid, text, misc);
        render(window, grid, text, gui);
    }
    return 0;
}