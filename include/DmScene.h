
#ifndef __DM_SCENE_INCLUDED__
#define __DM_SCENE_INCLUDED__
#include "DmEntity.h"
#include "DmCubeEntity.h"
#include "DmMeshEntity.h"
#include "DmLightEntity.h"
#include "DmCameraEntity.h"
#include "DmIMLoader.h"
#include "DmArray.h"
#include "DmList.h"
#include "DmSystem.h"
#include "DmColor.h"
#include "DmVector.h"
#include "DmResource.h"
#include "DmMaterialManager.h"

namespace demi
{
namespace scene
{

	class DmScene : public DmRoot, DmEntity
	{
	friend class DmEntity;
		void registerEntity(DmEntity* entity);
		void unregisterEntity(DmEntity* entity);
	protected:
		system::DmSystem*	_System;
		resource::DmResource* Resource;
		material::DmMaterialManager* MaterialManager;
		list<DmEntity*>		Entities;
		list<DmEntity*>::iterator EntitiesIter;
		array<IMLoader*>	MeshLoaders;
		list<SMesh>			Meshes;
		DmCameraEntity*		Camera;
		int					LastLight;
	public:

		//! Constructor
		DmScene(system::DmSystem* _system, resource::DmResource* resource,
			material::DmMaterialManager* mmgr);

		//! Destructor
		virtual ~DmScene();
		
		//! Add an Entity
		/**
		\param parent Parent Entity
		\param pos Position
		\param rot Rotation
		\param scl Scale
		\return DmEntity
		*/
		virtual DmEntity * addEntity(DmEntity* parent = 0,vector3 pos = vector3(0,0,0),
			vector3 rot = vector3(0,0,0),vector3 scl = vector3(0,0,0));

		virtual DmCubeEntity* addCubeEntity(DmEntity* parent = 0);

		virtual DmMeshEntity* addMeshEntity(SMesh* mesh, DmEntity* parent = 0);

		virtual DmMeshEntity* addMeshEntity(const char* filename, DmEntity* parent = 0);

		virtual DmLightEntity* addLightEntity(DmEntity* parent = 0, float radius = 300.0f, color4 color = color4());

		virtual DmCameraEntity* addCameraEntity(DmEntity* parent = 0, vector3 position = vector3(0,0,0),
			vector3 target = vector3(0,0,-10));

		virtual void addMLoader(IMLoader* loader);

		virtual SMesh* loadMesh(stringc filename);

		virtual void Render();

	};

}
}

#endif
