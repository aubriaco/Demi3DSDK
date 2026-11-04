
#ifndef __DM_GEM_LOADER_INCLUDED__
#define __DM_GEM_LOADER_INCLUDED__
#include "DmIMLoader.h"
#include "DmMaterialScript.h"

namespace demi
{
namespace scene
{

	class DmGEMLoader : public IMLoader
	{
	public:
		virtual bool isBinary()
		{
			return false;
		}

		virtual bool isLoadableFile(stringc filename)
		{
			if(filename.size() < 4) return false;
			if(filename.subString(filename.size()-4,4) == ".gem")
				return true;
			else
				return false;
		}

		virtual SMesh load(system::DmFileIO* file)
		{
			SMesh mesh;
			char buf[256];
			file->readLine(buf,255);
			if(strncmp(buf,"gem",3) == 0)
			{
				file->readLine(buf,255);
				SMeshGroup* group = 0;
				stringc d3mFile = file->getFileName();
				d3mFile = d3mFile.subString(0,d3mFile.size()-4);
				d3mFile += ".mts";
				material::IMaterialScript* mScript = MaterialManager->loadScript(d3mFile.c_str());
				while(!file->eof())
				{
					file->readLine(buf,255);
					if(strncmp(buf,"#",1) == 0)
						continue;
					if(strncmp(buf,"g ",2) == 0)
					{
						if(group)
							mesh.Groups.push_back(group);
						group = new SMeshGroup();
						stringc l = buf;
						group->Name = l.subString(2,l.size()-2);
						group->Name.trim();
						if(mScript)
							group->Material.setMaterialScript(mScript,group->Name);
						continue;
					}
					if(strncmp(buf,"v ",2) == 0)
					{
						vertex v;
						if (group && sscanf(buf,"%*c %f %f %f,%f %f",&v.Vector.X,&v.Vector.Y,&v.Vector.Z,
							&v.TexCoord.X,&v.TexCoord.Y) == 5)
							group->Vertices.push_back(v);
					}
				}
				if (group) mesh.Groups.push_back(group);
			}
			return mesh;
		}
	};

}
}

#endif
