
#ifndef __DM_I_EFFECT_INCLUDED__
#define __DM_I_EFFECT_INCLUDED__

namespace demi
{
namespace effect
{
	class IEffect
	{
	protected:
		bool Active;
	public:
		IEffect() : Active(false) {}
		virtual ~IEffect() {}

		virtual void activate() = 0;
		virtual void deactivate() = 0;

		virtual void Render() = 0;

		virtual void setActive(bool enabled) { Active = enabled; }

		virtual bool isActive() { return Active; }
	};

}
}

#endif
