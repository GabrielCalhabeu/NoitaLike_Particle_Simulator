#pragma once
#ifndef SIMULATION_H
#define SIMULATION_H

#include "SDL.h"
#include "Display.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "Particle.h"
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
	void spawnParticleCluster(int x, int y, ParticleType particleType, int clusterSize, float spawnChance, std::vector<Particle*>& particleVector, PhysicsSimulator& phySimulator, ParticleRenderer& particleRenderer);
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif // !SIMULATION_H