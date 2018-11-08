#include "Cloth.h"
//#include "Spring.h"
#include "Engine/Time.h"
#include"Engine/Time.h"
#include "ParticleEnt.h"
#include "Engine/Utils.h"
#include "Engine/Shader.h"
#include "Engine/Camera.h"
#include "Link.h"

Cloth::Cloth(int gridSize, float distance, const glm::vec3 & position)
	: Entity({ { 0,0,0 },{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER)
{

	
	float k = -1.0f;
	float b = 0.0f;
	clothSize = gridSize;
	verts.clear();
	structural.clear();
	shear.clear();
	bend.clear();
	verts.resize(gridSize * gridSize);
	float hs = (float)(gridSize - 1) * 0.5f;

	if (gridSize< 3) { //Minimum of 3 needed for a stable simulation
		gridSize = 3;
	}

	for (int x = 0; x <gridSize; ++x) 
	{
		for (int z = 0; z < gridSize; ++z) 
		{
			int i = z * gridSize + x;

			float x_pos = ((float)x + position.x
				- hs) * distance;

			float z_pos = ((float)z + position.z
				- hs) * distance;

			verts[i].SetPosition(glm::vec3(x_pos, position.y, z_pos));
			verts[i].SetMass(1.0f);
			verts[i].SetBounce(0.0f);
			verts[i].SetFriction(0.9f);
		}
	}
	for (int x = 0; x <gridSize; ++x) 
	{
		for (int z = 0; z <gridSize - 1; ++z) 
		{
			int i = z * gridSize + x;
			int j = (z + 1) * gridSize + x;

			glm::vec3 iPos = verts[i].GetPosition();
			glm::vec3 jPos = verts[j].GetPosition();
			float rest = glm::length(iPos - jPos);

			Spring spring(k, b, rest);
			spring.SetParticles(&verts[i], &verts[j]);
			structural.push_back(spring);
		}
	}
	for (int x = 0; x <gridSize - 1; ++x)
	{
		for (int z = 0; z <gridSize; ++z) 
		{
			int i = z * gridSize + x;
			int j = z * gridSize + (x + 1);

			glm::vec3 iPos = verts[i].GetPosition();
			glm::vec3 jPos = verts[j].GetPosition();
			float rest = glm::length(iPos - jPos);

			Spring spring(k, b, rest);
			spring.SetParticles(&verts[i], &verts[j]);
			structural.push_back(spring);
		}
	}

	for (int x = 0; x <gridSize - 1; ++x) 
	{
		for (int z = 0; z <gridSize - 1; ++z) 
		{
			int i = z * gridSize + x;
			int j = (z + 1) * gridSize + (x + 1);

			glm::vec3 iPos = verts[i].GetPosition();
			glm::vec3 jPos = verts[j].GetPosition();
			float rest = glm::length(iPos - jPos);

			Spring spring(k, b, rest);
			spring.SetParticles(&verts[i], &verts[j]);
			shear.push_back(spring);
		}
	}

	for (int x = 1; x <gridSize; ++x)
	{
		for (int z = 0; z <gridSize - 1; ++z) 
		{
			int i = z * gridSize + x;
			int j = (z + 1) * gridSize + (x - 1);

			glm::vec3 iPos = verts[i].GetPosition();
			glm::vec3 jPos = verts[j].GetPosition();
			float rest = glm::length(iPos - jPos);

			Spring spring(k, b, rest);
			spring.SetParticles(&verts[i], &verts[j]);
			shear.push_back(spring);
		}
	}

	for (int x = 0; x <gridSize; ++x) 
	{
		for (int z = 0; z <gridSize - 2; ++z) 
		{
			int i = z * gridSize + x;
			int j = (z + 2) * gridSize + x;

			glm::vec3 iPos = verts[i].GetPosition();
			glm::vec3 jPos = verts[j].GetPosition();
			float rest = glm::length(iPos - jPos);

			Spring spring(k, b, rest);
			spring.SetParticles(&verts[i], &verts[j]);
			bend.push_back(spring);
		}
	}

	for (int x = 0; x <gridSize - 2; ++x) 
	{
		for (int z = 0; z <gridSize; ++z) 
		{
			int i = z * gridSize + x;
			int j = z * gridSize + (x + 2);

			glm::vec3 iPos = verts[i].GetPosition();
			glm::vec3 jPos = verts[j].GetPosition();
			float rest = glm::length(iPos - jPos);

			Spring spring(k, b, rest);
			spring.SetParticles(&verts[i], &verts[j]);
			bend.push_back(spring);
		}
	}

}


Cloth::~Cloth()
{
}

void Cloth::AddSpring(const Spring& spring)
{
	Springs.push_back(spring);

}



void Cloth::ClearSprings()
{
	Springs.clear();
}

void Cloth::SetStructuralSprings(float k, float b)
{
	for (int i = 0; i < structural.size(); ++i) 
	{
		structural[i].SetConstants(k, b);
	}
}

void Cloth::SetShearSprings(float k, float b)
{
	for (int i = 0, size = shear.size(); i< size; ++i)
	{
		shear[i].SetConstants(k, b);
	}
}

void Cloth::SetBendSprings(float k, float b)
{
	
	for (int i = 0, size = bend.size(); i < size; ++i)
	{
		bend[i].SetConstants(k, b);
	}
	
}

void Cloth::SetParticleMass(float mass)
{
	for (int i = 0, size = verts.size(); i< size; ++i) 
	{
		verts[i].SetMass(mass);
	}
}

void Cloth::ApplyForces()
{
	for (int i = 0, size = verts.size(); i< size; ++i)
	{
		verts[i].ApplyForces();
	}
}

void Cloth::ApplySpringForces()
{
	for (int i = 0; i < structural.size(); ++i) {
		structural[i].ApplyForce(static_cast<float>(Time::dTimeDelta));
	}
	for (int i = 0, size = shear.size(); i < size; ++i) {
		shear[i].ApplyForce(static_cast<float>(Time::dTimeDelta));
	}
	for (int i = 0, size = bend.size(); i < size; ++i) {
		bend[i].ApplyForce(static_cast<float>(Time::dTimeDelta));
	}
}

void Cloth::Update(float dt)
{
	//// First part of Update remains unchanged!
	//// NEW: Apply spring forces
	//for (int i = 0, size = Springs.size(); i< size; ++i) 
	//{
	//	Springs[i].ApplyForce(static_cast<float>(Time::dTimeDelta));
	//	
	//}

	for (int i = 0, size = verts.size(); i< size; ++i)
	{
		verts[i].Update();
		verts[i].Update();
	}

	// The rest of the Update function remains unchanged
	//// OLD, stays unchanged: Solve constraints
	//for (int i = 0, size = bodies.size(); i< size; ++i) {
	//	bodies[i]->SolveConstraints(constraints);
}

void Cloth::PopulateGrid()
{
	//Had to make a lot of pointers
	/*std::vector<GLfloat> ClothVerticies;
	std::vector<GLuint> ParticleIndicies;*/
	for (int i = 0; i < 120; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			ClothParticlePosition.x = i;
			ClothParticlePosition.y = j;
			ClothParticlePosition.z = 0;
			ParticleEnt* NewParticle = new ParticleEnt(ClothParticlePosition);
			Particles[i].push_back(*NewParticle);

			if (i - 1 >= 0)
			{
				Link LeftLink;
				LeftLink.P1 = &Particles[i - 1][j];
				LeftLink.P2 = NewParticle;
				Links.push_back(LeftLink);
			}

			if (j - 1 >= 0)
			{
				Link AboveLink;
				AboveLink.P1 = &Particles[i][j - 1];
				AboveLink.P2 = NewParticle;
				Links.push_back(AboveLink);
			}

			// Set Positions for grid

			ClothVerticies.push_back(i);
			//Texturedvertices.push_back((;
			ClothVerticies.push_back(j);

			//Setting colour of position on grid
			ClothVerticies.push_back(0.9);
			ClothVerticies.push_back(0.2);
			ClothVerticies.push_back(0.1);
			ClothVerticies.push_back(1);

			//Setting UV Coords
			ClothVerticies.push_back(j / 120);
			ClothVerticies.push_back(i / 120);
		}

	}


	for (int i = 0; i < 119; i++)
	{
		for (int j = 0; j < 119; j++)
		{
			//Points of the square we're drawing
			int P1, P2, P3, P4;

			//Bottom left corner
			P1 = j * 120 + i;
			//Top Left
			P2 = j * 120 + i + 1;
			//Top Right
			P3 = (j + 1) * 120 + i + 1;
			//Bottom Right
			P4 = (j + 1) * 120 + i;

			ParticleIndicies.push_back(P1);
			ParticleIndicies.push_back(P2);
			ParticleIndicies.push_back(P3);
			ParticleIndicies.push_back(P1);
			ParticleIndicies.push_back(P3);
			ParticleIndicies.push_back(P4);

		}
	}

	
	// If no texture, texture source is equal to ""
	vao = Shader::CreateBuffer("", texture, true);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* ClothVerticies.size(), ClothVerticies.data(), GL_STATIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*ParticleIndicies.size(), ParticleIndicies.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &vbo); // Position could be wrong?
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	IndiciesCount = ParticleIndicies.size();

	program = Shader::Programs["BaseProgram"];



	
	for (auto& link : Links)
	{
		link.IndiciesID = ParticleIndicies.size();
		ParticleIndicies.push_back(link.P1->VerticiesArrayId);
		ParticleIndicies.push_back(link.P2->VerticiesArrayId);
	}

	for (int i = 0; i < clothSize; i++)
	{
		for (int j = 0; j < clothSize; j++)
		{

			Particles[i][j].VerticiesArrayId = i * clothSize + j;
			ParticlePositions.push_back(Particles[i][j].GetPosition().x);
			ParticlePositions.push_back(Particles[i][j].GetPosition().y);
			ParticlePositions.push_back(Particles[i][j].GetPosition().z);


			ParticlePositions.push_back(0.6f);
			ParticlePositions.push_back(0.3f);
			ParticlePositions.push_back(0.7f);
		}
	}
}

void Cloth::DrawCloth()
{

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlePositions.size() * sizeof(GLfloat), ParticlePositions.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ARRAY_BUFFER, ParticlePositions.size() * sizeof(GLfloat), ParticlePositions.data(), GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ParticleIndicies.size() * sizeof(GLuint), ParticleIndicies.data(), GL_DYNAMIC_DRAW);


	glUseProgram(program);
	Camera::GetInstance()->SetMVP(transform, program);
	glBindVertexArray(vao);

	// Updates indicies (for when we don't draw some if links are broken)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ParticleIndicies.size() * sizeof(GLuint), ParticleIndicies.data(), GL_DYNAMIC_DRAW);
	// Updates verticies for updating positions
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticleIndicies.size() * sizeof(GLfloat), ParticleIndicies.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawElements(GL_LINES, ParticleIndicies.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	int CurrentVert = 0;
	for (auto& row : Particles)
	{
		for (auto& Particle : row)
		{
			Particle.ApplyForces();
			Particle.Update();

			ParticleIndicies[CurrentVert] = Particle.GetPosition().x;
			ParticleIndicies[CurrentVert + 1] = Particle.GetPosition().y;
			ParticleIndicies[CurrentVert + 2] = Particle.GetPosition().z;
			CurrentVert += 6;
		}
	}
	/*bool Fog = false;
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "bIsTex"), false);
	glUniform1i(glGetUniformLocation(program, "bFog"), false);

	glEnable(GL_BLEND);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glFrontFace(GL_CW);
	glDisable(GL_CULL_FACE);
	Camera::GetInstance()->SetMVP(transform, program);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlePositions.size() * sizeof(GLfloat), ParticlePositions.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDrawElements(GL_TRIANGLES, IndiciesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);*/
}
