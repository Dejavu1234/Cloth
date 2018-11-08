#pragma once

#include "Engine\Entity.h"

class Player :	public Entity
{
public:
	Player(glm::vec3 StartPos);
	~Player();

	virtual void Update() override;

	std::shared_ptr<class Terrain> TerrainPointer;
};

