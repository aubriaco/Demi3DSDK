
#ifndef __DM_FILE_SYSTEM_INCLUDED__
#define __DM_FILE_SYSTEM_INCLUDED__
#include "DmRoot.h"
#include "DmFileIO.h"

namespace demi
{
namespace system
{
	class DmSystem : public DmRoot
	{
	public:
		DmSystem();

		virtual bool fileExists(const char* filename);

		virtual DmFileIO * createFileIO(stringc filename,stringc access);
	};
}
}

#endif
