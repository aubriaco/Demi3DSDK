
#include "../include/DmScene.h"
#include "DmDefaultBlends.h"
#include "DmOBJLoader.h"
#include "DmD3MLoader.h"
#include "DmBSPLoader.h"
#include "DmGEMLoader.h"
#include <memory>

namespace demi
{
namespace scene
{

	DmScene::DmScene(system::DmSystem* _system, resource::DmResource* resource,
		material::DmMaterialManager* mmgr)
		: DmEntity(), _System(_system), Resource(resource), MaterialManager(mmgr),
		Camera(0), LastLight(0)
	{
		addMLoader(new DmD3MLoader());
		addMLoader(new DmBSPLoader());
		addMLoader(new DmOBJLoader());
		addMLoader(new DmGEMLoader());
		for(int n = 0;n < MeshLoaders.size();n++)
			MeshLoaders[n]->construct(_system,resource,mmgr);
	}

	DmScene::~DmScene()
	{
		while (!Entities.isEmpty())
			delete *Entities.begin();
		for (auto mesh = Meshes.begin(); mesh != Meshes.end(); ++mesh)
			for (unsigned int i = 0; i < (*mesh).Groups.size(); ++i)
				delete (*mesh).Groups[i];
		Meshes.clear();
		for (unsigned int i = 0; i < MeshLoaders.size(); ++i)
			delete MeshLoaders[i];
	}

	void DmScene::registerEntity(DmEntity* entity)
	{
		Entities.add(entity);
		entity->SceneOwner = this;
	}

	void DmScene::unregisterEntity(DmEntity* entity)
	{
		if (Camera == entity)
			Camera = nullptr;
		for (auto it = Entities.begin(); it != Entities.end(); ++it)
			if (*it == entity)
			{
				Entities.remove(it);
				break;
			}
	}

	DmEntity* DmScene::addEntity(DmEntity* parent,vector3 pos,vector3 rot,vector3 scl)
	{
		if(!parent)
			parent = this;
		DmEntity* entity = new DmEntity(parent,pos,rot,scl);
		registerEntity(entity);
		return entity;
	}

	DmCubeEntity* DmScene::addCubeEntity(DmEntity* parent)
	{
		if(!parent)
			parent = this;
		DmCubeEntity* entity = new DmCubeEntity(parent);
		registerEntity(entity);
		return entity;
	}

	DmMeshEntity* DmScene::addMeshEntity(SMesh* mesh, DmEntity* parent)
	{
		if(!parent)
			parent = this;
		DmMeshEntity* entity = new DmMeshEntity(parent,mesh);
		registerEntity(entity);
		return entity;
	}

	DmMeshEntity* DmScene::addMeshEntity(const char* filename, DmEntity* parent)
	{
		if(!parent)
			parent = this;
		DmMeshEntity* entity = new DmMeshEntity(parent,loadMesh(filename));
		registerEntity(entity);
		return entity;
	}

	DmLightEntity* DmScene::addLightEntity(DmEntity* parent, float radius, color4 color)
	{
		if(!parent)
			parent = this;
		DmLightEntity* entity = new DmLightEntity(parent, (GL_LIGHT0 + LastLight), radius);
		LastLight++;
		registerEntity(entity);
		return entity;
	}

	DmCameraEntity* DmScene::addCameraEntity(DmEntity* parent, vector3 position,
		vector3 target)
	{
		if(!parent)
			parent = this;
		DmCameraEntity* entity = new DmCameraEntity(parent,position,target);
		registerEntity(entity);
		Camera = entity;
		return entity;
	}

	void DmScene::addMLoader(IMLoader* loader)
	{
		MeshLoaders.add(loader);
	}

	SMesh* DmScene::loadMesh(stringc filename)
	{
		for(int n = 0;n < MeshLoaders.size();n++)
		{
			if(MeshLoaders[n]->isLoadableFile(filename))
			{
				stringc access = "r";
				if(MeshLoaders[n]->isBinary())
					access += "b";
				std::unique_ptr<system::DmFileIO> file(_System->createFileIO(filename,access));
				if (!file)
					return nullptr;
				auto mesh = MeshLoaders[n]->load(file.get());
				if (!mesh.Groups.size())
					return nullptr;
				try
				{
					Meshes.add(mesh);
				}
				catch (...)
				{
					for (unsigned int i = 0; i < mesh.Groups.size(); ++i)
						delete mesh.Groups[i];
					throw;
				}
				return &(*Meshes.getLast());
			}
		}
		return 0;
	}

	void DmScene::Render()
	{
		for(EntitiesIter = Entities.begin();EntitiesIter != Entities.end();++EntitiesIter)
		{
			glLoadIdentity();
			if(Camera) Camera->update();
			(*EntitiesIter)->PreRender();
		}
		for(EntitiesIter = Entities.begin();EntitiesIter != Entities.end();++EntitiesIter)
		{
			glLoadIdentity();
			if(Camera) Camera->update();
			(*EntitiesIter)->Render();
		}
	}

}
}