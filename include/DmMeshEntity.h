
#ifndef __DM_MESH_INCLUDED__
#define __DM_MESH_INCLUDED__
#include "DmEntity.h"
#include "DmSMesh.h"

namespace demi
{
namespace scene
{

	class DmMeshEntity : public DmEntity
	{
	protected:
		SMesh*	Mesh;

	public:

		//! Constructor
		DmMeshEntity(DmEntity* parent,SMesh* mesh);

		//! Destructor
		virtual ~DmMeshEntity() {}

		//! Render (Automatically Called)
		virtual void Render();


		virtual SMesh* getMesh() { return Mesh; }

		virtual void setMaterial(material::IMaterial* mat);

	};

}
}

#endif
