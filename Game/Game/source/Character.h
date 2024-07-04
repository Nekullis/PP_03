#pragma once
#include "AppFrame.h"
class Character : public ObjectBase
{
	using base = ObjectBase;
	//�L�����N�^�[�S�ʂ̐e�N���X
public:
	enum class ANIMATION
	{
		WAIT,
		WALK
	};
	Character(ModeBase* game);
	virtual ~Character();
	virtual void RegisterAnimation();
	virtual void Process()override;
	virtual void Render()override;
	//�Q�b�^�[
	int GetHP() const { return mHp; }
	//�Z�b�^�[
protected:
	//�̗�
	int mHp;
	//�A�j���[�V�����֘A
	int mAnimHandle;
	int mAnimAttachIndex;
	int mAttachNum;
	float mAnimPlayTime;
	float mAnimTotalTime;
};

