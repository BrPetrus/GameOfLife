#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Grid.hpp"

const int WINDOW_HEIGH = 800;
const int WINDOW_WIDTH = 800;

void printIntro();

int main() {
    printIntro();

    // Create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGH), "My window", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(10);

    Grid myGrid(WINDOW_WIDTH, WINDOW_HEIGH, 20);

    bool isPaused = true;

    // Prepare fonts
    sf::Font muktaMalarRegular;
    if(!muktaMalarRegular.loadFromFile("resources/MuktaMalar-Regular.ttf")) {
        std::cerr << "[ERROR] Unable to load font!\n";
    }
    sf::Text paused;
    paused.setFont(muktaMalarRegular);
    paused.setString("Paused");

    // Run the program
    while(window.isOpen()) {
        // Events
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Space) {
                    isPaused = !isPaused;
                }
            }
        }

        // Realtime
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window is a sf::Window
            try {
                myGrid.mouseClick(localPosition);
            } catch(const char * msg) {
                std::cout << msg << "\nIgnoring...\n";
            }   
        }
         
        

        // Logic
        if(!isPaused)
            myGrid.update();

        window.clear(sf::Color::Black);
        // .... Drawing entities
        window.draw(myGrid);
        if(isPaused)
            window.draw(paused);
        window.display();
    }

    return 0;
}

void printIntro() {
    std::cout << "Conway's Game of Life\nProgrammed by Bruno Petrus (brunoxpetrus@gmail.com)\n";
    std::cout << "------------\n";
    std::cout << "Press [SPACE] to pause/unpause\n";
    std::cout << "Left click on cell to set it alive/dead\n";
    std::cout << "Have fun!\n\n\n";
}
