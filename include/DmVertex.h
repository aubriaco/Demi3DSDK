
#ifndef __DM_VERTEX_INCLUDED__
#define __DM_VERTEX_INCLUDED__
#include "DmVector.h"

namespace demi
{
	struct glVertex
	{
		float x,y,z;
	};

	struct glCoord
	{
		float u,v;
	};

	class vertex
	{
	public:
		vector3 Vector, TexCoord, Normal, TexCoordX[4];
		int UseExtraCoords;

		vertex() : Vector(), TexCoord(), Normal(), UseExtraCoords(0) {}
		vertex(vector3 vector, vector3 texcoord, vector3 normal)
			: Vector(vector), TexCoord(texcoord), Normal(normal), UseExtraCoords(0) {}

		~vertex() {}
	};
}

#endif
