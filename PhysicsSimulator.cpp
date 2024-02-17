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
			particleArray[i][j]->particle = NULL;
		}
		
	}

}


// Helper function to check if a cell is empty
bool PhysicsSimulator::isCellEmpty(int x, int y) const {
	if (x < 0 || x >= width || y < 0 || y >= height)
		return false; // Out of bounds
	return (particleArray[x][y]->particle == nullptr);
}

bool PhysicsSimulator::isCellWater(int x, int y) const {
	if (x < 0 || x >= width || y < 0 || y >= height)
		return false; // Out of bounds
	if (isCellEmpty(x, y))
		return false;
	return (particleArray[x][y]->particle->getType() == ParticleType::Water);
}

// Helper function to move a particle particle to a new position
void PhysicsSimulator::moveParticle(Particle* particle, int newX, int newY) {
	if (particle == nullptr) return; // Null pointer check

	// Check if the new position is valid
	if (newX < 0 || newX >= width || newY < 0 || newY >= height) {
		// Invalid position, do nothing
		return;
	}

	// Move the particle particle to the new position
	particleArray[particle->getXPosition()][particle->getYPosition()]->particle = nullptr;
	particleArray[newX][newY]->particle = particle;
	particle->setXPosition(newX);
	particle->setYPosition(newY);
}

//This is extremely inneficient for big resolutions as it will produce less than 10 frames when at full HD
//and a couple particles are loaded in
void PhysicsSimulator::Simulate() {
	
	for (int y = height - 1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			Particle* p1 = particleArray[x][y]->particle;
			if (p1 != nullptr)
			{
			switch (particleArray[x][y]->particle->getType()) {
				case ParticleType::Sand:
					simulateSand(p1, x, y);
					break;
				case ParticleType::Water:
					// Simulate behavior for water particles
					simulateWater(p1, x, y);
					break;
					// Handle other particle types
				}
			}
		}
	}
}
void PhysicsSimulator::simulateSand(Particle* p1, int x, int y) {
	//Function for simulating sand particle
	if (p1 != nullptr) {
		// Check if this is the bottom of the screen
		if (p1->getYPosition() < height - 1) {
			// Try to go down immediately
			if (isCellEmpty(x, p1->getYPosition() + gravity)) {
				moveParticle(p1, x, p1->getYPosition() + gravity);
			}
			// Try going left
			else if (isCellEmpty(x - 1, p1->getYPosition() + gravity)) {
				moveParticle(p1, x - 1, p1->getYPosition() + gravity);
			}
			// Try going right
			else if (isCellEmpty(x + 1, p1->getYPosition() + gravity)) {
				moveParticle(p1, x + 1, p1->getYPosition() + gravity);
			}
		}
	}	
}

void PhysicsSimulator::simulateWater(Particle* p1, int x, int y) {
	//Function for simulating water particle
	if (p1 != nullptr) {
		// Check if this is the bottom of the screen
		if (p1->getYPosition() < height - 1) {
			// Try to go down immediately
			if (isCellEmpty(x, p1->getYPosition() + gravity)) {
				moveParticle(p1, x, p1->getYPosition() + gravity);
			}
			// Try going left and down
			else if (isCellEmpty(x - 1, p1->getYPosition() + gravity)) {
				moveParticle(p1, x - 1, p1->getYPosition() + gravity);
			}
			// Try going right and down
			else if (isCellEmpty(x + 1, p1->getYPosition() + gravity)) {
				moveParticle(p1, x + 1, p1->getYPosition() + gravity);
			}
			// Try going left 
			else if ( isCellEmpty(x - 1, p1->getYPosition()) ) {
				moveParticle(p1, x - 1, p1->getYPosition() );
			}
			// Try going righ
			else if ( isCellEmpty(x + 1, p1->getYPosition()) ) {
				moveParticle(p1, x + 1, p1->getYPosition());
			}
		}
	}
}


int PhysicsSimulator::getGravity() const {
	return gravity;
}
