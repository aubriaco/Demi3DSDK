
#ifndef __DM_MATERIAL_INCLUDED__
#define __DM_MATERIAL_INCLUDED__
#include "DmTexture.h"
#include "DmIBlend.h"
#include "DmColor.h"
#include "DmIShader.h"
#include "DmIMaterialScript.h"

namespace demi
{
namespace material
{
	class IMaterial
	{
	public:
		virtual void setBlend(IBlend* blend) = 0;
		virtual IBlend* getBlend() = 0;

		virtual void setShader(shader::IShader* shader) = 0;
		virtual shader::IShader* getShader() = 0;

		virtual void setMaterialScript(IMaterialScript* script, stringc section) = 0;
		virtual IMaterialScript* getMaterialScript() = 0;
	};

	class DmMaterial : public IMaterial
	{
	protected:
		IBlend*					Blend;
		IMaterialScript*		Script;
		stringc					ScriptSection;
		shader::IShader*		Shader;
	public:
		stringc					Name;
		color4					Color;
		// Borrowed textures, typically owned by the resource manager.
		resource::DmTexture*	Textures[8];

		DmMaterial();
		virtual ~DmMaterial();

		virtual void setBlend(IBlend* blend) { Blend = blend; }
		virtual IBlend* getBlend() { return Blend; }

		virtual void setShader(shader::IShader* shader) { Shader = shader; }
		virtual shader::IShader* getShader() { return Shader; }

		virtual void setMaterialScript(IMaterialScript* script, stringc section = "")
		{ Script = script; ScriptSection = section; }
		virtual IMaterialScript* getMaterialScript() { return Script; }

		virtual void set();
		virtual void unset();
	};
}
}

#endif
