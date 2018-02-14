#include "Grid.hpp"

#include <iostream>

Grid::Grid(int simW, int simH, int cellSize) : _simulationWidth(simW), _simulationHeight(simH), _cellSize(cellSize) {
    std::cout << "Constructing Grid class...\n";
    _rows = simH / cellSize;
    _col = simW / cellSize;
    _numOfCells = _rows*_col;
    //_vertices.resize(_numOfCells*2); // Two points for every quad
    genQuads();
    std::cout << "Done creating grid.\n";
}

void Grid::mouseClick(sf::Vector2i clickPos) {
    // Check if in bounds
    if(clickPos.x < 0 || clickPos.y < 0) {
        throw "[Error] Negative coordinates of mouse click.";
    } 

    // First, determine cell
    int indexRow = clickPos.y / _cellSize;
    int indexCol = clickPos.x / _cellSize;
    std::cout << "click at (col,row): (" << indexCol << "," << indexRow << ")\n";

    // Second, change colour
    int index = (indexCol*_rows + indexRow) * 4;
    for(int i = 0; i < 4; i++) {
        _vertices[index+i].color = sf::Color::Black;
    }
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Apply transforms
    states.transform *= getTransform();
    target.draw(&_vertices[0], _vertices.size(), sf::Quads, states);
}

void Grid::genQuads() {
    std::cout << "Creating quads...\n";

    for(int i = 0; i < _col; i++) {
        for(int j = 0; j < _rows; j++) {
            // Up-Left
            sf::Vector2f point1(_cellSize*i, _cellSize*j);
            sf::Vertex vertex1(point1, sf::Color::Red);
            // Up-Right
            sf::Vector2f point2(_cellSize*(i+1), _cellSize*j);
            sf::Vertex vertex2(point2, sf::Color::Green);
            // Down-Right
            sf::Vector2f point3(_cellSize*(i+1), _cellSize*(j+1));
            sf::Vertex vertex3(point3, sf::Color::Blue);
            // Down-Left
            sf::Vector2f point4(_cellSize*i, _cellSize*(j+1));
            sf::Vertex vertex4(point4, sf::Color::White);

            // FOR DEBUG PURPOSES YELLOW

            _vertices.push_back(vertex1);
            _vertices.push_back(vertex2);
            _vertices.push_back(vertex3);
            _vertices.push_back(vertex4);
        }
    }
}