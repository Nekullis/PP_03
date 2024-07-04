#include "AttackManager.h"
#include "GameCollision.h"
#include "Player.h"

AttackManager* AttackManager::atkManaInstance = nullptr;
AttackManager::AttackManager()
{
	atkManaInstance = this;
	mState = AttackState();
	mAttackCnt = 0;
	mNowNum = 0;
	mChangeFrag = false;
	AttackMotionChange(0);
}

AttackManager::~AttackManager()
{
}

void AttackManager::AddAttack(int num ,AttackState state)
{
	//コンテナに格納する
	mAttackList.emplace(num,state);
}

void AttackManager::AttackMotionChange(int num)
{
	//イテレータで対応キーを見つける
	auto itr = mAttackList.find(num);
	if (itr != mAttackList.end())
	{
		//対応キーが見つかったら対応要素を代入する
		mState = itr->second;
		if (num != 0) { Player::GetInstance()->SetAnimation(mState.GetState().mAnimation); }
		//カウントリセット
		mAttackCnt = 0;
	}
}

void AttackManager::Update()
{
	GameXPad* pad = GameXPad::GetInstance();
	//ボタン入力フラグ
	bool push_flag = false;
	//カウントを増やす
	if (mNowNum != 0) { mAttackCnt++; }
	//フレームカウントが入力猶予フレーム内ならば
	if (mAttackCnt >= mState.GetState().mPushStartFrame && mAttackCnt <= mState.GetState().mPushEndFrame)
	{
		//ボタン入力フラグをtureに
		push_flag = true;
	}
	//攻撃ボタンが押された時
	if (pad->GetXTrg(XINPUT_BUTTON_B))
	{
		//ボタン入力フラグがtrueなら
		if (push_flag)
		{
			//モーション変更フラグをtrueに
			mChangeFrag = true;
			if (GameCollision::GetInstance()->GetLockOn())
			{
				Vector3D sub = GameCollision::GetInstance()->GetTarget() - Player::GetInstance()->GetPos();
				if (sub.Length() <= 1000)
				{
					Vector3D norm = sub.Normalize();
					double len = sub.Length() * 0.5;
					Vector3D scale = norm.Scale(len);
					Vector3D add = Player::GetInstance()->GetPos() + scale;
					if (sub.Length() >= 200) { Player::GetInstance()->SetPos(add); }
				}
			}
		}
	}
	//モーション変更フラグがtrueの時
	if (mChangeFrag)
	{	
		//モーションが切り替わるフレームカウントに到達した
		if (mAttackCnt >= mState.GetState().mMotionChangeFrame)
		{
			//かつその攻撃が派生可能の時
			if (mState.GetState().mIsDerivation)
			{
				//攻撃番号を加算
				mNowNum++;
				AttackMotionChange(mNowNum);
				mChangeFrag = false;
			}
		}
	}
	//攻撃時
	if (mNowNum != 0)
	{
	}
	//何も入力せずにトータルフレームに達した
	if (mAttackCnt == mState.GetState().mMotionTotalFrame)
	{
		//攻撃番号を0に
		mNowNum = 0;
		//攻撃モーション変更
		AttackMotionChange(mNowNum);
		//カウントリセット
		mAttackCnt = 0;
	}
}

bool AttackManager::IsAttack()
{
	//カウントが衝突判定時間内ならば
	if (mNowNum != 0)
	{
		if (mAttackCnt >= mState.GetState().mColStartFrame && mAttackCnt <= mState.GetState().mColEndFrame)
		{
			//trueを返す
			return true;
		}
	}
	
	return false;
}

bool AttackManager::IsAttackMotion()
{
	if (mNowNum != 0) {return true;}
	return false;
}
