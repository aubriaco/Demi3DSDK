
#ifndef __DM_SHADER_INCLUDED__
#define __DM_SHADER_INCLUDED__
#include "DmRoot.h"
#include "DmSystem.h"
#include "DmIShader.h"

namespace demi
{
namespace shader
{

	class DmShaderARB : public IShader
	{
	public:
		DmShaderARB(system::DmFileIO* file);
		virtual ~DmShaderARB();

		virtual void set();
		virtual void unset();
	};
}
}

#endif
