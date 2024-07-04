#include "MoveComponent.h"
#include "ObjectManager.h"
#include <Math.h>
MoveComponent::MoveComponent(ObjectBase* owner, int updateowder) :Component(owner, updateowder)
{
	mOwner->AddComponent(this);
}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::Update()
{
	Component::Update();
}
