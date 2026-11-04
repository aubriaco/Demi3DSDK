
#ifndef __DM_SHADER_VERTEX__
#define __DM_SHADER_VERTEX__
#include "DmIShader.h"
#include "DmSystem.h"
#include "DmGLExtensions.h"

namespace demi
{
namespace shader
{

	class DmShaderVertex : public IShader, DmRoot
	{
	protected:
		GLhandleARB Program;
		GLhandleARB VertexShader;
		GLint VertexCompiled;
	public:
		DmShaderVertex(system::DmFileIO* file);
		virtual ~DmShaderVertex();

		virtual void set();
		virtual void unset();
	};

}
}

#endif
