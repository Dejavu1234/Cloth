#include "ParticleEnt.h"
#include "Engine/Utils.h"
#include "Engine/Time.h"


ParticleEnt::ParticleEnt()
{
}

ParticleEnt::ParticleEnt(glm::vec3 Transform)
{
	Friction = 0.95f;
	Gravity = glm::vec3(0.0f, -9.82f, 0.0f);
	Mass = 1.0f;
	Bounce = 0.7f;
}

ParticleEnt::~ParticleEnt()
{
}

void ParticleEnt::AddImpulse(const glm::vec3 & impulse)
{
	Velocity = Velocity + impulse;
}

float ParticleEnt::InvMass()
{
	if (Mass == 0.0f) {
		return 0.0f;
	}
	return 1.0f / Mass;
}

void ParticleEnt::SetMass(float m)
{
	if (m < 0) {
		m = 0;
	}
	Mass = m;
}

glm::vec3 ParticleEnt::GetVelocity()
{
	return Velocity;
}

void ParticleEnt::SetFriction(float f)
{
	if (f < 0) {
		f = 0;
	}
	Friction = f;
}

void ParticleEnt::SetPosition(const glm::vec3 & pos)
{
	Position = OldPosition = pos;
}

glm::vec3 ParticleEnt::GetPosition()
{
	return Position;
}

void ParticleEnt::SetBounce(float b)
{
	Bounce = b;
}

float ParticleEnt::GetBounce()
{
	return Bounce;
}

void ParticleEnt::SolveConstraints(std::vector<Entity>& constraints)
{
	/*int size = constraints.size();
	for (int i = 0; i < size; ++i) 
	{
		D = sqrt((x_2 - x_1)*(x_2 - x_1) + (y_2 - y_1)*(y_2 - y_1));

		if (D <= r1 + r2)
		{
			r = !r
		}
	}*/
}

void ParticleEnt::ApplyForces()
{
	Forces = Gravity * Mass;
}

void ParticleEnt::Update()
{
	/* NEW: */ glm::vec3 Acceleration = Forces * InvMass();
	Velocity = Velocity * Friction + Acceleration * static_cast<float>(Time::dTimeDelta);
	Position = Position + Velocity * static_cast<float>(Time::dTimeDelta);
}




