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
	//�R���e�i�Ɋi�[����
	mAttackList.emplace(num,state);
}

void AttackManager::AttackMotionChange(int num)
{
	//�C�e���[�^�őΉ��L�[��������
	auto itr = mAttackList.find(num);
	if (itr != mAttackList.end())
	{
		//�Ή��L�[������������Ή��v�f��������
		mState = itr->second;
		if (num != 0) { Player::GetInstance()->SetAnimation(mState.GetState().mAnimation); }
		//�J�E���g���Z�b�g
		mAttackCnt = 0;
	}
}

void AttackManager::Update()
{
	GameXPad* pad = GameXPad::GetInstance();
	//�{�^�����̓t���O
	bool push_flag = false;
	//�J�E���g�𑝂₷
	if (mNowNum != 0) { mAttackCnt++; }
	//�t���[���J�E���g�����͗P�\�t���[�����Ȃ��
	if (mAttackCnt >= mState.GetState().mPushStartFrame && mAttackCnt <= mState.GetState().mPushEndFrame)
	{
		//�{�^�����̓t���O��ture��
		push_flag = true;
	}
	//�U���{�^���������ꂽ��
	if (pad->GetXTrg(XINPUT_BUTTON_B))
	{
		//�{�^�����̓t���O��true�Ȃ�
		if (push_flag)
		{
			//���[�V�����ύX�t���O��true��
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
	//���[�V�����ύX�t���O��true�̎�
	if (mChangeFrag)
	{	
		//���[�V�������؂�ւ��t���[���J�E���g�ɓ��B����
		if (mAttackCnt >= mState.GetState().mMotionChangeFrame)
		{
			//�����̍U�����h���\�̎�
			if (mState.GetState().mIsDerivation)
			{
				//�U���ԍ������Z
				mNowNum++;
				AttackMotionChange(mNowNum);
				mChangeFrag = false;
			}
		}
	}
	//�U����
	if (mNowNum != 0)
	{
	}
	//�������͂����Ƀg�[�^���t���[���ɒB����
	if (mAttackCnt == mState.GetState().mMotionTotalFrame)
	{
		//�U���ԍ���0��
		mNowNum = 0;
		//�U�����[�V�����ύX
		AttackMotionChange(mNowNum);
		//�J�E���g���Z�b�g
		mAttackCnt = 0;
	}
}

bool AttackManager::IsAttack()
{
	//�J�E���g���Փ˔��莞�ԓ��Ȃ��
	if (mNowNum != 0)
	{
		if (mAttackCnt >= mState.GetState().mColStartFrame && mAttackCnt <= mState.GetState().mColEndFrame)
		{
			//true��Ԃ�
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
