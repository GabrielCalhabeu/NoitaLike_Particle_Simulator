#include "Particle.h"


// Constructor
Particle::Particle(uint16_t x, uint16_t y, ParticleType n_type) : xPosition(x), yPosition(y){
    //std::cout << "Particle object created at position (" << xPosition << ", " << yPosition << ")" << std::endl;
    type = n_type;
    has_updated = true;
    switch (n_type)
    {
    case (ParticleType::Sand):
        color.r = 255; // Red component for sand color
        color.g = 165; // Green component for sand color
        color.b = 0;   // Blue component for sand color
        color.a = 255; // Alpha component (opacity)
        break;
    case (ParticleType::Water):
        color.r = 102;   // Red component for water color
        color.g = 204;   // Green component for water color
        color.b = 255; // Blue component for water color
        color.a = 100; // Alpha component (opacity)
        break;
    case (ParticleType::Dirt):
        color.r = 139; // Red component for water color
        color.g = 69;   // Green component for water color
        color.b = 19; // Blue component for water color
        color.a = 255; // Alpha component (opacity)
        break;
    default:
        color.r = 255; // Default color (white)
        color.g = 255;
        color.b = 255;
        color.a = 255;
        break;
    }
}



Particle::color_t Particle::getColor() const
{
    return color;
}

ParticleType Particle::getType() const {
    return type;
}

void Particle::setType(ParticleType newType) {
    type = newType;
}

// Getter for xPosition
int Particle::getXPosition() const {
    return xPosition;
}

// Getter for yPosition
int Particle::getYPosition() const {
    return yPosition;
}

// Setter for xPosition
void Particle::setXPosition(int x) {
    xPosition = x;
}

// Setter for yPosition
void Particle::setYPosition(int y) {
    yPosition = y;
}


