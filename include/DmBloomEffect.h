
#ifndef __DM_BLOOM_EFFECT_ENABLED__
#define __DM_BLOOM_EFFECT_ENABLED__
#include "DmIEffect.h"

namespace demi
{
namespace effect
{

	class DmBloomEffect : public IEffect
	{
	protected:
		float			angle;												// Used To Rotate The Helix
		float			vertexes[4][3];										// Holds Float Info For 4 Sets Of Vertices
		float			normal[3];											// An Array To Store The Normal Data
		unsigned int	BlurTexture;
	public:
		DmBloomEffect() {}
		virtual ~DmBloomEffect() {}

		virtual void activate() {}
		virtual void deactivate() {}

		virtual unsigned int emptyTexture();
		virtual void reduceToUnit(float vector[3]);
		virtual void calcNormal(float v[3][3], float out[3]);

		virtual void processHelix();

		virtual void renderToTexture();

		virtual void drawBlur(int times, float inc);

		virtual void viewOrtho();
		virtual void viewPerspective();

		virtual void Render();
	};
}
}

#endif
