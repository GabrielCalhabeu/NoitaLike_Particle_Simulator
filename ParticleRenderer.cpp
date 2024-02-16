#include "ParticleRenderer.h"

// Constructor
ParticleRenderer::ParticleRenderer(SDL_Renderer* renderer) : renderer(renderer) {}

// Function to add a sand particle
void ParticleRenderer::addSandParticle(Sand* sand) {
    sandParticles.push_back(sand);
}

void ParticleRenderer::clearMemory()
{
    sandParticles.clear();
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
        return;
    }
    SDL_SetRenderDrawColor(renderer, sandParticles[0]->getColor().r, sandParticles[0]->getColor().g, sandParticles[0]->getColor().b, 0); // Example color: Yellow

    // Draw each sand particle
    for (const Sand *sand : sandParticles) {
        if(sand != NULL)
            SDL_RenderDrawPoint(renderer, sand->getXPosition(), sand->getYPosition());
    }


}
