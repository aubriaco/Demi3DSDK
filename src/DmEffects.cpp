
#include "../include/DmEffects.h"

namespace demi
{
namespace effect
{

	DmEffects::DmEffects()
	{
		addEffect(new DmBloomEffect());
	}

	DmEffects::~DmEffects()
	{
		for(int n = 0;n < Effects.size();n++)
		{
			if(Effects[n])
				delete Effects[n];
		}
		Effects.clear();
	}

	void DmEffects::enableEffect(int id)
	{
		if(id >= Effects.size()) return;
		Effects[id]->setActive(true);
	}

	void DmEffects::disableEffect(int id)
	{
		if(id >= Effects.size()) return;
		Effects[id]->setActive(false);
	}

	int DmEffects::addEffect(IEffect* effect)
	{
		Effects.add(effect);
		return Effects.size()-1;
	}

	void DmEffects::Render()
	{
		for(int n = 0;n < Effects.size();n++)
		{
			if(Effects[n])
				if(Effects[n]->isActive())
					Effects[n]->Render();
		}
	}


}
}
