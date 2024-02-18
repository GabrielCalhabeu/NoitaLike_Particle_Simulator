#include "ParticleRenderer.h"

// Constructor
ParticleRenderer::ParticleRenderer(SDL_Renderer* renderer) : renderer(renderer) {}

// Function to add a particle particle
void ParticleRenderer::addParticle(Particle* particle) {
    particles.push_back(particle);
}

void ParticleRenderer::clearMemory()
{
    particles.clear();
}
void ParticleRenderer::ClearRenderer()
{
    SDL_SetRenderDrawColor(renderer, 10, 0, 50, 255);
    SDL_RenderClear(renderer);
    return;
}

// Function to draw all particle particles
void ParticleRenderer::drawParticles() {
    // Set particle color
    ClearRenderer();
    if (particles.size() == 0)
    {
        return;
    }

    //SDL_Point *points = new SDL_Point;
    // Draw each particle particle
    for (const Particle *particle : particles) {
        if (particle != nullptr) {
            SDL_SetRenderDrawColor(renderer, particle->getColor().r, particle->getColor().g, particle->getColor().b, particle->getColor().a); // Example color: Yellow
            SDL_RenderDrawPoint(renderer, particle->getXPosition(), particle->getYPosition());
        }
    }


}
