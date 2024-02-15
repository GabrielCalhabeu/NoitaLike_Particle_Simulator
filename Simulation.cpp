#include "Simulation.h"
#include "Sand.h"




Simulation::Simulation(SDL_Window* window, SDL_Renderer* renderer, int xResolution, int yResolution) : window(window), renderer(renderer), xResolution(xResolution), yResolution(yResolution)
{

	// Set the background color
	SDL_SetRenderDrawColor(renderer, 10, 0, 50, 255);
	SDL_RenderClear(renderer);	
	
}
void Simulation::Stop()
{
	// Cleanup and exit
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return;
}



void Simulation::Run()
{

	PhysicsSimulator phySimulator(1); //Gravity = 1
	ParticleRenderer particleRenderer(renderer);

	// SDL Event structure
	SDL_Event e;
	int x = 0, y = 0;
	int particleLimit = 1024;
	//Sand sand(xResolution / (2 * Display::largeScaling), 
	//		  yResolution / (2 * Display::largeScaling));



	std::vector<Sand*> sandVector;

	Uint32 button;
	//phySimulator.addSand(&sand);
	//particleRenderer.addSandParticle(&sand);

	

	

	if (window != nullptr && renderer != nullptr)
	{
		// Main loop
		bool running = true;
		while (running)
		{
			Uint64 start = SDL_GetPerformanceCounter();
			// Event handling
			while (SDL_PollEvent(&e))
			{
				switch (e.type) {
				case(SDL_QUIT):
					running = false; // Quit the main loop
					break;
					
				case(SDL_MOUSEBUTTONDOWN):
					

						break;
				default:
					//Stinky
					break;
				}
			};
			//Refresh renderer
			particleRenderer.drawSandParticles();
			
			
			// Draw a point at the center of the screen
			
			phySimulator.simulateSand();
			
			// Present the renderer's buffer
			SDL_RenderPresent(renderer);

			Uint64 end = SDL_GetPerformanceCounter();
			float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
			std::cout << "Current FPS: " << std::to_string(1.0f / elapsed) << std::endl;
			button = SDL_GetMouseState(&x, &y);
			if (sandVector.size() < particleLimit && SDL_BUTTON_LMASK && button)
			{

				Sand* newSand = new Sand(x / Display::largeScaling, y / Display::largeScaling);
				sandVector.push_back(newSand);
				phySimulator.addSand(newSand);
				particleRenderer.addSandParticle(newSand);
			}
			
			// Add a small delay to control the frame rate
		}


	}
	for (Sand* sand : sandVector) {
		delete sand; // Free memory allocated for each sand particle
	}
	sandVector.clear(); // Clear the vector
	Stop();
}
