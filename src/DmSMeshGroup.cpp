
#include "../include/DmSMeshGroup.h"
#include <memory>

namespace demi
{
namespace scene
{
	void SMeshGroup::fillArrays()
	{
		auto vertices = std::make_unique<glVertex[]>(Vertices.size());
		auto coordinates = std::make_unique<glCoord[]>(Vertices.size());
		auto normals = std::make_unique<glVertex[]>(Vertices.size());
		delete[] VertexArray;
		delete[] TexCoordArray;
		delete[] NormalArray;
		VertexArray = vertices.release();
		TexCoordArray = coordinates.release();
		NormalArray = normals.release();
		for(int n = 0;n < Vertices.size();n++)
		{
			VertexArray[n].x = Vertices[n].Vector.X;
			VertexArray[n].y = Vertices[n].Vector.Y;
			VertexArray[n].z = Vertices[n].Vector.Z;
			NormalArray[n].x = Vertices[n].Normal.X;
			NormalArray[n].y = Vertices[n].Normal.Y;
			NormalArray[n].z = Vertices[n].Normal.Z;
			TexCoordArray[n].u = Vertices[n].TexCoord.X;
			TexCoordArray[n].v = Vertices[n].TexCoord.Y;
		}
	}

	void SMeshGroup::draw()
	{
		Material.set();
		if(UseArrays)
		{
			glVertexPointer(3,GL_FLOAT,0,VertexArray);
			glTexCoordPointer(2,GL_FLOAT,0,TexCoordArray);
			glNormalPointer(GL_FLOAT,0,NormalArray);
			glDrawArrays(GL_TRIANGLES,0,Vertices.size());
		}
		else
		{
			glBegin(GL_TRIANGLES);
			for(int n = 0;n < Vertices.size();n++)
			{
				glTexCoord2d(Vertices[n].TexCoord.X,Vertices[n].TexCoord.Y);
				glNormal3f(Vertices[n].Normal.X,Vertices[n].Normal.Y,Vertices[n].Normal.Z);
				glVertex3f(Vertices[n].Vector.X,Vertices[n].Vector.Y,Vertices[n].Vector.Z);
			}
			glEnd();
		}
		Material.unset();
	}
}
}
