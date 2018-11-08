#pragma once
class Spring
{
public:
	Spring();
	~Spring();
	Spring(float _k, float _b, float len)
		: k(_k), b(_b), restingLength(len) { }
	class ParticleEnt* GetP1();
	class ParticleEnt* GetP2();
	void SetParticles(ParticleEnt* _p1, ParticleEnt* _p2);
	void SetConstants(float _k, float _b);
	void ApplyForce(float dt);
private:
	class ParticleEnt* p1;
	class ParticleEnt* p2;
	// higher k = stiff spring, lower k = loose spring
	float k; // [-n to 0]
	float b; // [0 to 1], default to 0
	float restingLength;
};

