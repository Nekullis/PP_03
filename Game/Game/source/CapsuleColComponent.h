#pragma once
#include "CollisionComponent.h"
//�J�v�Z���^�̏Փ˔���p�R���|�[�l���g
class CapsuleColComponent :public CollisionComponent
{
public:
	static CapsuleColComponent* capInstance;
	CapsuleColComponent(class ObjectBase* owner, int updateowder = 200);
	virtual ~CapsuleColComponent();
	virtual void Update()override;
	//�Q�b�^�[
	static CapsuleColComponent* GetInstance() { return capInstance; }
	Vector3D GetTopPos() { return mTopPos; }
	//�Z�b�^�[
	void SetTopPos(Vector3D pos) { mTopPos = pos; }
protected:
	Vector3D mTopPos;
};

