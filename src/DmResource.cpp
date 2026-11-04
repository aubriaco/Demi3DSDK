
#include "../include/DmResource.h"
#include "DmBMPTextureLoader.h"

namespace demi
{
namespace resource
{
	DmResource::DmResource()
	{
		addTextureLoader(new DmBMPTextureLoader());
	}

	DmResource::~DmResource()
	{
		list<DmTexture*>::iterator it;
		for(it = Textures.begin();it != Textures.end();++it)
			delete (*it);
		Textures.clear();
		for(int n = 0;n < TextureLoaders.size();n++)
			delete TextureLoaders[n];
		TextureLoaders.clear();
	}

	DmTexture* DmResource::loadTexture(const char* filename, E_TEXTURE_TYPE type)
	{
		list<DmTexture*>::iterator it;
		for(it = Textures.begin();it != Textures.end();++it)
			if((*it)->getName() == filename)
				return (*it);
		for(int n = 0;n < TextureLoaders.size();n++)
		{
			if(TextureLoaders[n])
			{
				if(TextureLoaders[n]->isLoadable(filename))
				{
					DmTexture* tex = TextureLoaders[n]->load(filename);
					if (tex)
					{
						Textures.push_back(tex);
						return tex;
					}
				}
			}
		}
		return 0;
	}

	int DmResource::addTextureLoader(ITextureLoader* loader)
	{
		TextureLoaders.push_back(loader);
		return TextureLoaders.size()-1;
	}
}
}
