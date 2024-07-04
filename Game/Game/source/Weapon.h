#pragma once
#include "AppFrame.h"
class Weapon : public ObjectBase
{
public:
	Weapon(ModeBase* game);
	virtual ~Weapon();
	void Process()override;
	void Render()override;
	//�Q�b�^�[
	float GetRadius() { return mRadius; }
	class WeaponColComponent* GetColComponent() { return mCol; }
	//�Z�b�^�[
	void SetRadius(float radius) { mRadius = radius; }
	void SetFrameIndex(int index) { mFrameIndex = index; }
	void SetEquipHandle(int handle) { mEquipModelHandle = handle; }
protected:
	Vector3D mTopPos;
	int mFrameIndex;
	int mEquipModelHandle;
	float mRadius;
	int mAnimHandle;
	class ObjectManager* mManager;
	class WeaponColComponent* mCol;
	class DrawComponent* mDraw;
};

