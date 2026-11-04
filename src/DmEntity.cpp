
#include "DmScene.h"

namespace demi
{
namespace scene
{

	DmEntity::DmEntity()
	{
		Parent		= 0;
		Position	= vector3(0,0,0);
		Rotation	= vector3(0,0,0);
		Scale		= vector3(0,0,0);
		EntityType	= EENT_DEFAULT;
		updateAbsoluteTranslation();
	}

	DmEntity::DmEntity(DmEntity* parent,vector3 pos,vector3 rot,vector3 scl) : Parent(nullptr)
	{
		Position	= pos;
		Rotation	= rot;
		Scale		= scl;
		EntityType	= EENT_DEFAULT;
		setParent(parent);
		updateAbsoluteTranslation();
	}

	DmEntity::~DmEntity()
	{
		if (SceneOwner) SceneOwner->unregisterEntity(this);
		detachFromParent();
		removeAllChildren();
	}

	void DmEntity::addChild(DmEntity* entity)
	{
		if (entity) entity->setParent(this);
	}

	list<DmEntity*> & DmEntity::getChildren()
	{
		return Children;
	}

	void DmEntity::removeChild(DmEntity* entity)
	{
		list<DmEntity*>::iterator it;
		for(it = Children.begin();it != Children.end();++it)
			if((*it) == entity)
			{
				Children.remove(it);
				entity->Parent = nullptr;
				delete entity;
				return;
			}
	}

	void DmEntity::removeAllChildren()
	{
		while (!Children.isEmpty())
			removeChild(*Children.begin());
	}

	void DmEntity::setParent(DmEntity* entity)
	{
		if (Parent == entity)
			return;
		for (auto* ancestor = entity; ancestor; ancestor = ancestor->Parent)
			if (ancestor == this)
				return;
		if (entity)
			entity->Children.add(this);
		detachFromParent();
		Parent = entity;
		updateAbsoluteTranslation();
	}

	void DmEntity::detachFromParent()
	{
		if (!Parent)
			return;
		auto& siblings = Parent->Children;
		for (auto it = siblings.begin(); it != siblings.end(); ++it)
		{
			if (*it == this)
			{
				siblings.remove(it);
				break;
			}
		}
		Parent = nullptr;
	}

	void DmEntity::setPosition(vector3 pos)
	{
		Position = pos;
		updateAbsoluteTranslation();
	}

	vector3 DmEntity::getPosition()
	{
		return Position;
	}

	void DmEntity::setRotation(vector3 rot)
	{
		Rotation = rot;
		updateAbsoluteTranslation();
	}

	vector3 DmEntity::getRotation()
	{
		return Rotation;
	}

	vector3 DmEntity::getAbsolutePosition()
	{
		return AbsolutePosition;
	}

	vector3 DmEntity::getAbsoluteRotation()
	{
		return AbsoluteRotation;
	}

	void DmEntity::updateAbsoluteTranslation()
	{
		AbsolutePosition = Position;
		AbsoluteRotation = Rotation;
		if(Parent)
		{
			AbsolutePosition += Parent->getAbsolutePosition();
			AbsoluteRotation += Parent->getAbsoluteRotation();
		}
		list<DmEntity*>::iterator it;
		for(it = Children.begin();it != Children.end();++it)
			if((*it))
				(*it)->updateAbsoluteTranslation();
	}

	void DmEntity::setupRender()
	{
		glTranslatef(AbsolutePosition.X,AbsolutePosition.Y,AbsolutePosition.Z);
		glRotatef(AbsoluteRotation.X,1,0,0);
		glRotatef(AbsoluteRotation.Y,0,1,0);
		glRotatef(AbsoluteRotation.Z,0,0,1);
	}

}
}
