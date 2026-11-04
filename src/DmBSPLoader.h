
#ifndef __DM_BSP_LOADER_INCLUDED__
#define __DM_BSP_LOADER_INCLUDED__
#include "DmIMLoader.h"
#include "DmBSPUtil.h"
#include <memory>
#include <vector>

namespace demi
{
namespace scene
{

	class DmBSPLoader : public IMLoader
	{
	public:

		virtual bool isBinary()
		{
			return true;
		}

		virtual bool isLoadableFile(stringc filename)
		{
			if(filename.size() < 4) return false;
			if(filename.subString(filename.size()-4,4) == ".bsp")
				return true;
			else
				return false;
		}

		virtual SMesh load(system::DmFileIO* file)
		{
			SMesh mesh;
			stQ3Header Header;
			stQ3FileLump Lumps[iMaxLumpsOffset];
			if (file->read(&Header, sizeof(Header)) != 1 ||
				std::memcmp(Header.bspID, "IBSP", sizeof(Header.bspID)) != 0 ||
				Header.version != 46 || file->read(Lumps, sizeof(Lumps)) != 1)
				return mesh;

			const auto size = file->size();
			const auto& vertices = Lumps[iVerticesOffset];
			const auto& faces = Lumps[iFacesOffset];
			const auto valid = [size](const stQ3FileLump& lump, size_t elementSize)
			{
				return lump.offset >= 0 && lump.length >= 0 && lump.offset <= size &&
					lump.length <= size - lump.offset && lump.length % elementSize == 0;
			};
			if (!valid(vertices, sizeof(stQ3Vertex)) || !valid(faces, sizeof(stQ3Face)))
				return mesh;

			const int m_totalVertices = vertices.length / sizeof(stQ3Vertex);
			const int m_totalFaces = faces.length / sizeof(stQ3Face);
			std::vector<stQ3Vertex> m_vertices(m_totalVertices);
			std::vector<stQ3Face> m_faces(m_totalFaces);
			file->seek(vertices.offset);
			if (file->read(m_vertices.data(), sizeof(stQ3Vertex), m_totalVertices) != m_totalVertices)
				return mesh;
			file->seek(faces.offset);
			if (file->read(m_faces.data(), sizeof(stQ3Face), m_totalFaces) != m_totalFaces)
				return mesh;

			for(int i = 0; i < m_totalVertices; i++)
			{
				float temp = m_vertices[i].vertex.y;
				m_vertices[i].vertex.y = m_vertices[i].vertex.z;
				m_vertices[i].vertex.z = -temp;
				m_vertices[i].texCoord.tv *= -1;

			}

			for(int i = 0; i < m_totalFaces; i++)
			{
				const auto* pFace = &m_faces[i];
				if (pFace->startVertexIndex < 0 || pFace->startVertexIndex > m_totalVertices ||
					pFace->totalVertices <= 0 || pFace->totalVertices > m_totalVertices - pFace->startVertexIndex)
					continue;
				auto group = std::make_unique<SMeshGroup>();
				for(int j = pFace->startVertexIndex;j < pFace->startVertexIndex + pFace->totalVertices;j++)
				{
					vector3 v3(m_vertices[j].vertex.x,m_vertices[j].vertex.y,
						m_vertices[j].vertex.z);
					vector3 tc(m_vertices[j].texCoord.tu,m_vertices[j].texCoord.tv,0);
					vector3 nm(m_vertices[j].normal.x,m_vertices[j].normal.y,
						m_vertices[j].normal.z);
					vector3 ltc(m_vertices[j].lightmapCoord.tu,m_vertices[j].lightmapCoord.tv,0);
					vertex vx(v3,tc,nm);
					vx.TexCoordX[0] = ltc;
					vx.UseExtraCoords = 1;
					group->Vertices.push_back(vx);
				}
				mesh.Groups.push_back(group.get());
				group.release();
			}


			return mesh;

		}
	};

}
}

#endif
