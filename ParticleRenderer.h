#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <vector>
#include "SDL.h" // Assuming SDL is needed for rendering
#include "Sand.h" // Assuming Sand class is defined in Sand.h

class ParticleRenderer {
private:
    SDL_Renderer* renderer;
    std::vector<Sand*> sandParticles;

public:
    // Constructor
    ParticleRenderer(SDL_Renderer* renderer);

    // Function to add a sand particle
    void addSandParticle(Sand* sand);

    // Function to draw all sand particles
    void drawSandParticles();
    void ClearRenderer();
    void clearMemory();
};

#endif // PARTICLE_RENDERER_H
