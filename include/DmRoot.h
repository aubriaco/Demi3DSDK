
#ifndef __DM_ROOT_INCLUDED__
#define __DM_ROOT_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#	include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstring>
#include <DmString.h>
#include <DmArray.h>

namespace demi
{
	class DmRoot
	{
	protected:
		virtual void log(stringc str);
	public:
		DmRoot();
		virtual ~DmRoot();

		virtual void Render() {}
		virtual void PreEvents() {}
		virtual void PostEvents() {}
	};
	
	
	void ExecutePreEvents();
	void ExecutePostEvents();
	void ExecuteRender();
}

#endif
