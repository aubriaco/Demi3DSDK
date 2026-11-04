
#include "../include/Demi3D.h"

namespace demi
{
	DmDevice * createDemiDevice(int width,int height,int bits,bool fullscreen,const char *title)
	{
		SDemiDeviceParameters params{};
		params.Width = width;
		params.Height = height;
		params.Bits = bits;
		params.Fullscreen = fullscreen;
		params.Title = title;
		return (new DmDevice(params));
	}
}

