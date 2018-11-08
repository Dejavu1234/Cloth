// This Includes //
#include "Player.h"

// Local Includes //
#include "Terrain.h"

// Engine Includes //
#include "Engine\Input.h"
#include "Engine\Time.h"
#include "Engine\Sphere.h"

Player::Player(glm::vec3 StartPos)
	: Entity({ StartPos, { 0, 0, 0 }, {1, 1, 1} }, Utils::CENTER)
{
	std::shared_ptr<Sphere> PlayerSphere = std::make_shared<Sphere>(Sphere(0.5f, 0.5f, 0.5f, { 0.2f, 0.7f, 0.9f, 1.0f }));

	AddMesh(PlayerSphere);
}


Player::~Player()
{

}

void Player::Update()
{
	Entity::Update();
	float Speed = 5.0f;
	if (TerrainPointer)
	{
		if (Input::GetInstance()->KeyState[(unsigned char)'w'] == Input::INPUT_FIRST_PRESS || Input::GetInstance()->KeyState[(unsigned char)'w'] == Input::INPUT_HOLD)
		{
			this->transform.Position.z += Speed * Time::dTimeDelta;
		}
		else if (Input::GetInstance()->KeyState[(unsigned char)'s'] == Input::INPUT_FIRST_PRESS || Input::GetInstance()->KeyState[(unsigned char)'s'] == Input::INPUT_HOLD)
		{
			this->transform.Position.z -= Speed * Time::dTimeDelta;
		}
		
		if (Input::GetInstance()->KeyState[(unsigned char)'a'] == Input::INPUT_FIRST_PRESS || Input::GetInstance()->KeyState[(unsigned char)'a'] == Input::INPUT_HOLD)
		{
			this->transform.Position.x += Speed * Time::dTimeDelta;
		}
		else if (Input::GetInstance()->KeyState[(unsigned char)'d'] == Input::INPUT_FIRST_PRESS || Input::GetInstance()->KeyState[(unsigned char)'d'] == Input::INPUT_HOLD)
		{
			this->transform.Position.x -= Speed * Time::dTimeDelta;
		}

		this->transform.Position.y = TerrainPointer->getHeight(transform.Position.x, transform.Position.z);
	}
}
