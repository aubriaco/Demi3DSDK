
#ifndef __DM_MATERIAL_MANAGER_INCLUDED__
#define __DM_MATERIAL_MANAGER_INCLUDED__
#include "DmRoot.h"
#include "DmIBlend.h"
#include "DmIMaterialScript.h"
#include "DmList.h"
#include "DmSystem.h"
#include "DmResource.h"

namespace demi
{
namespace material
{
	enum EMATERIAL_BLEND
	{
		EMB_ADD_COLOR,
		EMB_ALPHA_CHANNEL,
		EMB_COUNT
	};

	class DmMaterialManager : public DmRoot
	{
	protected:
		system::DmSystem* _System;
		resource::DmResource* Resource;
		array<IBlend*> BlendList;
		list<IMaterialScript*> ScriptList;
	public:
		DmMaterialManager(system::DmSystem* _system, resource::DmResource* resource);
		virtual ~DmMaterialManager();

		virtual int addBlend(IBlend* blend);
		virtual IBlend* getBlend(EMATERIAL_BLEND index);
		virtual int getBlendCount();

		virtual IMaterialScript* loadScript(const char* filename);
	};

}
}


#endif
