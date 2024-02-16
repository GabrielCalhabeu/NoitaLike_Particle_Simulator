#include "Sand.h"


// Constructor
Sand::Sand(int x, int y) : xPosition(x), yPosition(y){
    std::cout << "Sand object created at position (" << xPosition << ", " << yPosition << ")" << std::endl;
}

// Destructor
Sand::~Sand() {
    std::cout << "Sand object destroyed" << std::endl;
}

Sand::color_t Sand::getColor() const
{
    return color;
}

ParticleType Sand::getType() const {
    return type;
}

void Sand::setType(ParticleType newType) {
    type = newType;
}

// Getter for xPosition
int Sand::getXPosition() const {
    return xPosition;
}

// Getter for yPosition
int Sand::getYPosition() const {
    return yPosition;
}

// Setter for xPosition
void Sand::setXPosition(int x) {
    xPosition = x;
}

// Setter for yPosition
void Sand::setYPosition(int y) {
    yPosition = y;
}


