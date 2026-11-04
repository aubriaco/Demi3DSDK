
#ifndef __DM_MATERIAL_SCRIPT__
#define __DM_MATERIAL_SCRIPT__
#include "DmRoot.h"
#include "DmIMaterialScript.h"
#include "DmSystem.h"
#include "DmList.h"
#include "DmResource.h"

#define FUNCTION(f,a,c,d) addToModule((void (*)(aPtr))(f),a,c,d)

namespace demi
{
namespace material
{
	typedef void* TARG;

	struct aPtr
	{
		void* Arg;
		float* Flt;
		int* Integer;
		stringc* String;
		unsigned int Count;

		aPtr() : Arg(nullptr), Flt(nullptr), Integer(nullptr), String(nullptr), Count(0) {}

		void destroy()
		{
			delete[] Integer;
		}
	};

	typedef void (*TFUNCTION)(aPtr);

	struct fPtr
	{
		TFUNCTION Func;
		aPtr Args;
		stringc Section;

		fPtr() : Args() {}
	};

	class DmMaterialScript : public IMaterialScript
	{
	protected:
		stringc Script;
		list<fPtr> Module;
		resource::DmResource* Resource;
		stringc Section;
	public:
		DmMaterialScript(system::DmFileIO* file, resource::DmResource* resource);
		virtual ~DmMaterialScript();

		virtual void set();
		virtual void unset();
		virtual void setSection(stringc name);
	protected:

		virtual void build();
		virtual void addToModule(void (*)(aPtr), aPtr* arg, unsigned int argCount,
			stringc section);
	};

}
}

#endif
