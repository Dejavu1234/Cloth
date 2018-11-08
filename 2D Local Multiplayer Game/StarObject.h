#pragma once
#include "Engine\Mesh.h"
class StarObject :
	public Mesh
{
public:
	StarObject(glm::vec4 _Colour);
	~StarObject();

	void BindGeometryObject();
	

	void Render(Utils::Transform Newtransform);
};

