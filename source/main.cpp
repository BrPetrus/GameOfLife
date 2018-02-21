#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Grid.hpp"

const int WINDOW_HEIGH = 800;
const int WINDOW_WIDTH = 800;

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGH), "My window");
    window.setFramerateLimit(10);

    Grid myGrid(WINDOW_WIDTH, WINDOW_HEIGH, 20);

    bool isPaused = true;

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
                    std::cout << "[Game state] Paused: " << isPaused << std::endl;
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
        window.display();
    }

    return 0;
}