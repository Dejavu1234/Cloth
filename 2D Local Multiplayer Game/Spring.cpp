//#include "Spring.h"
//#include "ParticleEnt.h"
//
//
//Spring::Spring()
//{
//}
//
//
//Spring::~Spring()
//{
//}
//
//ParticleEnt * Spring::GetP1()
//{
//	return p1;
//}
//
//ParticleEnt * Spring::GetP2()
//{
//	return p2;
//}
//
//void Spring::SetParticles(ParticleEnt * _p1, ParticleEnt * _p2)
//{
//	p1 = _p1;
//	p2 = _p2;
//}
//
//void Spring::SetConstants(float _k, float _b)
//{
//	k = _k;
//	b = _b;
//}
//
//void Spring::ApplyForce(float dt)
//{
//	glm::vec3 relPos = p2->GetPosition() - p1->GetPosition();
//	glm::vec3 relVel = p2->GetVelocity() - p1->GetVelocity();
//
//	float x = glm::length(relPos) - restingLength;
//	float v = glm::length(relVel);
//
//	float F = (-k * x) + (-b * v);
//
//	glm::vec3 impulse =glm::normalize(relPos) * F;
//
//	p1->AddImpulse(impulse * p1->InvMass());
//	p2->AddImpulse(impulse* -1.0f * p2->InvMass());
//
//
//
//
//}
