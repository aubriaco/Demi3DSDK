
#ifndef __DM_ENGINE_INCLUDED__
#define __DM_ENGINE_INCLUDED__
#include "DmRoot.h"
#include "DmScene.h"
#include "DmSystem.h"
#include "DmResource.h"
#include "DmEffects.h"
#include "DmColor.h"
#include "DmMaterialManager.h"
#include "DmShaderManager.h"


struct SDL_Window;

namespace demi
{

	enum E_FOG_MODE
	{
		EFM_EXP = GL_EXP,
		EFM_EXP2 = GL_EXP2,
		EFM_LINEAR = GL_LINEAR
	};

	struct SDemiDeviceParameters
	{
		int *argc;
		char **argv;
		int Width;
		int Height;
		int Bits; // Retained for source compatibility. SDL selects the color format.
		bool Fullscreen;
		const char * Title;
	};

	class DmDevice : public DmRoot
	{
	private:
		SDL_Window* Window = nullptr;
		void* Context = nullptr;
		bool Running = false;
		void closeWindow();

	protected:
		scene::DmScene*	Scene;
		system::DmSystem* _System;
		resource::DmResource* Resource;
		effect::DmEffects* Effects;
		material::DmMaterialManager* MaterialManager;
		shader::DmShaderManager* ShaderManager;



	public:
		DmDevice(SDemiDeviceParameters params);
		DmDevice(const DmDevice&) = delete;
		DmDevice& operator=(const DmDevice&) = delete;
		virtual ~DmDevice();

		virtual scene::DmScene * getScene();
		virtual system::DmSystem * getSystem();
		virtual resource::DmResource* getResourceManager();
		virtual effect::DmEffects* getEffects();
		virtual material::DmMaterialManager* getMaterialManager();
		virtual shader::DmShaderManager* getShaderManager();

		virtual void setFog(bool enabled, E_FOG_MODE mode, float start, float end,
			float density, color4 color);

		bool isRunning() const { return Running; }
		virtual void beginScene();
		virtual void renderScene();
		virtual void flushScene();

		virtual void resizeScene(int width, int height);

		virtual bool createWindow(SDemiDeviceParameters & params);
	};

}

#endif
