
#ifndef __DM_SHADER_MANAGER_INCLUDED__
#define __DM_SHADER_MANAGER_INCLUDED__
#include "DmRoot.h"
#include "DmSystem.h"
#include "DmIShader.h"
#include "DmList.h"

namespace demi
{
namespace shader
{
	class DmShaderManager
	{
	protected:
		system::DmSystem* _System;
		list<IShader*> Shaders;
	public:
		DmShaderManager(system::DmSystem* _system) : _System(_system) {}
		virtual ~DmShaderManager();
		virtual IShader* loadShader(const char* filename,ESHADER_TYPE type);
		virtual void deleteShader(IShader* shader);
	};

}
}

#endif
