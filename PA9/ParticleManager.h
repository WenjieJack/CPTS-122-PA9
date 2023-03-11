#pragma once

#include <vector>
#include "pa9.h"
#include "Particle.h"

class ParticleManager
{
private:
	static int mIdCount;
	int mI;
	std::vector<Particle> allParticles;
	float mFloorHeight;
public:
	ParticleManager();
	~ParticleManager();

	void AddParticle(Particle particle);
	void RemoveParticle(Particle particle);

	void setFloorHeight(float floorHeight);

	void update(float deltaTime);
	void drawAll(sf::RenderWindow& window);
	void spawnHitEffect(sf::Texture& hitEffectTExture, sf::Vector2f position);
	void spawnBloodEffect(sf::Texture& bloodEffectTExture, sf::Vector2f position, int amount);
};

