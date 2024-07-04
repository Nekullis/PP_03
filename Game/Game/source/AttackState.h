#pragma once
#include "AppFrame.h"
#include "Player.h"
class AttackState
{
public:
	struct ATTACK
	{
		//�A�j���[�V����
		Player::ANIMATION mAnimation;
		//���[�V�����g�[�^���t���[��
		float mMotionTotalFrame;
		//�{�^�����͗P�\�J�n�t���[��
		float mPushStartFrame;
		//�{�^�����͗P�\�I���t���[��
		float mPushEndFrame;
		//���[�V�����؂�ւ��J�n�t���[��
		float mMotionChangeFrame;
		//�U������J�n�t���[��
		float mColStartFrame;
		//�U������I���t���[��
		float mColEndFrame;
		//�Փ˔���͈�
		float mColRadius;
		//�h���\��
		bool mIsDerivation;
	};
	AttackState();
	virtual ~AttackState();
	void Update();
	//�Q�b�^�[
	ATTACK GetState() { return mAttack; }
	//�Z�b�^�[
	void SetState(ATTACK attack) { mAttack = attack; }
protected:
	ATTACK mAttack;
};