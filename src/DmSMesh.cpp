
#include "DmSMesh.h"

namespace demi
{
namespace scene
{

	void SMesh::draw()
	{
		for(int n = 0;n < Groups.size();n++)
			Groups[n]->draw();
	}

}
}
