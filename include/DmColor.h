
#ifndef __DM_COLOR_INCLUDED__
#define __DM_COLOR_INCLUDED__
#include "DmTypes.h"

namespace demi
{
	class color4
	{
	protected:
		float *Color;
	public:
		float R, G, B, A;

		color4() : R(1), G(1), B(1), A(1) {}
		color4(float r, float g, float b) : R(r), G(g), B(b), A(1) {}
		color4(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {}

		void operator=(const color4 & other)
		{
			R = other.R;
			G = other.G;
			B = other.B;
			A = other.A;
		}

		bool operator==(const color4 & other)
		{
			return (R == other.R && G == other.G && B == other.B && A == other.A);
		}


		stringc str(stringc delim = " ")
		{
			return stringc(stringc(R) + delim + stringc(G) + delim + stringc(B) + delim
				+ stringc(A));
		}

		float* toGL()
		{
			Color = new float[4];
			Color[0] = R;
			Color[1] = G;
			Color[2] = B;
			Color[3] = A;
			return Color;
		}
	};
}


#endif
