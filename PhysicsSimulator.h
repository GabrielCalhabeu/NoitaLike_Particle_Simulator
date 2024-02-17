#pragma once
#ifndef PHY_SIM_H
#define PHY_SIM_H


#include "Particle.h"
#include "Display.h"
#include "SDL.h"
#include <iostream>
#include <vector>
class PhysicsSimulator
{
private:

	int gravity;
	bool isCellEmpty(int x, int y) const;
	bool isCellWater(int x, int y) const;

	void moveParticle(Particle* particle, int newX, int newY);

	void simulateSand(Particle* p1, int x, int y);
	void simulateWater(Particle* p1, int x, int y);

	

	int width = Display::xResolution / Display::largeScaling;
	int height = Display::yResolution / Display::largeScaling;

public:
	typedef struct particle_pointer_t
	{
		Particle* particle = NULL;
	}particle_pointer_t;

	particle_pointer_t*** particleArray = new particle_pointer_t **[Display::xResolution/Display::largeScaling];
	
	PhysicsSimulator(int g);
	~PhysicsSimulator();
	void reinitializeParticleArray();

	void simulateAndDraw(SDL_Renderer *renderer);


	void Simulate();

	int getGravity() const;
	void addParticle(Particle* particle);
	
};


#endif // !PHY_SIM_H

