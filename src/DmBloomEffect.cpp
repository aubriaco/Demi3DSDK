
#include "DmBloomEffect.h"
#include "DmRoot.h"
#include "math.h"

namespace demi
{
namespace effect
{
	unsigned int DmBloomEffect::emptyTexture()
	{
		GLuint txtnumber;											// Texture ID
		unsigned int* data;											// Stored Data

		// Create Storage Space For Texture Data (128x128x4)
		data = (unsigned int*)new GLuint[((128 * 128)* 4 * sizeof(unsigned int))];
		memset(data, 0,((128 * 128)* 4 * sizeof(unsigned int)));	// Clear Storage Memory

		glGenTextures(1, &txtnumber);								// Create 1 Texture
		glBindTexture(GL_TEXTURE_2D, txtnumber);					// Bind The Texture
		glTexImage2D(GL_TEXTURE_2D, 0, 4, 128, 128, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, data);						// Build Texture Using Information In data
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		delete [] data;												// Release data

		return txtnumber;
	}

	void DmBloomEffect::reduceToUnit(float vector[3])								// Reduces A Normal Vector (3 Coordinates)
	{																// To A Unit Normal Vector With A Length Of One.
		float length;												// Holds Unit Length
		// Calculates The Length Of The Vector
		length = (float)sqrt((vector[0]*vector[0]) + (vector[1]*vector[1]) + (vector[2]*vector[2]));

		if(length == 0.0f)											// Prevents Divide By 0 Error By Providing
			length = 1.0f;											// An Acceptable Value For Vectors To Close To 0.

		vector[0] /= length;										// Dividing Each Element By
		vector[1] /= length;										// The Length Results In A
		vector[2] /= length;										// Unit Normal Vector.
	}

	void DmBloomEffect::calcNormal(float v[3][3], float out[3])					// Calculates Normal For A Quad Using 3 Points
	{
		float v1[3],v2[3];											// Vector 1 (x,y,z) & Vector 2 (x,y,z)
		static const int x = 0;										// Define X Coord
		static const int y = 1;										// Define Y Coord
		static const int z = 2;										// Define Z Coord

		// Finds The Vector Between 2 Points By Subtracting
		// The x,y,z Coordinates From One Point To Another.

		// Calculate The Vector From Point 1 To Point 0
		v1[x] = v[0][x] - v[1][x];									// Vector 1.x=Vertex[0].x-Vertex[1].x
		v1[y] = v[0][y] - v[1][y];									// Vector 1.y=Vertex[0].y-Vertex[1].y
		v1[z] = v[0][z] - v[1][z];									// Vector 1.z=Vertex[0].y-Vertex[1].z
		// Calculate The Vector From Point 2 To Point 1
		v2[x] = v[1][x] - v[2][x];									// Vector 2.x=Vertex[0].x-Vertex[1].x
		v2[y] = v[1][y] - v[2][y];									// Vector 2.y=Vertex[0].y-Vertex[1].y
		v2[z] = v[1][z] - v[2][z];									// Vector 2.z=Vertex[0].z-Vertex[1].z
		// Compute The Cross Product To Give Us A Surface Normal
		out[x] = v1[y]*v2[z] - v1[z]*v2[y];							// Cross Product For Y - Z
		out[y] = v1[z]*v2[x] - v1[x]*v2[z];							// Cross Product For X - Z
		out[z] = v1[x]*v2[y] - v1[y]*v2[x];							// Cross Product For X - Y

		reduceToUnit(out);											// Normalize The Vectors
	}

	void DmBloomEffect::processHelix()
	{
		GLfloat x;													// Helix x Coordinate
		GLfloat y;													// Helix y Coordinate
		GLfloat z;													// Helix z Coordinate
		GLfloat phi;												// Angle
		GLfloat theta;												// Angle
		GLfloat v,u;												// Angles
		GLfloat r;													// Radius Of Twist
		int twists = 5;												// 5 Twists

		GLfloat glfMaterialColor[]={0.4f,0.2f,0.8f,1.0f};			// Set The Material Color
		GLfloat specular[]={1.0f,1.0f,1.0f,1.0f};					// Sets Up Specular Lighting

		glLoadIdentity();											// Reset The Modelview Matrix
		gluLookAt(0, 5, 50, 0, 0, 0, 0, 1, 0);						// Eye Position (0,5,50) Center Of Scene (0,0,0), Up On Y Axis

		glPushMatrix();												// Push The Modelview Matrix

		glTranslatef(0,0,-50);										// Translate 50 Units Into The Screen
		glRotatef(angle/2.0f,1,0,0);								// Rotate By angle/2 On The X-Axis
		glRotatef(angle/3.0f,0,1,0);								// Rotate By angle/3 On The Y-Axis

		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,glfMaterialColor);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
		
		r=1.5f;														// Radius

		glBegin(GL_QUADS);											// Begin Drawing Quads
		for(phi=0; phi <= 360; phi+=20.0)							// 360 Degrees In Steps Of 20
		{
			for(theta=0; theta<=360*twists; theta+=20.0)			// 360 Degrees * Number Of Twists In Steps Of 20
			{
				v=(phi/180.0f*3.142f);								// Calculate Angle Of First Point	(  0 )
				u=(theta/180.0f*3.142f);							// Calculate Angle Of First Point	(  0 )

				x=float(cos(u)*(2.0f+cos(v) ))*r;					// Calculate x Position (1st Point)
				y=float(sin(u)*(2.0f+cos(v) ))*r;					// Calculate y Position (1st Point)
				z=float((( u-(2.0f*3.142f)) + sin(v) ) * r);		// Calculate z Position (1st Point)

				vertexes[0][0]=x;									// Set x Value Of First Vertex
				vertexes[0][1]=y;									// Set y Value Of First Vertex
				vertexes[0][2]=z;									// Set z Value Of First Vertex

				v=(phi/180.0f*3.142f);								// Calculate Angle Of Second Point	(  0 )
				u=((theta+20)/180.0f*3.142f);						// Calculate Angle Of Second Point	( 20 )

				x=float(cos(u)*(2.0f+cos(v) ))*r;					// Calculate x Position (2nd Point)
				y=float(sin(u)*(2.0f+cos(v) ))*r;					// Calculate y Position (2nd Point)
				z=float((( u-(2.0f*3.142f)) + sin(v) ) * r);		// Calculate z Position (2nd Point)

				vertexes[1][0]=x;									// Set x Value Of Second Vertex
				vertexes[1][1]=y;									// Set y Value Of Second Vertex
				vertexes[1][2]=z;									// Set z Value Of Second Vertex

				v=((phi+20)/180.0f*3.142f);							// Calculate Angle Of Third Point	( 20 )
				u=((theta+20)/180.0f*3.142f);						// Calculate Angle Of Third Point	( 20 )

				x=float(cos(u)*(2.0f+cos(v) ))*r;					// Calculate x Position (3rd Point)
				y=float(sin(u)*(2.0f+cos(v) ))*r;					// Calculate y Position (3rd Point)
				z=float((( u-(2.0f*3.142f)) + sin(v) ) * r);		// Calculate z Position (3rd Point)

				vertexes[2][0]=x;									// Set x Value Of Third Vertex
				vertexes[2][1]=y;									// Set y Value Of Third Vertex
				vertexes[2][2]=z;									// Set z Value Of Third Vertex

				v=((phi+20)/180.0f*3.142f);							// Calculate Angle Of Fourth Point	( 20 )
				u=((theta)/180.0f*3.142f);							// Calculate Angle Of Fourth Point	(  0 )

				x=float(cos(u)*(2.0f+cos(v) ))*r;					// Calculate x Position (4th Point)
				y=float(sin(u)*(2.0f+cos(v) ))*r;					// Calculate y Position (4th Point)
				z=float((( u-(2.0f*3.142f)) + sin(v) ) * r);		// Calculate z Position (4th Point)

				vertexes[3][0]=x;									// Set x Value Of Fourth Vertex
				vertexes[3][1]=y;									// Set y Value Of Fourth Vertex
				vertexes[3][2]=z;									// Set z Value Of Fourth Vertex

				calcNormal(vertexes,normal);						// Calculate The Quad Normal

				glNormal3f(normal[0],normal[1],normal[2]);			// Set The Normal

				// Render The Quad
				glVertex3f(vertexes[0][0],vertexes[0][1],vertexes[0][2]);
				glVertex3f(vertexes[1][0],vertexes[1][1],vertexes[1][2]);
				glVertex3f(vertexes[2][0],vertexes[2][1],vertexes[2][2]);
				glVertex3f(vertexes[3][0],vertexes[3][1],vertexes[3][2]);
			}
		}
		glEnd();													// Done Rendering Quads
		
		glPopMatrix();
	}

	void DmBloomEffect::renderToTexture()											// Renders To A Texture
	{
		glViewport(0,0,128,128);									// Set Our Viewport (Match Texture Size)

		//processHelix();												// Render The Helix
		// RENDER SCENE HERE

		glBindTexture(GL_TEXTURE_2D,BlurTexture);					// Bind To The Blur Texture

		// Copy Our ViewPort To The Blur Texture (From 0,0 To 128,128... No Border)
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, 128, 128, 0);

		glClearColor(0.0f, 0.0f, 0.5f, 0.5);						// Set The Clear Color To Medium Blue
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear The Screen And Depth Buffer

		glViewport(0 , 0,640 ,480);									// Set Viewport (0,0 to 640x480)
	}

	void DmBloomEffect::viewOrtho()												// Set Up An Ortho View
	{
		glMatrixMode(GL_PROJECTION);								// Select Projection
		glPushMatrix();												// Push The Matrix
		glLoadIdentity();											// Reset The Matrix
		glOrtho( 0, 640 , 480 , 0, -1, 1 );							// Select Ortho Mode (640x480)
		glMatrixMode(GL_MODELVIEW);									// Select Modelview Matrix
		glPushMatrix();												// Push The Matrix
		glLoadIdentity();											// Reset The Matrix
	}

	void DmBloomEffect::viewPerspective()											// Set Up A Perspective View
	{
		glMatrixMode( GL_PROJECTION );								// Select Projection
		glPopMatrix();												// Pop The Matrix
		glMatrixMode( GL_MODELVIEW );								// Select Modelview
		glPopMatrix();												// Pop The Matrix
	}

	void DmBloomEffect::drawBlur(int times, float inc)								// Draw The Blurred Image
	{
		float spost = 0.0f;											// Starting Texture Coordinate Offset
		float alphainc = 0.9f / times;								// Fade Speed For Alpha Blending
		float alpha = 0.2f;											// Starting Alpha Value

		// Disable AutoTexture Coordinates
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);

		glEnable(GL_TEXTURE_2D);									// Enable 2D Texture Mapping
		glDisable(GL_DEPTH_TEST);									// Disable Depth Testing
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);							// Set Blending Mode
		glEnable(GL_BLEND);											// Enable Blending
		glBindTexture(GL_TEXTURE_2D,BlurTexture);					// Bind To The Blur Texture
		viewOrtho();												// Switch To An Ortho View

		alphainc = alpha / times;									// alphainc=0.2f / Times To Render Blur

		glBegin(GL_QUADS);											// Begin Drawing Quads
			for (int num = 0;num < times;num++)						// Number Of Times To Render Blur
			{
				glColor4f(1.0f, 1.0f, 1.0f, alpha);					// Set The Alpha Value (Starts At 0.2)
				glTexCoord2f(0+spost,1-spost);						// Texture Coordinate	( 0, 1 )
				glVertex2f(0,0);									// First Vertex		(   0,   0 )

				glTexCoord2f(0+spost,0+spost);						// Texture Coordinate	( 0, 0 )
				glVertex2f(0,480);									// Second Vertex	(   0, 480 )

				glTexCoord2f(1-spost,0+spost);						// Texture Coordinate	( 1, 0 )
				glVertex2f(640,480);								// Third Vertex		( 640, 480 )

				glTexCoord2f(1-spost,1-spost);						// Texture Coordinate	( 1, 1 )
				glVertex2f(640,0);									// Fourth Vertex	( 640,   0 )

				spost += inc;										// Gradually Increase spost (Zooming Closer To Texture Center)
				alpha = alpha - alphainc;							// Gradually Decrease alpha (Gradually Fading Image Out)
			}
		glEnd();													// Done Drawing Quads

		viewPerspective();											// Switch To A Perspective View

		glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
		glDisable(GL_TEXTURE_2D);									// Disable 2D Texture Mapping
		glDisable(GL_BLEND);										// Disable Blending
		glBindTexture(GL_TEXTURE_2D,0);								// Unbind The Blur Texture
	}

	void DmBloomEffect::Render()
	{
		renderToTexture();
		drawBlur(25,0.02f);
	}

}
}
