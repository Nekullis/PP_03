#pragma once
#include "Enemy.h"
class EnemyMob : public Enemy
{
public:
	enum class ANIMATION
	{
		WAIT,
		WALK,
		DAMAGE,
		DEAD
	};
	EnemyMob(ModeBase* game);
	virtual ~EnemyMob();
	void RegisterAnimation()override;
	void Process()override;
	void Render()override;
	void Damage(Vector3D pos)override;
protected:
	class ObjectManager* mManager;
	ANIMATION mAnimation;
	ANIMATION oldAnimation;
	class CapsuleColComponent* mCol;
	class DrawComponent* mDraw;
	bool mIsDamage;
	bool mIsDead;
	int mDamageCnt;
};

