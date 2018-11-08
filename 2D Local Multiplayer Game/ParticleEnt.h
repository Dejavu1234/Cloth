#pragma once
#include "Engine\Entity.h"
#include "Engine/Dependencies/glew/glew.h"
#include "Engine/Dependencies/glm/glm.hpp"
#include <vector>
class ParticleEnt
{
public:
	ParticleEnt();
	ParticleEnt(glm::vec3 Transform);
	~ParticleEnt();

	void AddImpulse(const glm::vec3& impulse);
	float InvMass();
	void SetMass(float m);
	glm::vec3 GetVelocity();
	void SetFriction(float f);
	void SetPosition(const glm::vec3& pos);
	glm::vec3 GetPosition();
	void SetBounce(float b);
	float GetBounce();
	void SolveConstraints(std::vector<Entity>& constraints);
	void ApplyForces();
	int VerticiesArrayId;
	void Update();
	

private:
	;
	glm::vec3 Velocity;
	glm::vec3 Forces;
	float Mass;
	float Bounce;
	float Friction;
	glm::vec3 Gravity;
	glm::vec3 OldPosition;
	glm::vec3 Position;
	int VerticiesArrayID;
};

