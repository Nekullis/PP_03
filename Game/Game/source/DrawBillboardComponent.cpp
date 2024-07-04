#include "DrawBillboardComponent.h"

DrawBillboardComponent::DrawBillboardComponent(ObjectBase* owner, int updateowder) :Component(owner, updateowder)
{
	mOwner = owner;
	mHandle = -1;

}

DrawBillboardComponent::~DrawBillboardComponent()
{

}

void DrawBillboardComponent::Update()
{
	Component::Update();
	DrawBillboard3D(mOwner->GetPos().dxl(), 0.5, 0.5, 1, 0.0, mHandle, true);
	//DrawGraph(0, 0, mHandle, true);
}
