
#include "DmShaderARB.h"
#include "DmGLExtensions.h"
#include <memory>
#include <cstring>

namespace demi
{
namespace shader
{
	DmShaderARB::DmShaderARB(system::DmFileIO* file)
	{
		std::unique_ptr<char[]> assembly(file->readAll());
		const char* source = assembly ? assembly.get() : "";
		glGenProgramsARB( 1, &ShaderID);
		glBindProgramARB( GL_VERTEX_PROGRAM_ARB, ShaderID );
		glProgramStringARB( GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,
                        static_cast<GLsizei>(std::strlen(source)), source );
	}

	DmShaderARB::~DmShaderARB()
	{
		glDeleteProgramsARB( 1, &ShaderID );
	}

	void DmShaderARB::set()
	{
		glMatrixMode( GL_MODELVIEW );
		glProgramEnvParameter4fARB( GL_VERTEX_PROGRAM_ARB, 0, 1.0f, 1.0f, 1.0f, 1.0f );
		glBindProgramARB( GL_VERTEX_PROGRAM_ARB, ShaderID );
		glEnable( GL_VERTEX_PROGRAM_ARB );
	}

	void DmShaderARB::unset()
	{
		glDisable( GL_VERTEX_PROGRAM_ARB );
	}

}
}
