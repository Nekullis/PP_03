#include "Character.h"

Character::Character(ModeBase* game):base(game)
{
	mHp = 0;
	mAttachNum = 0;
}

Character::~Character()
{
}

void Character::RegisterAnimation()
{
	//初期状態のアニメーションセット
	mAnimAttachIndex = MV1AttachAnim(mAnimHandle, mAttachNum, -1, false);
	//再生時間初期化
	mAnimPlayTime = 0;
	//総再生時間取得
	mAnimTotalTime = MV1GetAttachAnimTotalTime(mAnimHandle, mAnimAttachIndex);
}

void Character::Process()
{
	base::Process();
	mPos._y = 100;
}

void Character::Render()
{
	base::Render();
}
