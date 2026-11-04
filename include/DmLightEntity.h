
#ifndef __DM_LIGHT_ENTITY_INCLUDED__
#define __DM_LIGHT_ENTITY_INCLUDED__
#include "DmEntity.h"

namespace demi
{
namespace scene
{
	class DmLightEntity : public DmEntity
	{
	protected:
		float Attenuation;
		color4 Diffuse;
		int LightID;
		float Radius;
	public:
		DmLightEntity(DmEntity* parent, int lightId, float radius = 300.0f);

		virtual void setAttenuation(float attenuation) { Attenuation = attenuation; }

		virtual void setDiffuse(color4 diffuse) { Diffuse = diffuse; }

		virtual void setRadius(float radius) { Radius = radius; }

		virtual void PreRender();
	};
}
}

#endif
