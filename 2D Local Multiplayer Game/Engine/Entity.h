//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Entity.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

#pragma once
//Entity.h
#ifndef _ENTITY_H
#define _ENTITY_H

// Library Includes //
#include <memory>

// OpenGL Library Includes //
#include <glm/common.hpp>

// Engine Includes //
#include "Utils.h"
#include "Mesh.h"
#include <Box2D.h>
//#include "Plane.h"
//#include "Sphere.h"
//#include "Pyramid.h"


class Entity : public std::enable_shared_from_this<Entity>
{
public:
	Entity(Utils::Transform _Transform, Utils::EANCHOR _Anchor);
	//Entity() {};
	/*Entity(Utils::Transform _Transform, float _fWidth, float _fHeight, Utils::EANCHOR _Anchor, glm::vec4 _Colour, Utils::ESHAPE _eShape);
	Entity(Utils::Transform _Transform, float _fWidth, float _fHeight, Utils::EANCHOR _Anchor, glm::vec4 _Colour, const char* TextureSource, Utils::ESHAPE _eShape, glm::vec4 UVCoords = glm::vec4(0, 1, 0, 1));
	Entity(Utils::Transform _Transform, float _fWidth, float _fHeight, Utils::EANCHOR _Anchor, glm::vec4 _Colour, const char* TextureSource, int iCount, bool bHorizontal);
	Entity(Utils::Transform _Transform, float _fWidth, float _fHeight, Utils::EANCHOR _Anchor, glm::vec4 _Colour, const char* TextureSource, glm::vec2 v2FrameCounts, int _iFPS);*/
	~Entity();
	
	void AddMesh(std::shared_ptr<Mesh> _NewMesh);
	//void AddMesh(Utils::ESHAPE _NewShape);

	virtual void DrawEntity();
	void BaseUpdate();
	virtual void Update();
	virtual void OnDestroy();
	virtual void Reset();

	virtual void SetActive(bool _bIsActive, bool _bIsInitialState = false);
	bool IsActive() { return bActive; };
	virtual void SetVisible(bool _bIsVisible, bool _bIsInitialState = false);
	bool IsVisible() { return bVisible; };
	
	void Translate(glm::vec3 _Movement);
	void Rotate(glm::vec3 Rotate); 
	void SetScale(glm::vec3 _NewScale);


	Utils::Transform transform;
	Utils::EANCHOR EntityAnchor;
	std::shared_ptr<Mesh> EntityMesh;
	
	int GetEntityValue() { return iEntityID; };
	void SetInitialEntity(bool IsInitial) { bIsInitialEntity = IsInitial; };
	bool IsInitialEntity() { return bIsInitialEntity; };

	// Box2D Physics
	b2Body* body = nullptr;
	void SetupB2BoxBody(b2World& Box2DWorld, b2BodyType BodyType, bool bCanRotate = true, bool bHasFixture = true, float Density = 1.0f, float Friction = 0.3f, bool IsBullet = false);
	void SetupB2CircleBody(b2World& Box2DWorld, b2BodyType BodyType, bool bCanRotate = true, bool bHasFixture = true, float Density = 1.0f, float Friction = 0.3f);

	void SetBox2DTransform(glm::vec3 _Position, float _Rotation);

	void ShadowMap();
	
protected:
	bool bActive = true;
	bool bVisible = true;
	bool bIsInitialEntity = false;

	int iEntityID;

	struct InitialState
	{
		Utils::Transform transform;
		Utils::EANCHOR EntityAnchor;
		bool bActive;
		bool bVisible;
		int iEntityID;
	};

	InitialState EntityInitialState;
};

#endif