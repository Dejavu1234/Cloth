#include "StarObject.h"
#include "Engine\Shader.h"
#include "Engine\Camera.h"
#include "Engine\Utils.h"




StarObject::StarObject(glm::vec4 _Colour)
{
	m_fWidth = 1;
	m_fHeight = 1;
	m_iIndicies = 1;
	Colour = _Colour;
	TextureSource = "";
	bHasTexture = false;
	BindGeometryObject();
	m_eShape = Utils::GEOMETRY;
	program = Shader::Programs["GeometryShader"];

	SetInitialStates();
}

StarObject::~StarObject()
{
}

void StarObject::BindGeometryObject()
{
	GLfloat vertices[] = {
		// Position						// Color		
		0.0f, 0.0f, 0.0f,				 Colour.r, Colour.g, Colour.b, Colour.a, //passing in 1 point
	};

	// If no texture, texture source is equal to ""
	vao = Shader::CreateBuffer("", texture, true);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void StarObject::Render(Utils::Transform Newtransform)
{
	glUseProgram(program);
	if (bHasTexture)
	{
		glEnable(GL_BLEND);
	}
	else
	{
		glDisable(GL_BLEND);
	}
	glFrontFace(GL_CW);
	glDisable(GL_CULL_FACE);
	//Mesh::Render(Newtransform);

	Camera::GetInstance()->SetMVP(Newtransform, program);

	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}


