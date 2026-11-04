
#include "DmShaderManager.h"
#include "DmShaderARB.h"
#include "DmShaderVertex.h"
#include "DmGLExtensions.h"
#include <memory>

namespace demi
{
namespace shader
{
	DmShaderManager::~DmShaderManager()
	{
		list<IShader*>::iterator it;
		for(it = Shaders.begin();it != Shaders.end();++it)
			if(*it)
				delete (*it);
		Shaders.clear();
	}

	IShader* DmShaderManager::loadShader(const char* filename, ESHADER_TYPE type)
	{
		std::unique_ptr<system::DmFileIO> file(_System->createFileIO(filename,"r"));
		if (!file) return nullptr;
		IShader* shader = 0;
		switch(type)
		{
		case ESHT_ARB:
			if (glGenProgramsARB && glDeleteProgramsARB && glBindProgramARB &&
				glProgramStringARB && glProgramEnvParameter4fARB)
				shader = new DmShaderARB(file.get());
			break;
		case ESHT_VERTEX:
			if (glCreateShaderObjectARB && glCreateProgramObjectARB && glShaderSourceARB &&
				glCompileShaderARB && glGetObjectParameterivARB && glGetInfoLogARB &&
				glAttachObjectARB && glLinkProgramARB && glDeleteObjectARB && glUseProgramObjectARB &&
				glGetUniformLocationARB && glUniform4fARB && glUniform4fvARB && glUniform1iARB)
				shader = new DmShaderVertex(file.get());
			break;
		}
		if (shader) Shaders.push_back(shader);
		return shader;
	}

	void DmShaderManager::deleteShader(IShader* shader)
	{
		list<IShader*>::iterator it;
		for(it = Shaders.begin();it != Shaders.end();++it)
			if((*it) == shader)
			{
				delete (*it);
				Shaders.remove(it);
				return;
			}
	}
}
}
