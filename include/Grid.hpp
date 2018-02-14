#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Grid : public sf::Drawable, public sf::Transformable {
public:
    Grid(int simW, int simH, int cellSize);
    void mouseClick(sf::Vector2i clickPos);
private:
    // Dimensions
    int _simulationWidth;
    int _simulationHeight;
    int _cellSize;

    // Grid
    int _rows;
    int _col;
    int _numOfCells;

    // Holds the vertices of quad
    std::vector<sf::Vertex> _vertices;

    // Draws the grid 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Gen quads
    void genQuads();
};

#endif