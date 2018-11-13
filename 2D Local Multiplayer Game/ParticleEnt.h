#pragma once
#include "Engine\Entity.h"
#include "Engine/Dependencies/glew/glew.h"
#include "Engine/Dependencies/glm/glm.hpp"
#include "Engine/Camera.h"
#include <vector>
#include <random>
class ParticleEnt
{
public:
	ParticleEnt(glm::vec3 Origin, glm::vec3 Velocity, float ElapsedTime, float Speed, int ID,  Camera* ParticleCam);
	
	~ParticleEnt();

	glm::vec3 Position;
	void Update();
	float Random();
	Camera* CameraReference;
	float CameraDistance;

private:

	
	float fSpeed;
	glm::vec3 Velocity;
	float fFalloffDistance;
	float fFllOffTime;
	float fElapsedTime;
	float fTimeLength;
	int ID;
	
	glm::vec3 InitialPostition;
};

