
#ifndef __DM_I_SHADER_INCLUDED__
#define __DM_I_SHADER_INCLUDED__
#include "DmRoot.h"
#include "DmString.h"

namespace demi
{
namespace shader
{
	enum ESHADER_TYPE
	{
		ESHT_ARB,
		ESHT_VERTEX,
		ESHT_PIXEL,
		ESHT_COUNT
	};

	class IShader
	{
	protected:
		unsigned int ShaderID;
	public:
		virtual void set() = 0;
		virtual void unset() = 0;
	};
}
}

#endif
