#pragma once
#include "Character.h"
class Player : public Character
{
	using chara = Character;
public:
	static Player* plInstance;
	//�X�e�[�^�X
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
	//�Q�b�^�[
	static Player* GetInstance() { return plInstance; }
	//�Z�b�^�[
	void SetAnimation(ANIMATION animation) { mAnimation = animation; }
protected:
	//�X�e�[�^�X
	ANIMATION mAnimation;
	ANIMATION oldAnimation;
	//�N���X
	class ObjectManager* mManager;
	class CapsuleColComponent* mCol;
	class DrawComponent* mDraw;
	class Weapon* mWeapon;
	class AttackManager* mAtkManager;
};

