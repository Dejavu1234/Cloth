#pragma once
#include "ParticleEnt.h"
#include "Engine/Utils.h"
#include "Engine/Time.h"
#include "Engine/Camera.h"
class PartySystem
{
public:
	PartySystem(glm::vec3 origin, Camera* _camera, std::string texFileName);
	~PartySystem();

	void render();
	bool Comparison(ParticleEnt a, ParticleEnt b);
	std::vector<ParticleEnt> particles;
	std::vector<glm::vec3> vPosition;

private:
	Camera * camera;
	GLuint vao, vbo, texture, program;
	float nParticles;
};

