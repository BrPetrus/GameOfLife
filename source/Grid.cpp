#include "Grid.hpp"

#include <iostream>
#include <queue>

Grid::Grid(int simW, int simH, int cellSize) : _simulationWidth(simW), _simulationHeight(simH), _cellSize(cellSize) {
    std::cout << "Constructing Grid class...\n";
    _rows = simH / cellSize;
    _col = simW / cellSize;
    _numOfCells = _rows*_col;
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

    // Second, change colour
    int index = getIndex(indexRow, indexCol);
    if(_vertices[index].color == sf::Color::Yellow)
        setColourAtIndex(indexRow, indexCol, sf::Color::Black);
    else
        setColourAtIndex(indexRow, indexCol, sf::Color::Yellow);
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
            sf::Vertex vertex1(point1, sf::Color::Black);
            // Up-Right
            sf::Vector2f point2(_cellSize*(i+1), _cellSize*j);
            sf::Vertex vertex2(point2, sf::Color::Black);
            // Down-Right
            sf::Vector2f point3(_cellSize*(i+1), _cellSize*(j+1));
            sf::Vertex vertex3(point3, sf::Color::Black);
            // Down-Left
            sf::Vector2f point4(_cellSize*i, _cellSize*(j+1));
            sf::Vertex vertex4(point4, sf::Color::Black);

            _vertices.push_back(vertex1);
            _vertices.push_back(vertex2);
            _vertices.push_back(vertex3);
            _vertices.push_back(vertex4);
        }
    }
}

void Grid::update() {

    struct change {
        int row, col;
        sf::Color colour;

        change(int row, int col, sf::Color colour) : row(row), col(col), colour(colour) {};
    };

    std::queue<change> changes;

    for(int i = 0; i < _col; i++) {
        for(int j = 0; j < _rows; j++) {
            // Alive or dead?
            int index = getIndex(j, i);

            bool isAlive = (_vertices[index].color == sf::Color::Yellow) ? true : false;
            int neighbours = checkNeighbours(j, i);

            if(isAlive && neighbours < 2) {
                changes.push(change(j, i, sf::Color::Black));
            }
            else if(isAlive && (neighbours == 2 || neighbours == 3)) {}
            else if(isAlive && neighbours > 3) {
                changes.push(change(j, i, sf::Color::Black));
            }
            else if(!isAlive && neighbours == 3) {
                changes.push(change(j, i, sf::Color::Yellow));
            }
        }
    }
    while(!changes.empty()) {
        change change = changes.front();
        setColourAtIndex(change.row, change.col, change.colour);
        changes.pop();
    }
}

int Grid::checkNeighbours(int indexRow, int indexColumn) {
    int aliveNeighbours = 0;
    for(int i = indexColumn-1; i <= indexColumn+1; i++) {
        // Bounds checking
        if(i < 0 || i > _col-1)
            continue;

        for(int j = indexRow-1; j <= indexRow+1; j++) {
            // Bounds checking
            if(j < 0 || j > _rows-1)
                continue;

            // Get index of neighbour
            int index = getIndex(j, i);
            if(_vertices[index].color == sf::Color::Yellow)
                aliveNeighbours++;
        }
    }

    // If cell we are looking at is alive, then we have to substract one
    if(_vertices[getIndex(indexRow, indexColumn)].color == sf::Color::Yellow)
        aliveNeighbours--;
    
    return aliveNeighbours;
}

int Grid::getIndex(int indexRow, int indexColumn) {
    return (indexColumn*_rows + indexRow) * 4;
}

void Grid::setColourAtIndex(int indexRow, int indexColumn, sf::Color colour) {
    int index = getIndex(indexRow, indexColumn);
    for(int i = 0; i < 4; i++) {
        _vertices[index+i].color = colour;
    }
}