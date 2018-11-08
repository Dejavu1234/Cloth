#pragma once
#include <vector>
#include "Engine/Entity.h"
#include "Link.h"
#include "Spring.h"
class Cloth :
	public Entity
{
public:
	Cloth(int gridSize, float distance,
		const glm::vec3& position);
	~Cloth();
	void AddSpring(const class Spring& spring);
	void ClearSprings();
	//void Initialize();
	void SetStructuralSprings(float k, float b);
	void SetShearSprings(float k, float b);
	void SetBendSprings(float k, float b);
	void SetParticleMass(float mass);
	void ApplyForces();
	void ApplySpringForces();
	void Update(float dt);
	void PopulateGrid();
	void DrawCloth();
	//void SolveConstraints(
		//const std::vector<OBB>& constraints);


private:
	std::vector<GLfloat> ClothVerticies;
	std::vector<GLuint> ParticleIndicies;

	std::vector<class Spring> Springs;
	std::vector<class ParticleEnt> verts;
	std::vector<Spring> structural;
	std::vector<Spring> shear;
	std::vector<Spring> bend;
	std::vector<std::vector<ParticleEnt>> Particles;
	std::vector<GLfloat> ParticlePositions;
	float clothSize;
	glm::vec3 ClothParticlePosition;
	std::vector<Link> Links;
	GLuint program;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint texture;
	int IndiciesCount;
	std::vector<float> mHeightmap;

	std::vector<std::vector<glm::vec3>> Points;
	

};

