#include "ParticleRenderer.h"

// Constructor
ParticleRenderer::ParticleRenderer(SDL_Renderer* renderer) : renderer(renderer) {}

// Function to add a sand particle
void ParticleRenderer::addSandParticle(Sand* sand) {
    sandParticles.push_back(sand);
}


void ParticleRenderer::ClearRenderer()
{
    SDL_SetRenderDrawColor(renderer, 10, 0, 50, 255);
    SDL_RenderClear(renderer);
    return;
}

// Function to draw all sand particles
void ParticleRenderer::drawSandParticles() {
    // Set sand color
    ClearRenderer();
    if (sandParticles.size() == 0)
    {
        std::cout << "No particles to draw" << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, sandParticles[0]->r, sandParticles[0]->g, sandParticles[0]->b, 0); // Example color: Yellow

    // Draw each sand particle
    for (const Sand *sand : sandParticles) {
        SDL_RenderDrawPoint(renderer, sand->getXPosition(), sand->getYPosition());
    }


}
