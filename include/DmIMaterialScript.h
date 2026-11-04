
#ifndef __DM_I_MATERIAL_SCRIPT__
#define __DM_I_MATERIAL_SCRIPT__

namespace demi
{
namespace material
{

	class IMaterialScript
	{
	public:
		virtual void set() = 0;
		virtual void unset() = 0;

		virtual void setSection(stringc name) = 0;
	};

}
}

#endif
