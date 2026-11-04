
#ifndef __I_M_LOADER_INCLUDED__
#define __I_M_LOADER_INCLUDED__
#include "DmRoot.h"
#include "DmSystem.h"
#include "DmSMesh.h"
#include "DmSMeshGroup.h"
#include "DmResource.h"
#include "DmMaterialManager.h"

namespace demi
{
namespace scene
{

	class IMLoader : public DmRoot
	{
	protected:
		system::DmSystem* _System;
		resource::DmResource* Resource;
		material::DmMaterialManager* MaterialManager;
	public:
		virtual void construct(system::DmSystem* _system, resource::DmResource* resource,
			material::DmMaterialManager* mmgr)
		{
			_System = _system;
			Resource = resource;
			MaterialManager = mmgr;
		}

		virtual bool isBinary() = 0;

		virtual SMesh load(system::DmFileIO* file) = 0;

		virtual bool isLoadableFile(stringc filename) = 0;
	};

}
}

#endif
