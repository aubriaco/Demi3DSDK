
#ifndef __DM_I_TEXTURE_LOADER_INCLUDED__
#define __DM_I_TEXTURE_LOADER_INCLUDED__
#include "DmSystem.h"
#include "DmTexture.h"

namespace demi
{
namespace resource
{

	class ITextureLoader
	{
	public:
		virtual DmTexture* load(const char* filename) = 0;

		virtual bool isLoadable(const char* filename) = 0;
	};
}
}

#endif
