
#ifndef __DM_EFFECTS_INCLUDED__
#define __DM_EFFECTS_INCLUDED__
#include "DmRoot.h"
#include "DmIEffect.h"
#include "DmBloomEffect.h"

namespace demi
{
namespace effect
{

	class DmEffects : public DmRoot
	{
	protected:
		array<IEffect*> Effects;
	public:
		DmEffects();
		virtual ~DmEffects();

		virtual void enableEffect(int id);
		virtual void disableEffect(int id);

		virtual int addEffect(IEffect* effect);

		virtual void Render();
	};

}
}

#endif
