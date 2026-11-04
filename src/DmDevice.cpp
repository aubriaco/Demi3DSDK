
#include "../include/DmDevice.h"
#include "DmGLExtensions.h"

#include <SDL.h>
#include <stdexcept>
#include <memory>

namespace demi
{
	DmDevice::DmDevice(SDemiDeviceParameters params)
	{
		if (!createWindow(params))
			throw std::runtime_error(SDL_GetError());
		try
		{
			glEnable(GL_TEXTURE_2D);
			glShadeModel(GL_SMOOTH);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClearDepth(1.0f);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);
			const char* ext = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
			if (!ext) throw std::runtime_error("OpenGL compatibility context unavailable");
			glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)SDL_GL_GetProcAddress("glActiveTexture");
			glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)SDL_GL_GetProcAddress("glClientActiveTexture");


			if(strstr(ext,"GL_ARB_shading_language_100") == 0)
				log("WARNING: Shader Language 1.0 not supported.");

			if(strstr(ext,"GL_ARB_shader_objects") == 0)
				log("WARNING: Shader Objects not supported.");

			// Shaders ARB
			glGenProgramsARB		   = (PFNGLGENPROGRAMSARBPROC)SDL_GL_GetProcAddress("glGenProgramsARB");
			glDeleteProgramsARB		= (PFNGLDELETEPROGRAMSARBPROC)SDL_GL_GetProcAddress("glDeleteProgramsARB");
			glBindProgramARB		   = (PFNGLBINDPROGRAMARBPROC)SDL_GL_GetProcAddress("glBindProgramARB");
			glProgramStringARB		 = (PFNGLPROGRAMSTRINGARBPROC)SDL_GL_GetProcAddress("glProgramStringARB");
			glProgramEnvParameter4fARB = (PFNGLPROGRAMENVPARAMETER4FARBPROC)SDL_GL_GetProcAddress("glProgramEnvParameter4fARB");

			// Shaders Vertex and Pixel

			glCreateProgramObjectARB  = (PFNGLCREATEPROGRAMOBJECTARBPROC)SDL_GL_GetProcAddress("glCreateProgramObjectARB");
			glDeleteObjectARB         = (PFNGLDELETEOBJECTARBPROC)SDL_GL_GetProcAddress("glDeleteObjectARB");
			glUseProgramObjectARB     = (PFNGLUSEPROGRAMOBJECTARBPROC)SDL_GL_GetProcAddress("glUseProgramObjectARB");
			glCreateShaderObjectARB   = (PFNGLCREATESHADEROBJECTARBPROC)SDL_GL_GetProcAddress("glCreateShaderObjectARB");
			glShaderSourceARB         = (PFNGLSHADERSOURCEARBPROC)SDL_GL_GetProcAddress("glShaderSourceARB");
			glCompileShaderARB        = (PFNGLCOMPILESHADERARBPROC)SDL_GL_GetProcAddress("glCompileShaderARB");
			glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)SDL_GL_GetProcAddress("glGetObjectParameterivARB");
			glAttachObjectARB         = (PFNGLATTACHOBJECTARBPROC)SDL_GL_GetProcAddress("glAttachObjectARB");
			glGetInfoLogARB           = (PFNGLGETINFOLOGARBPROC)SDL_GL_GetProcAddress("glGetInfoLogARB");
			glLinkProgramARB          = (PFNGLLINKPROGRAMARBPROC)SDL_GL_GetProcAddress("glLinkProgramARB");
			glGetUniformLocationARB   = (PFNGLGETUNIFORMLOCATIONARBPROC)SDL_GL_GetProcAddress("glGetUniformLocationARB");
			glUniform4fARB            = (PFNGLUNIFORM4FARBPROC)SDL_GL_GetProcAddress("glUniform4fARB");
			glUniform4fvARB			  = (PFNGLUNIFORM4FVARBPROC)SDL_GL_GetProcAddress("glUniform4fvARB");
			glUniform1iARB		    = (PFNGLUNIFORM1IARBPROC)SDL_GL_GetProcAddress("glUniform1iARB");


			if (!glActiveTextureARB || !glClientActiveTextureARB)
				throw std::runtime_error("OpenGL multitexture support is required");
			auto system = std::make_unique<demi::system::DmSystem>();
			auto resource = std::make_unique<demi::resource::DmResource>();
			auto materials = std::make_unique<material::DmMaterialManager>(system.get(), resource.get());
			auto shaders = std::make_unique<shader::DmShaderManager>(system.get());
			auto scene = std::make_unique<demi::scene::DmScene>(system.get(), resource.get(), materials.get());
			auto effects = std::make_unique<effect::DmEffects>();
			_System = system.release();
			Resource = resource.release();
			MaterialManager = materials.release();
			ShaderManager = shaders.release();
			Scene = scene.release();
			Effects = effects.release();
		}
		catch (...)
		{
			closeWindow();
			throw;
		}
	}

	DmDevice::~DmDevice()
	{
		SDL_GL_MakeCurrent(Window, Context);
		delete Effects;
		delete Scene;
		delete ShaderManager;
		delete MaterialManager;
		delete Resource;
		delete _System;
		closeWindow();
	}

	void DmDevice::setFog(bool enable, E_FOG_MODE mode, float start, float end,
			float density, color4 color)
	{
		glClearColor(color.R,color.G,color.B,color.A);
		glFogi(GL_FOG_MODE, (int)mode);
		glFogfv(GL_FOG_COLOR, color.toGL());
		glFogf(GL_FOG_DENSITY, density);
		glHint(GL_FOG_HINT, GL_DONT_CARE);
		glFogf(GL_FOG_START, start);
		glFogf(GL_FOG_END, end);
		if(enable)
			glEnable(GL_FOG);
		else
			glDisable(GL_FOG);
	}

	void DmDevice::beginScene()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT ||
				(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
				 event.window.windowID == SDL_GetWindowID(Window)))
				Running = false;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED &&
				event.window.windowID == SDL_GetWindowID(Window))
			{
				int width, height;
				SDL_GL_GetDrawableSize(Window, &width, &height);
				resizeScene(width, height);
			}
		}
		if (!Running)
			return;
		ExecutePreEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
	}

	void DmDevice::renderScene()
	{
		ExecuteRender();
	}

	void DmDevice::flushScene()
	{
		glFlush();
		SDL_GL_SwapWindow(Window);
		ExecutePostEvents();
	}

	void DmDevice::resizeScene(int width, int height)
	{
		if (width <= 0 || height <= 0) return;													

		glViewport(0,0,width,height);									

		glMatrixMode(GL_PROJECTION);									
		glLoadIdentity();												

		
		gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);	

		glMatrixMode(GL_MODELVIEW);										
		glLoadIdentity();
	}

	scene::DmScene * DmDevice::getScene()
	{
		return Scene;
	}

	system::DmSystem * DmDevice::getSystem()
	{
		return _System;
	}

	resource::DmResource* DmDevice::getResourceManager()
	{
		return Resource;
	}

	effect::DmEffects* DmDevice::getEffects()
	{
		return Effects;
	}

	material::DmMaterialManager* DmDevice::getMaterialManager()
	{
		return MaterialManager;
	}

	shader::DmShaderManager* DmDevice::getShaderManager()
	{
		return ShaderManager;
	}


	bool DmDevice::createWindow(SDemiDeviceParameters& params)
	{
		if (Window)
			return false;
		SDL_SetMainReady();
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
			return false;
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 0);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		const auto flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
			(params.Fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
		Window = SDL_CreateWindow(params.Title, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, params.Width, params.Height, flags);
		if (Window)
			Context = SDL_GL_CreateContext(Window);
		if (!Context)
		{
			const std::string error = SDL_GetError();
			closeWindow();
			SDL_SetError("%s", error.c_str());
			return false;
		}
		SDL_GL_SetSwapInterval(1);
		int width, height;
		SDL_GL_GetDrawableSize(Window, &width, &height);
		resizeScene(width, height);
		Running = true;
		return true;
	}

	void DmDevice::closeWindow()
	{
		if (Context)
			SDL_GL_DeleteContext(Context);
		if (Window)
			SDL_DestroyWindow(Window);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		Context = nullptr;
		Window = nullptr;
		Running = false;
	}
}
