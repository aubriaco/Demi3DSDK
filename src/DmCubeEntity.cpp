
#include "DmCubeEntity.h"

namespace demi
{
namespace scene
{


	DmCubeEntity::DmCubeEntity(DmEntity * parent)
		: DmEntity(parent)
	{
		Size = 5;
	}

	void DmCubeEntity::Render()
	{
		setupRender();
		Material.set();
#   define V(a,b,c) glTexCoord2f(a Size, b Size); glVertex3d( a Size, b Size, c Size );
#   define N(a,b,c) glNormal3d( a, b, c );

		glBegin( GL_QUADS );
			N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+);
			N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+);
			N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+);
			N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-);
			N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+);
			N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-);
		glEnd();

#   undef V
#   undef N
		Material.unset();
	}

}
}
