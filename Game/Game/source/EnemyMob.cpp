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
	//体力設定
	mHp = 20;
	//待機状態に
	mAnimation = ANIMATION::WAIT;
	mIsDamage = false;
	mIsDead = false;
	mDamageCnt = 0;

	//描画用コンポーネント追加
	//描画用コンポーネント初期化
	mDraw = new DrawComponent(this);
	//パスを入れておく
	const char* pass = "res/Model/Character/Enemy/enemy.mv1";
	//セッターでパスを登録
	mDraw->LoadPass(pass);
	//アニメーション用にモデルハンドル取得
	mAnimHandle = mDraw->GetHandle();
	//プレイヤーに描画用コンポーネント登録
	mManager->AddDraw(mDraw);

	//衝突判定用コンポーネント追加
	//衝突判定用コンポーネント初期化
	mCol = new CapsuleColComponent(this);
	mCol->SetGroup(CollisionComponent::COLLISIONGROUP::ENEMY);
	//半径設定
	float rad = 30.0;
	mCol->SetRadius(rad);
	//線分の長さ設定
	float line_seg = 170.0;
	mCol->SetSeg(line_seg);
	mAttachNum = 6;
	RegisterAnimation();

	//マネージャーに登録
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
	//位置設定
	mCol->SetPos(mPos);
	mCol->SetTopPos(mPos + Vector3D(0.0, 170.0, 0.0));
	mDraw->SetPos(mPos);
	//アニメーションが1フレーム前と違うのなら
	if(mAnimation != oldAnimation)
	{
		int old_attach_index = mAnimAttachIndex;
		//アニメーションのデタッチ
		MV1DetachAnim(mAnimHandle, mAnimAttachIndex);
		//アニメーションによってアタッチする番号を変更する
		switch (mAnimation)
		{
			//待機
		case ANIMATION::WAIT:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 6, -1, false);
			break;
			//歩行
		case ANIMATION::WALK:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 7, -1, false);
			break;
			//ダメージ
		case ANIMATION::DAMAGE:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 3, -1, false);
			break;
		case ANIMATION::DEAD:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 4, -1, false);
			break;
		}
		//再生時間リセット
		mAnimPlayTime = 0;
		//総再生時間セット
		mAnimTotalTime = MV1GetAttachAnimTotalTime(mAnimHandle, mAnimAttachIndex);
	}
	//アニメーションカウント加算
	mAnimPlayTime += 1.0f;
	//総再生時間に到達したらリセット
	if(mAnimPlayTime >= mAnimTotalTime) 
	{ 
		mAnimPlayTime = (mIsDead) ? mAnimTotalTime : 0;
		if (mIsDead)
		{
			ModeGame::GetInstance()->SetClearFlag(true);
		}
	}
	//現再生時間をセット
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
