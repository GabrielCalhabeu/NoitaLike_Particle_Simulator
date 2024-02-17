#include "SDL.h"
#include "Simulation.h"
#include "Display.h"
int main(int argc, char* argv[])
{
	// Variable to control the main loop
	bool running = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		// Error initializing SDL
		SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return -1;
	}

	// Create a window
	SDL_Window* window = SDL_CreateWindow("Noita", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Display::xResolution, Display::yResolution, SDL_WINDOW_SHOWN);
	if (!window) {
		// Error creating window
		SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return -1;
	}

	// Create a renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		// Error creating renderer
		SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return -1;

	}
	SDL_SetHint("SDL_HINT_RENDER_SCALE_QUALITY", 0);
	SDL_RenderSetScale(renderer, Display::largeScaling, Display::largeScaling);
	
	Simulation simulation(window, renderer, Display::xResolution, Display::yResolution);
	simulation.Run();


	SDL_Quit();

	return 0;
}
