
#include "DmShaderVertex.h"
#include "DmGLExtensions.h"
#include <memory>

namespace demi
{
namespace shader
{
	DmShaderVertex::DmShaderVertex(system::DmFileIO *file)
	{
		std::unique_ptr<char[]> assembly(file->readAll());
		const char* vertexStrings[] = {assembly ? assembly.get() : ""};
		VertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
		glShaderSourceARB(VertexShader, 1, vertexStrings, NULL);
		glCompileShaderARB(VertexShader);
		glGetObjectParameterivARB(VertexShader, GL_OBJECT_COMPILE_STATUS_ARB, 
			&VertexCompiled);
		char str[4096];
		if(VertexCompiled == false)
		{
			glGetInfoLogARB(VertexShader, sizeof(str), NULL, str);
			log("Failed to compile vertex shader.");
			log(str);
		}
		Program = glCreateProgramObjectARB();
		glAttachObjectARB(Program,VertexShader);
		glLinkProgramARB(Program);
		GLint linked;
		glGetObjectParameterivARB(Program, GL_OBJECT_LINK_STATUS_ARB, &linked);
		if(linked == false)
		{
			glGetInfoLogARB(Program, sizeof(str), NULL, str);
			log(str);
		}
	}

	DmShaderVertex::~DmShaderVertex()
	{
		glDeleteObjectARB(VertexShader);
		glDeleteObjectARB(Program);
	}

	void DmShaderVertex::set()
	{
		glUseProgramObjectARB(Program);
	}

	void DmShaderVertex::unset()
	{
		glUseProgramObjectARB(0);
	}
}
}
