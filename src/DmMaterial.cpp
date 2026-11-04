
#include "../include/DmMaterial.h"
#include "DmGLExtensions.h"

namespace demi
{
namespace material
{
	DmMaterial::DmMaterial()
	{
		for (auto& texture : Textures)
			texture = nullptr;
		Blend = 0;
		Shader = 0;
		Script = 0;
	}

	DmMaterial::~DmMaterial() = default;

	void DmMaterial::set()
	{
		if(Textures[0])
		{
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, Textures[0]->getTexture());
		}
		if(Textures[1])
		{
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, Textures[1]->getTexture());
		}
		if(Blend)
			Blend->set();
		if(Shader)
			Shader->set();
		if(Script)
		{
			Script->setSection(ScriptSection);
			Script->set();
		}
	}

	void DmMaterial::unset()
	{
		if(Script)
			Script->unset();
		if(Shader)
			Shader->unset();
		if(Blend)
			Blend->unset();
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glDisable(GL_TEXTURE_2D);
	}
}
}
