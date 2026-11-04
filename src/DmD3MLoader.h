
#ifndef __DM_D3M_LOADER_INCLUDED__
#define __DM_D3M_LOADER_INCLUDED__
#include "DmIMLoader.h"
#include "DmVertex.h"
#include "DmMaterial.h"
#include <memory>
#include <vector>

namespace demi
{
namespace scene
{

	class DmD3MLoader : public IMLoader
	{
	public:
		virtual bool isBinary()
		{
			return true;
		}

		virtual SMesh load(system::DmFileIO* file)
		{
			SMesh mesh;
			stringc header = file->readString();
			if(header != "D3M")
				return mesh;
			unsigned int groupCount = file->readByte();
			std::vector<std::unique_ptr<SMeshGroup>> groups;
			for(unsigned int n = 0;n < groupCount;n++)
			{
				auto group = std::make_unique<SMeshGroup>();
				unsigned int vertexCount = file->readByte();
				for(unsigned int x = 0;x < vertexCount;x++)
				{
					vertex vx;
					if (file->read(&vx, sizeof(vertex)) != 1) return mesh;
					group->Vertices.add(vx);
				}
				groups.push_back(std::move(group));
			}
			for (const auto& group : groups) mesh.Groups.add(group.get());
			for (auto& group : groups) group.release();
			return mesh;
		}

		virtual bool isLoadableFile(stringc filename)
		{
			if(filename.size() < 4) return false;
			if(filename.subString(filename.size()-4,4) == ".d3m")
				return true;
			else
				return false;
		}
	};

}
}

#endif
