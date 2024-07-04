#pragma once
#include "CollisionComponent.h"
class WeaponColComponent : public CollisionComponent
{
public:
	WeaponColComponent(class ObjectBase* owner, int updateowder = 200);
	virtual ~WeaponColComponent();
	void Update()override;
	Vector3D GetTopPos() { return mTopPos; }
	//セッター
	void SetTopPos(Vector3D pos) { mTopPos = pos; }
protected:
	Vector3D mTopPos;
};

