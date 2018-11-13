#include "ShadowMap.h"
#include "Engine/Utils.h"
#include "Engine/Shader.h"
#include "Engine/Camera.h"
#include <fstream>


ShadowMap::ShadowMap()
{
}


ShadowMap::~ShadowMap()
{
}

void ShadowMap::init()
{
	// depth texture
	GLuint depthMapTexture;
	glGenTextures(1, &depthMapTexture);
	glBindTexture(GL_TEXTURE_2D, depthMapTexture);
	glTexImage2D(GL_TEXTURE_2D,
		0, //mipmap level
		GL_DEPTH_COMPONENT, //internal format
		1280, //screen width
		720, //screen height
		0, //border
		GL_DEPTH_COMPONENT, //color format
		GL_FLOAT, //data type
		NULL);


	GLuint depthMapFBO; // global variable
	glGenFramebuffers(1, &depthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	// attach depth texture as FBO's depth buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER,
		GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapTexture, 0);
	//disable writes to color buffer
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind buffer

	GLenum Status =
		glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		printf("FB error, status: 0x%x\n", Status);
	}
}

void ShadowMap::ShadowMapStart()
{
//	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMap::ShadowMapEnd()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

