#include "SpookySkeleton.h"
#include "ParticleEnt.h"
#include "Engine/Utils.h"
#include "Engine/Time.h"
#include "Engine/Camera.h"


SpookySkeleton::SpookySkeleton()
{
}


SpookySkeleton::~SpookySkeleton()
{
}

void SpookySkeleton::SetShaderEffectVariables()
{
	for (unsigned int i = 0; i < ARRAY_SIZE(m_boneLocation); i++) {
		char name[128];
		memset(name, 0, sizeof(name));
		sprintf_s(name, "jointTransforms[%d]", i);
		m_boneLocation[i] = glGetUniformLocation(program, name);
	} // get locations
	std::vector<Matrix4f> transforms;
	boneTransforms(dt, transforms); // get transform matrix
	for (int i = 0; i < transforms.size(); i++) {
		Matrix4f Transform = transforms[i];
		glUniformMatrix4fv(m_boneLocation[i], 1, GL_TRUE, (const GLfloat*)(Transform));
	} // set transform matrix
}
