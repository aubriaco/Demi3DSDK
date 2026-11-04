
#ifndef __DM_RESOURCE_INCLUDED__
#define __DM_RESOURCE_INCLUDED__
#include "DmRoot.h"
#include "DmTexture.h"
#include "DmArray.h"
#include "DmITextureLoader.h"
#include "DmList.h"

namespace demi
{
namespace resource
{

	class DmResource : public DmRoot
	{
	protected:
		list<DmTexture*> Textures;
		array<ITextureLoader*> TextureLoaders;
	public:
		DmResource();
		virtual ~DmResource();
		virtual DmTexture* loadTexture(const char* filename, E_TEXTURE_TYPE type = ETT_GUESS);
		virtual int addTextureLoader(ITextureLoader* loader);
	};

}
}

#endif
