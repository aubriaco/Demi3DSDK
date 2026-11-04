
#ifndef __DM_CUBE_ENTITY_INCLUDED__
#define __DM_CUBE_ENTITY_INCLUDED__
#include "DmEntity.h"
#include "DmMaterial.h"

namespace demi
{
namespace scene
{

	class DmCubeEntity : public DmEntity
	{
	protected:
		double Size;
		material::DmMaterial Material;
	public:

		DmCubeEntity(DmEntity * parent);

		virtual material::DmMaterial& getMaterial() { return Material; }

		virtual void setMaterial(material::DmMaterial& material) { Material = material; }

		virtual void Render();
	};
}
}

#endif
