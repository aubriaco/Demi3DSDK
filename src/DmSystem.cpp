
#include "../include/DmSystem.h"

namespace demi
{
namespace system
{
	DmSystem::DmSystem()
		: DmRoot()
	{}

	bool DmSystem::fileExists(const char* filename)
	{
		FILE* file = fopen(filename,"rb");
		if(file)
		{
			fclose(file);
			return true;
		}
		else
			return false;
	}

	DmFileIO * DmSystem::createFileIO(stringc filename,stringc access)
	{
		auto* file = new DmFileIO(filename, access);
		if (file->isOpen())
			return file;
		delete file;
		return nullptr;
	}

}
}
