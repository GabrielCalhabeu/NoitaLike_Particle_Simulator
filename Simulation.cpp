#include "Simulation.h"
#include "Sand.h"

// Constructor
Simulation::Simulation(SDL_Window* window, SDL_Renderer* renderer, int xResolution, int yResolution)
    : window(window), renderer(renderer), xResolution(xResolution), yResolution(yResolution) {
    // Set the background color
    SDL_SetRenderDrawColor(renderer, 10, 0, 50, 255);
    SDL_RenderClear(renderer);
}

// Destructor
void Simulation::Stop() {
    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return;
}

// Main simulation loop
void Simulation::Run() {
    // Initialize physics simulator and particle renderer
    PhysicsSimulator phySimulator(1); // Gravity = 1
    ParticleRenderer particleRenderer(renderer);

    // SDL Event structure
    SDL_Event e;
    int x = 0, y = 0;
    int particleLimit = Display::xResolution * Display::yResolution;

    // Vector to store sand particles
    std::vector<Sand*> sandVector;

    Uint32 button;

    if (window != nullptr && renderer != nullptr) {
        // Main loop
        bool running = true;
        while (running) {
            Uint64 start = SDL_GetPerformanceCounter(); // Start performance counter

            // Event handling
            while (SDL_PollEvent(&e)) {
                switch (e.type) {
                case(SDL_QUIT):
                    running = false; // Quit the main loop
                    break;
                case(SDL_KEYDOWN):
                    // Handle key presses
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        running = false; // Quit the main loop when ESC key is pressed
                    }
                    else if (e.key.keysym.sym == SDLK_SPACE) {
                        // Clear memory and reset simulation when SPACE key is pressed
                        particleRenderer.clearMemory();
                        phySimulator.reinitializeParticleArray();
                        for (Sand* sand : sandVector) {
                            delete sand; // Free memory allocated for each sand particle
                        }
                        sandVector.clear();
                    }
                    break;
                default:
                    // Other event types not handled
                    break;
                }
            }

            // Simulate physics
            phySimulator.Simulate();

            // Refresh renderer
            particleRenderer.drawSandParticles();

            // Present the renderer's buffer
            SDL_RenderPresent(renderer);

            // Spawn new sand particles on mouse click
            button = SDL_GetMouseState(&x, &y);
            if (sandVector.size() < particleLimit && SDL_BUTTON_LMASK && button) {
                // Check if the mouse click is within the bounds of the simulation window
                if (x <= Display::xResolution - 10 && y <= Display::yResolution - 10 && x >= 0 && y >= 0) {
                    int posX = x / Display::largeScaling;
                    int posY = y / Display::largeScaling;
                    if (posX <= Display::xResolution / Display::largeScaling && posY <= Display::yResolution / Display::largeScaling) {
                        if (phySimulator.particleArray[posX][posY]->sand == nullptr) {
                            // Spawn new sand particle
                            Sand* newSand = new Sand(posX, posY);
                            newSand->setType(ParticleType::Sand);
                            phySimulator.particleArray[newSand->getXPosition()][newSand->getYPosition()]->sand = newSand;
                            sandVector.push_back(newSand);
                            particleRenderer.addSandParticle(newSand);
                        }
                    }
                }
            }

            // Control frame rate
            SDL_Delay(16.67f);

            Uint64 end = SDL_GetPerformanceCounter(); // End performance counter
            float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency(); // Calculate elapsed time
        }
    }

    // Cleanup
    for (Sand* sand : sandVector) {
        delete sand; // Free memory allocated for each sand particle
    }
    sandVector.clear(); // Clear the vector
    Stop(); // Stop simulation
}
