
#ifndef __DM_I_BLEND_INCLUDED__
#define __DM_I_BLEND_INCLUDED__

namespace demi
{
namespace material
{
	enum E_BLEND_TYPE
	{
		EBT_SOLID,
		EBT_ALPHA,
		EBT_ADD_COLOR,
		EBT_COUNT
	};

	class IBlend
	{
	public:
		virtual void set() = 0;
		virtual void unset() = 0;
	};

}
}

#endif
