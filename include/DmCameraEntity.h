
#ifndef __DM_CAMERA_ENTITY_INCLUDED__
#define __DM_CAMERA_ENTITY_INCLUDED__
#include "DmEntity.h"

namespace demi
{
namespace scene
{

	class DmCameraEntity : public DmEntity
	{
	protected:
		vector3 Target;
		matrix4 View;
	public:
		DmCameraEntity(DmEntity* parent, vector3 position, vector3 target);

		virtual void setTarget(vector3 target);
		virtual vector3 getTarget();

		virtual void update();
	};

}
}

#endif
