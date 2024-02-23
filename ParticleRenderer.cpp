#include "ParticleRenderer.h"

// Constructor
ParticleRenderer::ParticleRenderer(SDL_Renderer* renderer) : renderer(renderer) {}

// Function to add a particle particle
void ParticleRenderer::addParticle(Particle* particle) {
    particles.push_back(particle);
    /*SDL_Point point;
    point.x = particle->getXPosition();
    point.y = particle->getYPosition();
    points.push_back(point);*/
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
    std::vector<SDL_Point> pointsSand;
    std::vector<SDL_Point> pointsWater;
    std::vector<SDL_Point> pointsDirt;
    
     for (const Particle *particle : particles) {
        if (particle != nullptr) {
            SDL_Point point;
            point.x = particle->getXPosition();
            point.y = particle->getYPosition();
            switch (particle->getType())
            {
            case  ParticleType::Sand:
                pointsSand.push_back(point);
                break;
            case  ParticleType::Water:
                pointsWater.push_back(point);
                break;
            case  ParticleType::Dirt:
                pointsDirt.push_back(point);
                break;
            default:
                break;
            }
           
            
        }
    }
    //Welcome to ugly code.
    //Couldnt figure a better way to implement vertex buffering into SDL without the use of openGL, so this will have to do.
    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    if (pointsSand.size() > 0) {
        SDL_Point* localPoints = &pointsSand[0];

        SDL_RenderDrawPoints(renderer, localPoints, pointsSand.size());
    }

    SDL_SetRenderDrawColor(renderer, 102, 204, 255, 255);
    if (pointsWater.size() > 0) {
        SDL_Point* localPoints = &pointsWater[0];
        SDL_RenderDrawPoints(renderer, localPoints, pointsWater.size());
    }

    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
    if (pointsDirt.size() > 0) {
        SDL_Point* localPoints = &pointsDirt[0];
        SDL_RenderDrawPoints(renderer, localPoints, pointsDirt.size());
    }

    // Draw each particle particle
    //for (const Particle *particle : particles) {
    //    if (particle != nullptr) {
    //        SDL_SetRenderDrawColor(renderer, particle->getColor().r, particle->getColor().g, particle->getColor().b, particle->getColor().a); // Example color: Yellow
    //        SDL_RenderDrawPoint(renderer, particle->getXPosition(), particle->getYPosition());
    //    }
    //}


}
