#pragma once
#include "CollisionComponent.h"
//カプセル型の衝突判定用コンポーネント
class CapsuleColComponent :public CollisionComponent
{
public:
	static CapsuleColComponent* capInstance;
	CapsuleColComponent(class ObjectBase* owner, int updateowder = 200);
	virtual ~CapsuleColComponent();
	virtual void Update()override;
	//ゲッター
	static CapsuleColComponent* GetInstance() { return capInstance; }
	Vector3D GetTopPos() { return mTopPos; }
	//セッター
	void SetTopPos(Vector3D pos) { mTopPos = pos; }
protected:
	Vector3D mTopPos;
};

