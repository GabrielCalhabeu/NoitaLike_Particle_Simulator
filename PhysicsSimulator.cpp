#include "PhysicsSimulator.h"


PhysicsSimulator::PhysicsSimulator(int g)
{
	gravity = g;
}
PhysicsSimulator::~PhysicsSimulator()
{}

void PhysicsSimulator::simulateSand() {
	if (sandList.size() == 0)
	{
		std::cout << "No sand to simulate" << std::endl;
		return;
	}
	for (Sand* sand : sandList)
	{
		if (sand->getYPosition() < Display::yResolution / Display::largeScaling - 1)
		{
			sand->setYPosition(sand->getYPosition() + gravity);
		}
	}
	
	return;
}
int PhysicsSimulator::getGravity() const {
	return gravity;
}
void PhysicsSimulator::addSand(Sand* sand)
{
	sandList.push_back(sand);
}