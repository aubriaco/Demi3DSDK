
#include "../include/DmCameraEntity.h"

namespace demi
{
namespace scene
{

	DmCameraEntity::DmCameraEntity(DmEntity* parent, vector3 position, vector3 target)
		: DmEntity(parent,position), Target(target)
	{ }

	void DmCameraEntity::setTarget(vector3 target)
	{
		Target = target;
	}

	vector3 DmCameraEntity::getTarget()
	{
		return Target;
	}

	void DmCameraEntity::update()
	{
		gluLookAt(Position.X,Position.Y,Position.Z,
			Target.X,Target.Y,Target.Z,0,1,0);

		/*
		View(0,0) = Position.X;
		View(1,0) = Position.Y;
		View(2,0) = Position.Z;

		View(0,1) = 0;
		View(1,1) = 1;
		View(2,1) = 0;

		View(0,2) = -Target.X;
		View(1,2) = -Target.Y;
		View(2,2) = -Target.Z;

		glMultMatrixf(View.M);
		*/
	}

}
}
