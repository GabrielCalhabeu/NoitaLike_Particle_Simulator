#include "Simulation.h"

//TODO: Still have to change the reference so that simulation and renderer use a singular reference to the particle vector.
//TODO: Introduce particle pooling for better performance?
//TODO: Better water logic, as it will accumulate on the left instead of evenly spread out.
//TODO: Make sand sink down in water instead of floating above it.

// Function to spawn a cluster of particles around the given position (x, y)
void Simulation::spawnParticleCluster(int x, int y, ParticleType particleType, int clusterSize, float spawnChance, std::vector<Particle*>& particleVector, PhysicsSimulator& phySimulator, ParticleRenderer& particleRenderer) {
    // Seed the random number generator with the current time
    std::srand(std::time(nullptr));

    // Define the size of the cluster (e.g., 3x3 square)
    int clusterRadius = clusterSize / 2;

    // Spawn particles in a square cluster around (x, y) with a chance of not spawning
    for (int xOffset = -clusterRadius; xOffset <= clusterRadius; ++xOffset) {
        for (int yOffset = -clusterRadius; yOffset <= clusterRadius; ++yOffset) {
            // Check if the particle should spawn based on the spawn chance
            if (rand() / static_cast<float>(RAND_MAX) < spawnChance) {
                int spawnX = x + xOffset;
                int spawnY = y + yOffset;

                // Ensure the spawn position is within the simulation bounds
                if (spawnX >= 0 && spawnX < Display::xResolution / Display::largeScaling &&
                    spawnY >= 0 && spawnY < Display::yResolution / Display::largeScaling) {
                    // Check if the spawn position is empty
                    if (phySimulator.particleArray[spawnX][spawnY]->particle == nullptr) {
                        // Spawn a new particle at the current position
                        Particle* newParticle = new Particle(spawnX, spawnY, particleType);
  
                        phySimulator.particleArray[spawnX][spawnY]->particle = newParticle;
                        particleVector.push_back(newParticle);
                        particleRenderer.addParticle(newParticle);
                    }
                }
            }
        }
    }
}

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

    
    std::string title = "Noita ";
    std::string titleFPS;
    // SDL Event structure
    SDL_Event e;
    int x = 0, y = 0;
    int particleLimit = Display::xResolution * Display::yResolution;

    // Vector to store particles
    std::vector<Particle*> particleVector;
    
    ParticleType selectedParticleType = ParticleType::Sand; //Default value :)

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
                        running = false; 
                    }
                    else if (e.key.keysym.sym == SDLK_SPACE) {
                        
                        // Clear memory and reset simulation
                        particleRenderer.clearMemory();
                        phySimulator.reinitializeParticleArray();
                        for (Particle* particle : particleVector) {
                            delete particle; // Free memory allocated for each  particle
                        }
                        particleVector.clear();
                    }
                    else if (e.key.keysym.sym == SDLK_s) {
                        // select Sand
                        selectedParticleType = ParticleType::Sand;
                    }
                    else if (e.key.keysym.sym == SDLK_w) {
                        // select Water
                        selectedParticleType = ParticleType::Water;
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
            particleRenderer.drawParticles();

            // Present the renderer's buffer
            SDL_RenderPresent(renderer);

            // Spawn new particles on mouse click

            //Hella ugly but gotta check those bounds.
            button = SDL_GetMouseState(&x, &y);
            if (particleVector.size() < particleLimit && SDL_BUTTON_LMASK && button) {
                // Check if the mouse click is within the bounds of the simulation window
                if (x <= Display::xResolution - 10 && y <= Display::yResolution - 10 && x >= 0 && y >= 0) {
                    int posX = x / Display::largeScaling;
                    int posY = y / Display::largeScaling;
                    if (posX <= Display::xResolution / Display::largeScaling && posY <= Display::yResolution / Display::largeScaling) {
                        
                        //I dont remember the point of this if statement, but without it will crash
                        if (phySimulator.particleArray[posX][posY]->particle == nullptr)
                        {
                            spawnParticleCluster(posX, posY, selectedParticleType, 16, .1, particleVector, phySimulator, particleRenderer);
                        }

                    }
                }
            }


            Uint64 end = SDL_GetPerformanceCounter(); // End performance counter

            //The point of this is to set the framerate to 60, so i get the frametime and try to make it 16.667.
            float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
            if (elapsedMS < 16.667f)
                SDL_Delay(16.667f - elapsedMS);
            else
                SDL_Delay(16.66f);


            end = SDL_GetPerformanceCounter(); // End performance counter
            float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
            titleFPS = title + (std::to_string(1.0f / elapsed)); //Use the title to display framerate as it is faster than printing it
            SDL_SetWindowTitle(window,  (titleFPS).c_str());
   
        }
    }

    // Cleanup
    for (Particle* particle : particleVector) {
        delete particle; // Free memory allocated for each particle 
    }

    particleVector.clear(); // Clear the vector
    Stop(); // Stop simulation
    
    return;
}
