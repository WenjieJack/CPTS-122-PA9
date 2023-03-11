#include "ParticleManager.h"

int ParticleManager::mIdCount = 0;

ParticleManager::ParticleManager()
{
	mI = 0;
	mIdCount = 0;
	mFloorHeight = 1000;
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::AddParticle(Particle particle)
{
	particle.mId = mIdCount++;
	allParticles.push_back(particle);
}

void ParticleManager::RemoveParticle(Particle particle)
{
	allParticles.erase(std::remove(allParticles.begin(), allParticles.end(), particle), allParticles.end());
	//delete &particle;
}

void ParticleManager::setFloorHeight(float floorHeight)
{
	mFloorHeight = floorHeight;
}

void ParticleManager::update(float deltaTime)
{
	for (mI = 0; mI < allParticles.size(); mI++)
	{
		if (allParticles[mI].update(deltaTime, mFloorHeight))
		{
			RemoveParticle(allParticles[mI]);
		}
	}
}

void ParticleManager::drawAll(sf::RenderWindow& window)
{
	for (mI = 0; mI < allParticles.size(); mI++)
	{
		allParticles[mI].draw(window);
	}
}

void ParticleManager::spawnHitEffect(sf::Texture& hitEffectTExture, sf::Vector2f position)
{
	float particleDuration = 0.1f;
	sf::Vector2f particleVelocity = sf::Vector2f(0, 0);
	sf::Vector2f particleScale = sf::Vector2f(2.f, 2.f);
	float particleAngularVelocity = 0.f;
	bool shouldApplyGravity = false;
	bool ignoreCollissionWithFloor = true;
	AddParticle(
		Particle(
			hitEffectTExture,
			particleDuration,
			position,
			particleVelocity,
			particleScale,
			particleAngularVelocity,
			shouldApplyGravity,
			ignoreCollissionWithFloor
		));
}

void ParticleManager::spawnBloodEffect(sf::Texture& bloodEffectTExture, sf::Vector2f position, int amount)
{
	int count = amount <= 0 ? 10 : amount;

	float particleDuration = 5.f;
	sf::Vector2f particleScale = sf::Vector2f(0.5f, 0.5f);
	bool shouldApplyGravity = true;
	bool ignoreCollissionWithFloor = true;

	for (int i = 0; i < count; i++)
	{

		float randomNumA = (((float)(rand() % 100) / 100.f) * 10.f) - 5.f;
		float randomNumB = (((float)(rand() % 100) / 100.f) * 10.f) - 5.f;
		sf::Vector2f particleVelocity = sf::Vector2f(randomNumA, randomNumB);

		float particleAngularVelocity = (float)(rand() % 50);

		AddParticle(
			Particle(
				bloodEffectTExture,
				particleDuration,
				position,
				particleVelocity,
				particleScale,
				particleAngularVelocity,
				shouldApplyGravity,
				ignoreCollissionWithFloor
			));
	}
}
