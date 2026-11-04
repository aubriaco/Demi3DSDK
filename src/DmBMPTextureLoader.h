#ifndef __DM_BMP_TEXTURE_LOADER__
#define __DM_BMP_TEXTURE_LOADER__
#include "DmITextureLoader.h"
#include <SDL.h>
#include <memory>
#include <vector>

namespace demi::resource
{
	class DmBMPTextureLoader : public ITextureLoader
	{
	public:
		DmTexture* load(const char* filename) override
		{
			using Surface = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;
			Surface bmp(SDL_LoadBMP(filename), SDL_FreeSurface);
			if (!bmp)
				return nullptr;
			Surface rgb(SDL_ConvertSurfaceFormat(bmp.get(), SDL_PIXELFORMAT_RGB24, 0), SDL_FreeSurface);
			if (!rgb)
				return nullptr;

			const auto rowSize = static_cast<size_t>(rgb->w) * 3;
			std::vector<unsigned char> pixels(rowSize * rgb->h);
			const auto* source = static_cast<const unsigned char*>(rgb->pixels);
			for (int y = 0; y < rgb->h; ++y)
				std::memcpy(pixels.data() + y * rowSize,
					source + static_cast<size_t>(rgb->h - 1 - y) * rgb->pitch, rowSize);
			return new DmTexture(pixels.data(), rgb->w, rgb->h, ETT_BMP, filename);
		}

		bool isLoadable(const char* filename) override
		{
			const char* extension = std::strrchr(filename, '.');
			return extension && SDL_strcasecmp(extension, ".bmp") == 0;
		}
	};
}

#endif
