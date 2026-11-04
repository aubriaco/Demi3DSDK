
#include "DmMaterialManager.h"
#include "DmDefaultBlends.h"
#include "DmGLExtensions.h"
#include "DmMaterialScript.h"

namespace demi
{
namespace material
{

	DmMaterialManager::DmMaterialManager(system::DmSystem* _system, resource::DmResource* resource)
		: _System(_system), Resource(resource)
	{
		addBlend(new DmBlendAddColor());
		addBlend(new DmBlendAlphaChannel());
	}

	DmMaterialManager::~DmMaterialManager()
	{
		for(int n = 0;n < BlendList.size();n++)
			delete BlendList[n];
		BlendList.clear();
		list<IMaterialScript*>::iterator it;
		for(it = ScriptList.begin();it != ScriptList.end();++it)
			delete (*it);
		ScriptList.clear();
	}

	int DmMaterialManager::addBlend(IBlend* blend)
	{
		BlendList.add(blend);
		return BlendList.size()-1;
	}

	IBlend* DmMaterialManager::getBlend(EMATERIAL_BLEND index)
	{
		if(index < 0 || index >= BlendList.size())
			return 0;
		return BlendList[index];
	}

	int DmMaterialManager::getBlendCount()
	{
		return BlendList.size();
	}

	IMaterialScript* DmMaterialManager::loadScript(const char* filename)
	{
		system::DmFileIO* file = _System->createFileIO(filename,"rb");
		if(file)
		{
			DmMaterialScript* script = new DmMaterialScript(file,Resource);
			delete file;
			ScriptList.push_back(script);
			return script;
		}
		else
			return 0;
	}

}
}
