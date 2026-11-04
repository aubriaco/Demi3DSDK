
#include "../include/DmLightEntity.h"

namespace demi
{
namespace scene
{
	DmLightEntity::DmLightEntity(DmEntity* parent, int lightId, float radius)
		: DmEntity(parent)
	{
		LightID = lightId;
		Attenuation = 1;
		Radius = radius;
		Diffuse = color4(1,1,1,1);
		glEnable(GL_LIGHTING);
	}

	void DmLightEntity::PreRender()
	{
		glLightfv(LightID,GL_DIFFUSE,Diffuse.toGL());
		glLightfv(LightID,GL_POSITION,Position.toGL());
		glLightf(LightID,GL_LINEAR_ATTENUATION , Attenuation / Radius);
		glEnable(LightID);
	}
}
}
