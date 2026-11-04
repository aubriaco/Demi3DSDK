
#ifndef __DM_TEXTURE_INCLUDED__
#define __DM_TEXTURE_INCLUDED__

#include "DmRoot.h"

namespace demi
{
namespace resource
{
	enum E_TEXTURE_TYPE
	{
		ETT_GUESS = -1,
		ETT_BMP,
		ETT_TGA,
		ETT_PCX,
		ETT_COUNT
	};

	class DmTexture : public DmRoot
	{
	protected:
		GLuint Texture;
		int SizeX, SizeY;
		

		stringc Name;
	public:
		// Pixel data is borrowed for the duration of the upload.
		DmTexture(const void* data, int sizex, int sizey, E_TEXTURE_TYPE type = ETT_GUESS,
			stringc name = "");
		DmTexture(const DmTexture&) = delete;
		DmTexture& operator=(const DmTexture&) = delete;
		virtual ~DmTexture();

		virtual stringc getName() { return Name; }

		virtual GLuint getTexture();
	};
}
}


#endif
