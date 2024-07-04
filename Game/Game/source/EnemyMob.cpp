#include "ModeGame.h"
#include "EnemyMob.h"
#include "DrawComponent.h"
#include "ObjectManager.h"
#include "AIComponent.h"
#include "CapsuleColComponent.h"
#include "DamageEffect.h"
#include "CollisionManager.h"

EnemyMob::EnemyMob(ModeBase* game) :Enemy(game)
{
	mManager = ObjectManager::GetInstance();
	//�̗͐ݒ�
	mHp = 20;
	//�ҋ@��Ԃ�
	mAnimation = ANIMATION::WAIT;
	mIsDamage = false;
	mIsDead = false;
	mDamageCnt = 0;

	//�`��p�R���|�[�l���g�ǉ�
	//�`��p�R���|�[�l���g������
	mDraw = new DrawComponent(this);
	//�p�X�����Ă���
	const char* pass = "res/Model/Character/Enemy/enemy.mv1";
	//�Z�b�^�[�Ńp�X��o�^
	mDraw->LoadPass(pass);
	//�A�j���[�V�����p�Ƀ��f���n���h���擾
	mAnimHandle = mDraw->GetHandle();
	//�v���C���[�ɕ`��p�R���|�[�l���g�o�^
	mManager->AddDraw(mDraw);

	//�Փ˔���p�R���|�[�l���g�ǉ�
	//�Փ˔���p�R���|�[�l���g������
	mCol = new CapsuleColComponent(this);
	mCol->SetGroup(CollisionComponent::COLLISIONGROUP::ENEMY);
	//���a�ݒ�
	float rad = 30.0;
	mCol->SetRadius(rad);
	//�����̒����ݒ�
	float line_seg = 170.0;
	mCol->SetSeg(line_seg);
	mAttachNum = 6;
	RegisterAnimation();

	//�}�l�[�W���[�ɓo�^
	mManager->Spawn(this);
}

EnemyMob::~EnemyMob()
{
	MV1DetachAnim(mAnimHandle, mAnimAttachIndex);
}

void EnemyMob::RegisterAnimation()
{
	Enemy::RegisterAnimation();
}

void EnemyMob::Process()
{
	Enemy::Process();
	//�ʒu�ݒ�
	mCol->SetPos(mPos);
	mCol->SetTopPos(mPos + Vector3D(0.0, 170.0, 0.0));
	mDraw->SetPos(mPos);
	//�A�j���[�V������1�t���[���O�ƈႤ�̂Ȃ�
	if(mAnimation != oldAnimation)
	{
		int old_attach_index = mAnimAttachIndex;
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(mAnimHandle, mAnimAttachIndex);
		//�A�j���[�V�����ɂ���ăA�^�b�`����ԍ���ύX����
		switch (mAnimation)
		{
			//�ҋ@
		case ANIMATION::WAIT:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 6, -1, false);
			break;
			//���s
		case ANIMATION::WALK:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 7, -1, false);
			break;
			//�_���[�W
		case ANIMATION::DAMAGE:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 3, -1, false);
			break;
		case ANIMATION::DEAD:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 4, -1, false);
			break;
		}
		//�Đ����ԃ��Z�b�g
		mAnimPlayTime = 0;
		//���Đ����ԃZ�b�g
		mAnimTotalTime = MV1GetAttachAnimTotalTime(mAnimHandle, mAnimAttachIndex);
	}
	//�A�j���[�V�����J�E���g���Z
	mAnimPlayTime += 1.0f;
	//���Đ����Ԃɓ��B�����烊�Z�b�g
	if(mAnimPlayTime >= mAnimTotalTime) 
	{ 
		mAnimPlayTime = (mIsDead) ? mAnimTotalTime : 0;
		if (mIsDead)
		{
			ModeGame::GetInstance()->SetClearFlag(true);
		}
	}
	//���Đ����Ԃ��Z�b�g
	MV1SetAttachAnimTime(mAnimHandle, mAnimAttachIndex, mAnimPlayTime);
	oldAnimation = mAnimation;
	if (mIsDamage)
	{
		mDamageCnt++;
		if (!mIsDead)
		{
			if (mDamageCnt >= 20)
			{
				mAnimation = ANIMATION::WAIT;
				mIsDamage = false;
				mDamageCnt = 0;
			}
		}
	}
}

void EnemyMob::Render()
{
	Enemy::Render();
}

void EnemyMob::Damage(Vector3D pos)
{
	if (!mIsDamage)
	{
		DamageEffect* effect = new DamageEffect(ModeGame::GetInstance());
		effect->SetPos(CollisionManager::GetInstance()->GetHitPos());
		effect->Start(50);
		Enemy::Damage(pos);
		mAnimation = (mHp > 0) ? ANIMATION::DAMAGE : ANIMATION::DEAD;
		mIsDead = (mHp > 0) ? false : true;
		Vector3D v = mPos - pos;
		Vector3D norm = v.Normalize();
		double len = -5;
		Vector3D scale = norm.Scale(len);
		mPos += scale;
		float tan = atan2(norm._z, norm._x);
		mRotation._y = MyMath::DegToRad(tan);
		mIsDamage = true;
	}
	
}
