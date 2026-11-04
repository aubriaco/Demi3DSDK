
#include "DmTexture.h"

namespace demi
{
namespace resource
{

	DmTexture::DmTexture(const void* data, int sizex, int sizey, E_TEXTURE_TYPE type,
		stringc name)
	{
		SizeX = sizex;
		SizeY = sizey;
		Name = name;
		glGenTextures(1, &Texture);
		glBindTexture(GL_TEXTURE_2D,Texture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		GLint alignment;
		glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, SizeX, SizeY, GL_RGB, GL_UNSIGNED_BYTE, data);
		glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
	}

	DmTexture::~DmTexture() { glDeleteTextures(1, &Texture); }

	GLuint DmTexture::getTexture()
	{
		return Texture;
	}

}
}
