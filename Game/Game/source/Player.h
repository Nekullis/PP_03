#pragma once
#include "Character.h"
class Player : public Character
{
	using chara = Character;
public:
	static Player* plInstance;
	//ステータス
	enum class ANIMATION
	{
		NONE,
		WAIT,
		WALK,
		FIRSTATTACK,
		SECONDATTACK,
		THIRDATTACK
	};
	Player(ModeBase* game);
	virtual ~Player();
	void RegisterAnimation()override;
	void Process()override;
	void Render()override;
	//ゲッター
	static Player* GetInstance() { return plInstance; }
	//セッター
	void SetAnimation(ANIMATION animation) { mAnimation = animation; }
protected:
	//ステータス
	ANIMATION mAnimation;
	ANIMATION oldAnimation;
	//クラス
	class ObjectManager* mManager;
	class CapsuleColComponent* mCol;
	class DrawComponent* mDraw;
	class Weapon* mWeapon;
	class AttackManager* mAtkManager;
};

