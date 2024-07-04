#pragma once
#include "AppFrame.h"
#include "Player.h"
class AttackState
{
public:
	struct ATTACK
	{
		//アニメーション
		Player::ANIMATION mAnimation;
		//モーショントータルフレーム
		float mMotionTotalFrame;
		//ボタン入力猶予開始フレーム
		float mPushStartFrame;
		//ボタン入力猶予終了フレーム
		float mPushEndFrame;
		//モーション切り替え開始フレーム
		float mMotionChangeFrame;
		//攻撃判定開始フレーム
		float mColStartFrame;
		//攻撃判定終了フレーム
		float mColEndFrame;
		//衝突判定範囲
		float mColRadius;
		//派生可能か
		bool mIsDerivation;
	};
	AttackState();
	virtual ~AttackState();
	void Update();
	//ゲッター
	ATTACK GetState() { return mAttack; }
	//セッター
	void SetState(ATTACK attack) { mAttack = attack; }
protected:
	ATTACK mAttack;
};