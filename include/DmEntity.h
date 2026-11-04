
#ifndef __DM_ENTITY_INCLUDED__
#define __DM_ENTITY_INCLUDED__

#include "DmRoot.h"
#include "DmTexture.h"
#include "DmSMesh.h"
#include "DmList.h"
#include "DmMatrix.h"

namespace demi
{
namespace scene
{
	enum E_ENTITY_TYPE
	{
		EENT_DEFAULT,
		EENT_LIGHT,
		EENT_MESH,
		EENT_TEST,
		EENT_COUNT
	};

	class DmScene;

	class DmEntity
	{
	friend class DmScene;
		DmScene* SceneOwner = nullptr;
	protected:
		cch*					EntityName;
		DmEntity*				Parent;
		list<DmEntity*>			Children;
		vector3					Position;
		vector3					Rotation;
		vector3					Scale;
		vector3					AbsolutePosition;
		vector3					AbsoluteRotation;
		E_ENTITY_TYPE			EntityType;

		/** Translate to Position */
		virtual void setupRender();
		void detachFromParent();

	public:

		//! Constructor
		DmEntity();

		//! Constructor
		DmEntity(DmEntity* parent,vector3 pos = vector3(0,0,0),vector3 rot = vector3(0,0,0),vector3 scl = vector3(0,0,0));
		
		//! Destructor
		virtual ~DmEntity();

		//! Add Child
		/**
		\param entity Entity to attach
		*/
		virtual void addChild(DmEntity* entity);

		//! Get All Children
		/*
		\return List of children.
		*/
		virtual list<DmEntity*> & getChildren();


		//! Remove Child
		/**
		\param entity Target Entity
		*/
		virtual void removeChild(DmEntity* entity);

		//! Remove all Children
		virtual void removeAllChildren();

		//! Set Entity Parent
		virtual void setParent(DmEntity* entity);

		/** Set Position
		\param pos Position vector
		*/
		virtual void setPosition(vector3 pos);

		/** Get Entity Position
		\return Entity Position
		*/
		virtual vector3 getPosition();

		/** Set Entity Rotation
		\param rot Rotation vector
		*/
		virtual void setRotation(vector3 rot);

		/** Get Entity Rotation
		\return Entity Rotation
		*/
		virtual vector3 getRotation();

		/** Get Absolute Position
		\return Absolute Postion
		*/
		virtual vector3 getAbsolutePosition();

		/** Get Absolute Rotation
		\return Absolute Rotation
		*/
		virtual vector3 getAbsoluteRotation();

		/** Update Absolute Vectors */
		virtual void updateAbsoluteTranslation();

		/** PreRender */
		virtual void PreRender() {}

		/** Render */
		virtual void Render() {}
	};
}
}

#endif
