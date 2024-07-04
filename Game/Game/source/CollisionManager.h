#pragma once
#include "CollisionComponent.h"
//�Փ˔�����s���ۂ̃}�l�[�W���[
class CollisionManager
{
public:
	static CollisionManager* colMaInstance;
	CollisionManager();
	~CollisionManager();
	void Update();
	//�ǉ�
	void AddCollision(CollisionComponent* col);
	//�폜
	void Delete();
	//�Q�b�^�[
	static CollisionManager* GetInstance() { return colMaInstance; }
	Vector3D GetHitPos() { return mHitPos; }
protected:
	std::list<CollisionComponent*> mCollisionList;
	Vector3D mHitPos;
};

