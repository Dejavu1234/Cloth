//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Menu.cpp
// Description    	:    main implementation for Menu
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//


// This Includes //
#include "Level.h"

// Engine Includes //
#include "Engine\Plane.h"
#include "Engine\UIButton.h"
#include "Engine\SceneManager.h"
#include "Engine\Cube.h"
#include "Engine\Sphere.h"
#include "Engine\Input.h"
#include "Engine\LogManager.h"
#include "Engine\Time.h"
#include "Engine\SoundManager.h"
#include "Engine/SceneManager.h"
//#include <Box2D/Dynamics/b2World.h>

// Local Includes //
#include "Terrain.h"
#include "Player.h"
#include "Cloth.h"
#include "PartySystem.h"
#include "ParticleEnt.h"

// Library Includes //
#include <iostream>
#include <glm\gtx\string_cast.hpp>




Level::Level(std::string sSceneName)
	:Scene(sSceneName)
{
	/*std::shared_ptr<Cloth> ClothObject = std::make_shared<Cloth>(Cloth(20, 10, {0,0,0}));
	ClothObject->DrawCloth();*/
	//AddEntity(ClothObject);
	std::shared_ptr<Entity> TerrainObject = std::make_shared<Entity>(Entity({ { 0, 0, 0 } ,{ 90, 0, 0 },{1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> TestImage = std::make_shared<Plane>(Plane(20, 20, { 0.9f, 0.3f, 0.1f, 1.0f }, "Resources/Images/Box.png"));
	TerrainObject->AddMesh(TestImage);
	TestImage->bCullFace = false;
	AddEntity(TerrainObject, true);

	std::shared_ptr<PartySystem> ParticleSystem = std::make_shared<PartySystem>(PartySystem({ 0, 0, 0 }, Camera::GetInstance(), "Blacklad"));
	std::shared_ptr<Terrain> ActualTerrainObject = std::make_shared<Terrain>(Terrain({ { 0, 0, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	AddEntity(ActualTerrainObject,true);

	PlayerOb = std::make_shared<Player>(Player({ 5, 20, 5 }));
	AddEntity(PlayerOb, true);
	PlayerOb->TerrainPointer = ActualTerrainObject;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Camera::GetInstance()->EnableSpectatorControls(true);
	
}

Level::~Level()
{

}

void Level::Update()
{	
	Scene::Update();
	Camera::GetInstance()->SetCameraForwardVector(PlayerOb->transform.Position);
	Camera::GetInstance()->EnableSpectatorControls(true);
}

void Level::OnLoadScene()
{
	Scene::OnLoadScene();

	Camera::GetInstance()->SetCameraPos(PlayerOb->transform.Position + glm::vec3(0, 8, -4));
	glm::vec3 DirToPlayer = PlayerOb->transform.Position - Camera::GetInstance()->GetCameraPosition();
	DirToPlayer = glm::normalize(DirToPlayer);
	Camera::GetInstance()->SetCameraForwardVector(DirToPlayer);
}

