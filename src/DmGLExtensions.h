
#ifndef __DM_GL_EXTENSIONS_INCLUDED__
#define __DM_GL_EXTENSIONS_INCLUDED__
#include "DmRoot.h"
#include <SDL_opengl_glext.h>

namespace demi
{
	extern PFNGLACTIVETEXTUREARBPROC		 glActiveTextureARB;
	extern PFNGLPOINTPARAMETERFARBPROC	 	 glPointParameterfARB;
	extern PFNGLPOINTPARAMETERFVARBPROC		 glPointParameterfvARB;
	extern PFNGLCLIENTACTIVETEXTUREARBPROC	 glClientActiveTextureARB;
	extern PFNGLGENPROGRAMSARBPROC           glGenProgramsARB;
	extern PFNGLDELETEPROGRAMSARBPROC        glDeleteProgramsARB;
	extern PFNGLBINDPROGRAMARBPROC           glBindProgramARB;
	extern PFNGLPROGRAMSTRINGARBPROC         glProgramStringARB;
	extern PFNGLPROGRAMENVPARAMETER4FARBPROC glProgramEnvParameter4fARB;
	extern PFNGLCREATEPROGRAMOBJECTARBPROC  glCreateProgramObjectARB;
	extern PFNGLDELETEOBJECTARBPROC         glDeleteObjectARB;
	extern PFNGLUSEPROGRAMOBJECTARBPROC     glUseProgramObjectARB;
	extern PFNGLCREATESHADEROBJECTARBPROC   glCreateShaderObjectARB;
	extern PFNGLSHADERSOURCEARBPROC         glShaderSourceARB;
	extern PFNGLCOMPILESHADERARBPROC        glCompileShaderARB;
	extern PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
	extern PFNGLATTACHOBJECTARBPROC         glAttachObjectARB;
	extern PFNGLGETINFOLOGARBPROC           glGetInfoLogARB;
	extern PFNGLLINKPROGRAMARBPROC          glLinkProgramARB;
	extern PFNGLGETUNIFORMLOCATIONARBPROC   glGetUniformLocationARB;
	extern PFNGLUNIFORM4FARBPROC            glUniform4fARB;
	extern PFNGLUNIFORM4FVARBPROC			glUniform4fvARB;
	extern PFNGLUNIFORM1IARBPROC            glUniform1iARB;

}

#endif
