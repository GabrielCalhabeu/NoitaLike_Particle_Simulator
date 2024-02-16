#pragma once
#ifndef PHY_SIM_H
#define PHY_SIM_H


#include "Sand.h"
#include "Display.h"
#include "SDL.h"
#include <iostream>
#include <vector>
class PhysicsSimulator
{
private:

	int gravity;

	std::vector<Sand*> sandList;
	bool isCellEmpty(int x, int y) const;
	void moveSand(Sand* sand, int newX, int newY);

	int width = Display::xResolution / Display::largeScaling;
	int height = Display::yResolution / Display::largeScaling;

public:
	typedef struct particle_pointer_t
	{
		Sand* sand = NULL;
	}particle_pointer_t;

	particle_pointer_t*** particleArray = new particle_pointer_t **[Display::xResolution/Display::largeScaling];
	
	PhysicsSimulator(int g);
	~PhysicsSimulator();
	void reinitializeParticleArray();

	void simulateAndDraw(SDL_Renderer *renderer);
	void simulateSand(Sand* p1, int x, int y);
	void Simulate();

	int getGravity() const;
	void addSand(Sand* sand);
	
};


#endif // !PHY_SIM_H

