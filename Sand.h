#ifndef SAND_H
#define SAND_H
#include <iostream>
// Define a struct for representing a color in RGBA format


// Define Sand class
class Sand {
    private:
        int xPosition;
        int yPosition;
        
    public:
        int const r = 255;
        int const g = 204;
        int const b = 0;
        int const a = 255;
        // Constructor
        Sand(int x, int y);

        // Destructor
        ~Sand();

        void Simulate();

        // Getter for xPosition
        int getXPosition() const;

        // Getter for yPosition
        int getYPosition() const;

        // Setters
        void setXPosition(int x);
        void setYPosition(int Y);

};

#endif // SAND_H
