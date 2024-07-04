#include "WeaponColComponent.h"

WeaponColComponent::WeaponColComponent(ObjectBase* owner, int updateowder) :CollisionComponent(owner, updateowder)
{
	mType = COLLISIONTYPE::WEAPON;
}

WeaponColComponent::~WeaponColComponent()
{
}

void WeaponColComponent::Update()
{
	CollisionComponent::Update();
}
