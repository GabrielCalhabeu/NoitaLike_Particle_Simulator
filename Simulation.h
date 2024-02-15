#pragma once
#ifndef SIMULATION_H
#define SIMULATION_H

#include "SDL.h"
#include "Display.h"
#include "PhysicsSimulator.h"
#include "ParticleRenderer.h"
#include <vector>
#include<string>

class Simulation
{
public:
	Simulation(SDL_Window* window, SDL_Renderer* renderer, int xResolution, int yResolution);
	void Run();
	void Stop();
	int yResolution;
	int xResolution;

private:
	void ClearRenderer(SDL_Renderer* renderer);
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif // !SIMULATION_H