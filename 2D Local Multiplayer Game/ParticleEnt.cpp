#include "ParticleEnt.h"
#include "Engine/Utils.h"
#include "Engine/Time.h"
#include "Engine/Camera.h"


ParticleEnt::ParticleEnt(glm::vec3 Origin, glm::vec3 Velocity, float ElapsedTime, float Speed, int ID, Camera* ParticleCam)
{
	CameraReference = ParticleCam;
}

ParticleEnt::~ParticleEnt()
{
}


void ParticleEnt::Update()
{

	this->Velocity.y += -0.2 * .0167f;
	this->Position += Velocity;
	this->fElapsedTime -= .000167;
	this->CameraDistance = glm::distance(this->CameraReference->GetCameraPosition(), this->Position); //add
	if (this->fTimeLength <= 0.0f) {
		this->Position = this->InitialPostition;
		this->Velocity =
			glm::vec3(0.25 * cos(this->ID * .0167) + 0.25f * Random() - 0.125f,
				1.5f + 0.25f * Random() - 0.125f,
				0.25 * sin(this->ID* .0167) + 0.25f * Random() - 0.125f);
		this->fElapsedTime = Random() + 0.125;
	}

	
}

float ParticleEnt::Random()
{
	float r = (float)rand() / (double)RAND_MAX;
	return r;
}
	




