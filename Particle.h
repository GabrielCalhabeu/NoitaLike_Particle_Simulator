#ifndef PARTICLE_H
#define PARTICLE_H
#include <iostream>
#include <cstdint>
// Define a struct for representing a color in RGBA format
enum class ParticleType {
    Sand,
    Water,
    Dirt,
    // Add more particle types as needed
};

// Define Particle class
class Particle {
    typedef struct color_t {
        uint8_t r; uint8_t b; uint8_t g; uint8_t a;
    }color_t;
    private:
        uint16_t xPosition;
        uint16_t yPosition;
        ParticleType type;
        color_t color;

      
    public:
       
        bool has_updated;
        // Constructor
        Particle(uint16_t x, uint16_t y, ParticleType type);

        // Destructor
        ~Particle();

        void Simulate();

        // Getter for xPosition
        int getXPosition() const;
        // Getter for yPosition
        int getYPosition() const;

        color_t getColor() const;


        ParticleType getType() const;
        void setType(ParticleType newType);
    

        // Setters
        void setXPosition(int x);
        void setYPosition(int Y);

};

#endif // PARTICLE_H
