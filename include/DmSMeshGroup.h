
#ifndef __DM_S_MESH_GROUP__
#define __DM_S_MESH_GROUP__
#include "DmArray.h"
#include "DmVertex.h"
#include "DmMaterial.h"

namespace demi
{
namespace scene
{

	class SMeshGroup
	{
	public:
		stringc					Name;
		array<vertex>			Vertices;
		material::DmMaterial	Material;
		glVertex*				VertexArray;
		glCoord*				TexCoordArray;
		glVertex*				NormalArray;
		bool					UseArrays;

		SMeshGroup() : VertexArray(nullptr), TexCoordArray(nullptr), NormalArray(nullptr), UseArrays(false) {}
		SMeshGroup(const SMeshGroup&) = delete;
		SMeshGroup& operator=(const SMeshGroup&) = delete;
		virtual ~SMeshGroup()
		{
			delete[] VertexArray;
			delete[] TexCoordArray;
			delete[] NormalArray;
		}

		virtual void fillArrays();

		virtual void draw();
	};

}
}

#endif
