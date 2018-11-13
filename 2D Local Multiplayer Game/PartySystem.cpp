#include "PartySystem.h"

#include <glm/gtc/type_ptr.hpp>


PartySystem::PartySystem(glm::vec3 origin, Camera * _camera, std::string texFileName)
{
	nParticles = 4000;
	for (int i = 0; i < nParticles; i++) {
		vPosition.push_back(glm::vec3(0.0)); //initialize position vector
		ParticleEnt p = ParticleEnt(
			origin, // pos
			glm::vec3(0.25 * cos(i * .0167) + 0.25f * p.Random() - 0.125f, // vel
				2.0f + 0.25f * p.Random() - 0.125f,
				0.25 * sin(i* .0167) + 0.25f * p.Random() - 0.125f),
			p.Random() + 0.125, // elapsed time
			1.0f, // speed
			i, // id
			_camera); particles.push_back(p); // add 
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenVertexArrays(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vPosition.size(), &vPosition[0],
		GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	for (int i = 0; i < nParticles; i++) {
		particles[i].Update();
		vPosition[i] = particles[i].Position;
	}
	//std::sort(particles.begin(), particles.end(), Comparison()); 


}

PartySystem::~PartySystem()
{
}

void PartySystem::render()
{
	for (int i = 0; i < nParticles; i++) {
		particles[i].Update();
		vPosition[i] = particles[i].Position;
	}
	glm::mat4 viewMat = camera->view;
	glm::vec3 vQuad1, vQuad2;
	glm::vec3 vView = camera->GetCameraForwardVector();
	vView = glm::normalize(vView);
	vQuad1 = glm::cross(vView, camera->GetCameraUpVector());
	vQuad1 = glm::normalize(vQuad1);
	vQuad2 = glm::cross(vView, vQuad1);
	vQuad2 = glm::normalize(vQuad2);
	
	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "vQuad1"), vQuad1.x, vQuad1.y,
		vQuad1.z);
	glUniform3f(glGetUniformLocation(program, "vQuad2"), vQuad2.x, vQuad2.y,
		vQuad2.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "vp"), 1, GL_FALSE, glm::value_ptr(vp));
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(program, "Texture"), 0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vPosition.size(),
		&vPosition[0], GL_STATIC_DRAW);
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, nParticles);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

bool PartySystem::Comparison(ParticleEnt a, ParticleEnt b)
{
	return (a.CameraDistance > b.CameraDistance);
}
