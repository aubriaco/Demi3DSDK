
#ifndef __DM_VECTOR_INCLUDED__
#define __DM_VECTOR_INCLUDED__

#include "DmTypes.h"
#include "DmString.h"

namespace demi
{
	class vector3
	{
	protected:
		float *Vector;
	public:
		float X,Y,Z;
		vector3() {}
		vector3(float x,float y,float z) : X(x),Y(y),Z(z) {}

		void operator=(const vector3& other)
		{
			X = other.X;
			Y = other.Y;
			Z = other.Z;
		}

		bool operator==(const vector3& other)
		{
			return (X == other.X && Y == other.Y && Z == other.Z);
		}

		vector3 operator+(const vector3& other)
		{
			return vector3(X+other.X,Y+other.Y,Z+other.Z);
		}

		void operator+=(const vector3& other)
		{
			X += other.X;
			Y += other.Y;
			Z += other.Z;
		}

		stringc str(stringc delim = " ")
		{
			return stringc(stringc(X) + delim + stringc(Y) + delim + stringc(Z));
		}

		float* toGL()
		{
			Vector = new float[4];
			Vector[0] = X;
			Vector[1] = Y;
			Vector[2] = Z;
			Vector[3] = 1.0f;
			return Vector;
		}
	};
}

#endif
