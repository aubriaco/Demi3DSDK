
#ifndef __DM_MATRIX_INCLUDED__
#define __DM_MATRIX_INCLUDED__

namespace demi
{
	class matrix4
	{
	public:
		float M[16];

		matrix4() { identity(); }
		matrix4(float m[16])
		{
			for(int n = 0;n < 16;n++)
				M[n] = m[n];
		}

		float & operator()(int row, int col) { return M[col*4+row]; }
		float & operator()(int index) { return M[index]; }

		virtual void identity()
		{
			M[0]=1.0f;M[1]=0.0f;M[2]=0.0f;M[3]=0.0f;
			M[4]=0.0f;M[5]=1.0f;M[6]=0.0f;M[7]=0.0f;
			M[8]=0.0f;M[9]=0.0f;M[10]=1.0f;M[11]=0.0f;
			M[12]=0.0f;M[13]=0.0f;M[14]=0.0f;M[15]=1.0f;
		}
	};
}

#endif
