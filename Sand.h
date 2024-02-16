#ifndef SAND_H
#define SAND_H
#include <iostream>
// Define a struct for representing a color in RGBA format
enum class ParticleType {
    Sand,
    Water,
    // Add more particle types as needed
};

// Define Sand class
class Sand {
    typedef struct color_t {
        int r; int b; int g; int a;
    }color_t;
    private:
        int xPosition;
        int yPosition;
        ParticleType type;
        color_t color;

        int has_updated;
    public:
       
        
        // Constructor
        Sand(int x, int y);

        // Destructor
        ~Sand();

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

#endif // SAND_H
