
#include "../include/DmFileIO.h"
#include <limits>

namespace demi
{
namespace system
{
	DmFileIO::DmFileIO(stringc filename,stringc access)
	{
		FileName = filename;
		Access = access;
		File = fopen(FileName.c_str(),Access.c_str());
	}

	DmFileIO::~DmFileIO()
	{
		if (File) fclose(File);
	}

	const long DmFileIO::size()
	{
		if (!File) return -1;
		long pos = ftell(File);
		if (pos < 0 || fseek(File, 0L, SEEK_END) != 0) return -1;
		long size	= ftell(File);
		if (fseek(File, pos, SEEK_SET) != 0) return -1;
		return size;
	}

	char* DmFileIO::readAll()
	{
		if (!isReading()) return nullptr;
		const long length = size();
		if (length < 0 || length >= std::numeric_limits<int>::max()) return nullptr;
		char* buf = new char[length + 1];
		buf[fread(buf, 1, length, File)] = 0;
		return buf;
	}

	bool DmFileIO::eof()
	{
		return !File || feof(File) || ferror(File);
	}

	void DmFileIO::seek(int offset,int origin)
	{
		if (File) fseek(File,offset,origin);
	}

	int DmFileIO::read(void * buf,int sz,int count)
	{
		if (!isReading() || sz < 0 || count < 0) return -1;
		if (sz == 0 || count == 0) return 0;
		return fread(buf,sz,count,File);
	}

	void DmFileIO::readLine(char * buf,int sz)
	{
		if (!buf || sz <= 0) return;
		if (!isReading() || !fgets(buf,sz,File)) buf[0] = 0;
	}

	unsigned int DmFileIO::readByte()
	{
		int ret = 0;
		read(&ret,sizeof(ret));
		return ret;
	}

	float DmFileIO::readFloat()
	{
		float ret = 0;
		read(&ret,sizeof(ret));
		return ret;
	}

	vector3 DmFileIO::readVector3()
	{
		vector3 v;
		read(&v,sizeof(vector3));
		return v;
	}

	color4 DmFileIO::readColor4()
	{
		color4 c;
		read(&c,sizeof(color4));
		return c;
	}

	vector3 DmFileIO::readVectorf3()
	{
		vector3 v;
		v.X = readFloat();
		v.Y = readFloat();
		v.Z = readFloat();
		return v;
	}

	color4 DmFileIO::readColorf4()
	{
		color4 c;
		c.R = readFloat();
		c.G = readFloat();
		c.B = readFloat();
		c.A = readFloat();
		return c;
	}

	stringc DmFileIO::readString()
	{
		stringc str = "";
		char c = (char)readByte();
		while(c != 0)
		{
			str += c;
			c = (char)readByte();
		}
		return str;
	}

	int DmFileIO::write(void * buf,int sz)
	{
		if(!isWriting()) return -1;
		return fwrite(buf,sz,1,File);
	}

	int DmFileIO::write(const char * buf)
	{
		if(!isWriting()) return -1;
		return fwrite(buf,strlen(buf),1,File);
	}

	int DmFileIO::writeByte(unsigned int byte)
	{
		if(!isWriting()) return -1;
		return fwrite(&byte,sizeof(byte),1,File);
	}

	int DmFileIO::writeFloat(float f)
	{
		if(!isWriting()) return -1;
		return fwrite(&f,sizeof(f),1,File);
	}

	int DmFileIO::writeString(stringc str)
	{
		if(!isWriting()) return -1;
		return fwrite(str.c_str(),str.size(),1,File);
	}

	bool DmFileIO::isReading()
	{
		return File && Access.findFirst('r') > -1;
	}

	bool DmFileIO::isWriting()
	{
		return File && (Access.findFirst('w') > -1 || Access.findFirst('a') > -1);
	}

	bool DmFileIO::isBinary()
	{
		return (Access.findFirst('b') > -1);
	}

}
}
