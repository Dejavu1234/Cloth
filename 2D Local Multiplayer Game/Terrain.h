#pragma once
#include "Engine\Entity.h"

#include <vector>

struct InitInfo
{
	std::string HeightmapFilename;

	float HeightScale;
	float HeightOffset;
	int NumRows;
	int NumCols;
	float CellSpacing;
};

class Terrain :
	public Entity
{
public:
	Terrain(Utils::Transform _Transform, Utils::EANCHOR _Anchor);
	~Terrain();

	virtual void DrawEntity() override;

	void loadHeightmap();

	void smooth();

	bool inBounds(UINT i, UINT j);

	float average(UINT i, UINT j);

	float getHeight(float x, float z) const;

private:
	GLuint program;
	GLuint vao;
	GLuint texture;
	int IndiciesCount;
	std::vector<float> mHeightmap;

	std::vector<std::vector<glm::vec3>> Points;
	InitInfo mInfo;
};

