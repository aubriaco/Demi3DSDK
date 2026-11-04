
#ifndef __S_MESH_INCLUDED__
#define __S_MESH_INCLUDED__
#include "DmRoot.h"
#include "DmVertex.h"
#include "DmMaterial.h"
#include "DmSMeshGroup.h"

namespace demi
{
namespace scene
{

	class SMesh
	{
	public:
		array<SMeshGroup*> Groups;

		SMesh() {}

		virtual void draw();
	};

}
}


#endif
