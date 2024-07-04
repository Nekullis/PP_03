#pragma once
#include "AppFrame.h"
class CollisionComponent : public Component
{
public:
	enum class COLLISIONTYPE
	{
		NONE,
		CIRCLE,
		AABB,
		CAPSULE,
		WEAPON,
	};
	enum class COLLISIONGROUP
	{
		PLAYER,
		ENEMY,
		Neutral
	};
	CollisionComponent(class ObjectBase* owner, int updateowder = 150);
	virtual ~CollisionComponent();
	virtual void Update()override;
	//ゲッター
	Vector3D GetPos() { return mPos; }
	float GetRadius() { return mRadius; }
	float GetSeg() { return mLineSeg; }
	COLLISIONTYPE GetType() { return mType; }
	COLLISIONGROUP GetGroup() { return mGroup; }
	//セッター
	void SetPos(Vector3D pos) { mPos = pos; }
	void SetRadius(float radius) { mRadius = radius; }
	void SetType(COLLISIONTYPE col) { mType = col; }
	void SetSeg(float seg) { mLineSeg = seg; }
	void SetGroup(COLLISIONGROUP group) { mGroup = group; }
protected:
	Vector3D mPos;
	class CollisionManager* mManager;
	COLLISIONTYPE mType;
	COLLISIONGROUP mGroup;
	float mRadius;
	float mLineSeg;
};

