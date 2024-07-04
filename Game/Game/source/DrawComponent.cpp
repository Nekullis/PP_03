#include "DrawComponent.h"
#include "ObjectManager.h"
#include "ModeGame.h"
DrawComponent::DrawComponent(ObjectBase* owner, int updateowder) :Component(owner, updateowder)
{
	mOwner = owner;
	mHandle = 0;
	mPass = "";
	mPos = Vector3D(0.0, 0.0, 0.0);
	mScale = Vector3D(1.0, 1.0, 1.0);
	ObjectManager::GetInstance()->AddDraw(this);
}

DrawComponent::~DrawComponent()
{
}

void DrawComponent::LoadPass(const char* pass)
{
	mPass = pass;
	mHandle = MV1LoadModel((const TCHAR*)(mPass));
}

void DrawComponent::Update()
{
	Component::Update();
	MV1SetPosition(mHandle, mPos.dxl());
	MV1SetScale(mHandle, mScale.dxl());
	MV1SetRotationXYZ(mHandle, mOwner->GetRotation().dxl());
	MV1DrawModel(mHandle);
}


