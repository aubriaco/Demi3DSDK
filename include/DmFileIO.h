
#ifndef __DM_FILE_IO_INCLUDED__
#define __DM_FILE_IO_INCLUDED__
#include "DmRoot.h"
#include "DmVector.h"
#include "DmColor.h"
#include "DmString.h"

namespace demi
{
namespace system
{
	class DmFileIO : public DmRoot
	{
	protected:
		stringc FileName;
		stringc Access;
		FILE * File;
	public:
		DmFileIO(stringc filename,stringc access);
		virtual ~DmFileIO();

		virtual stringc getFileName() { return FileName; }

		bool isOpen() const { return File != nullptr; }
		virtual bool isWriting();
		virtual bool isReading();
		virtual bool isBinary();

		virtual const long size();

		virtual char* readAll();

		virtual bool eof();

		virtual void seek(int offset,int origin = SEEK_SET);

		virtual int read(void * buf,int sz,int count = 1);
		virtual void readLine(char * buf,int sz);

		virtual unsigned int readByte();
		virtual float readFloat();
		virtual vector3 readVector3();
		virtual color4 readColor4();
		virtual vector3 readVectorf3();
		virtual color4 readColorf4();
		virtual stringc readString();

		virtual int write(void * buf,int sz);
		virtual int write(const char * buf);

		virtual int writeByte(unsigned int byte);
		virtual int writeFloat(float f);
		virtual int writeString(stringc str);
	

	};
}
}

#endif
