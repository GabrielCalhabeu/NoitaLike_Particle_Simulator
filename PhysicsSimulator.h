#pragma once
#ifndef PHY_SIM_H
#define PHY_SIM_H


#include "Sand.h"
#include "Display.h"
#include <iostream>
#include <vector>
class PhysicsSimulator
{
private:
	int gravity;
	std::vector<Sand*> sandList;
public:


	PhysicsSimulator(int g);
	~PhysicsSimulator();

	void simulateSand();

	int getGravity() const;
	void addSand(Sand* sand);
	
};


#endif // !PHY_SIM_H

