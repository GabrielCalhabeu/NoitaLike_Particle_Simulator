#include "PhysicsSimulator.h"

using namespace Display;
PhysicsSimulator::PhysicsSimulator(int g)
{

	for (int i = 0; i < width; ++i) {
		particleArray[i] = new particle_pointer_t * [height];
		for (int j = 0; j < height; ++j) {
			particleArray[i][j] = new particle_pointer_t();
		}
	}
	gravity = g;
}
PhysicsSimulator::~PhysicsSimulator()
{

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			delete particleArray[i][j];
		}
		delete[] particleArray[i];
	}
	delete[] particleArray;
}
void PhysicsSimulator::reinitializeParticleArray()
{

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			particleArray[i][j]->sand = NULL;
		}
		
	}

}


// Helper function to check if a cell is empty
bool PhysicsSimulator::isCellEmpty(int x, int y) const {
	if (x < 0 || x >= width || y < 0 || y >= height)
		return false; // Out of bounds
	return (particleArray[x][y]->sand == nullptr);
}

// Helper function to move a sand particle to a new position
void PhysicsSimulator::moveSand(Sand* sand, int newX, int newY) {
	if (sand == nullptr) return; // Null pointer check

	// Check if the new position is valid
	if (newX < 0 || newX >= width || newY < 0 || newY >= height) {
		// Invalid position, do nothing
		return;
	}

	// Move the sand particle to the new position
	particleArray[sand->getXPosition()][sand->getYPosition()]->sand = nullptr;
	particleArray[newX][newY]->sand = sand;
	sand->setXPosition(newX);
	sand->setYPosition(newY);
}

void PhysicsSimulator::Simulate() {

	for (int y = height - 1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			Sand* p1 = particleArray[x][y]->sand;
			if (p1 != nullptr)
			{
			switch (particleArray[x][y]->sand->getType()) {
				case ParticleType::Sand:
					simulateSand(p1, x, y);
					break;
				case ParticleType::Water:
					// Simulate behavior for water particles
					break;
					// Handle other particle types
				}
			}
		}
	}
}
void PhysicsSimulator::simulateSand(Sand* p1, int x, int y) {
	//Function for simulating sand
	if (p1 != nullptr) {
		// Check if this is the bottom of the screen
		if (p1->getYPosition() < height - 1) {
			// Try to go down immediately
			if (isCellEmpty(x, p1->getYPosition() + gravity)) {
				moveSand(p1, x, p1->getYPosition() + gravity);
			}
			// Try going left
			else if (isCellEmpty(x - 1, p1->getYPosition() + gravity)) {
				moveSand(p1, x - 1, p1->getYPosition() + gravity);
			}
			// Try going right
			else if (isCellEmpty(x + 1, p1->getYPosition() + gravity)) {
				moveSand(p1, x + 1, p1->getYPosition() + gravity);
			}
		}
	}
		

}
int PhysicsSimulator::getGravity() const {
	return gravity;
}
void PhysicsSimulator::addSand(Sand* sand)
{
	sandList.push_back(sand);
}