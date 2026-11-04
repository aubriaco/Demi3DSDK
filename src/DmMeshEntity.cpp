
#include "../include/DmMeshEntity.h"

namespace demi
{
namespace scene
{
	DmMeshEntity::DmMeshEntity(DmEntity* parent,SMesh* mesh)
		: DmEntity(parent)
	{
		Mesh = mesh;
	}

	void DmMeshEntity::setMaterial(material::IMaterial* mat)
	{
		auto* dmat = dynamic_cast<material::DmMaterial*>(mat);
		if (dmat && Mesh && Mesh->Groups.size())
			Mesh->Groups[0]->Material = *dmat;
	}

	void DmMeshEntity::Render()
	{
		setupRender();
		if(Mesh)
			Mesh->draw();
	}

}
}
