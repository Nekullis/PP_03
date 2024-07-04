#include "Player.h"
#include "AppFrame.h"
#include "ObjectManager.h"
#include "AttackManager.h"
#include "DrawComponent.h"
#include "CameraComponent.h"
#include "InputComponent.h"
#include "CapsuleColComponent.h"
#include "Weapon.h"
#include "WeaponColComponent.h"
#include "AttackState.h"

Player* Player::plInstance = nullptr;
Player::Player(ModeBase* game):chara(game)
{
	plInstance = this;
	mManager = ObjectManager::GetInstance();
	mHp = 100;
	//待機状態に
	mAnimation= ANIMATION::WAIT;
	//位置初期化
	mPos = Vector3D(0, 100, 0);
	//向き初期化
	mRotation = Vector3D(0, MyMath::DegToRad(180), 0);
	//初期アニメーションアタッチ番号設定
	mAttachNum = 0;
	//アニメーション登録
	RegisterAnimation();

	//描画用コンポーネント追加
	//プレイヤー描画用コンポーネント追加
	mDraw = new DrawComponent(this);
	//パスを入れておく
	const char* pass = "res/Model/Character/Player/Player.mv1";
	//セッターでパスを登録
	mDraw->LoadPass(pass);
	//アニメーション用にモデルハンドル取得
	mAnimHandle = mDraw->GetHandle();
	//プレイヤーに描画用コンポーネント登録
	mManager->AddDraw(mDraw);

	//オブジェクト(武器)追加
	//武器初期化
	mWeapon = new Weapon(game);
	//武器の衝突判定コンポーネントのグループをプレイヤーに
	mWeapon->GetColComponent()->SetGroup(CollisionComponent::COLLISIONGROUP::PLAYER);
	//武器半径初期化
	float weapon_rad = 50.0;
	mWeapon->SetRadius(weapon_rad);
	//武器をつけるフレーム設定
	int frame_index= MV1SearchFrame(mAnimHandle, "joint_sword");
	mWeapon->SetFrameIndex(frame_index);
	mWeapon->SetEquipHandle(mAnimHandle);

	//入力処理のコンポーネント追加
	//入力処理のコンポーネント初期化
	InputComponent* input = new InputComponent(this);
	//プレイヤー速度初期化
	input->SetForwardSpeed(20);

	//カメラコンポーネント追加
	//プレイヤーにカメラコンポーネント初期化、追加
	CameraComponent* camera = new CameraComponent(this);

	//衝突判定用コンポーネント追加
	//衝突判定用コンポーネント初期化
	mCol = new CapsuleColComponent(this);
	//衝突判定コンポーネントのグループをプレイヤーに
	mCol->SetGroup(CollisionComponent::COLLISIONGROUP::PLAYER);
	//半径設定
	float col_rad = 30.0;
	mCol->SetRadius(col_rad);
	//線分の長さ設定
	float line_seg = 170.0;
	mCol->SetSeg(line_seg);
	//マネージャーにプレイヤー登録
	mManager->Spawn(this);

	//攻撃追加
	//攻撃マネージャー初期化
	mAtkManager = new AttackManager();
	AttackState attack_state[4];
	AttackState::ATTACK attack[4] =
	{
		{
			//アニメーション
			Player::ANIMATION::NONE,
			//モーショントータルフレーム
			0.0,
			//ボタン入力猶予開始フレーム
			0.0,
			//ボタン入力猶予終了フレーム
			0.0,
			//モーション切り替え開始フレーム
			0.0,
			//攻撃判定開始フレーム
			0.0,
			//攻撃判定終了フレーム
			0.0,
			//衝突判定範囲
			0.0,
			//派生可能か
			true
		},
		{
			//アニメーション
			Player::ANIMATION::FIRSTATTACK,
			//モーショントータルフレーム
			65.0,
			//ボタン入力猶予開始フレーム
			15.0,
			//ボタン入力猶予終了フレーム
			60.0,
			//モーション切り替え開始フレーム
			40.0,
			//攻撃判定開始フレーム
			25.0,
			//攻撃判定終了フレーム
			35.0,
			//衝突判定範囲
			50.0,
			//派生可能か
			true
		},
		{
			//アニメーション
			Player::ANIMATION::SECONDATTACK,
			//モーショントータルフレーム
			72.0,
			//ボタン入力猶予開始フレーム
			15.0,
			//ボタン入力猶予終了フレーム
			70.0,
			//モーション切り替え開始フレーム
			28.0,
			//攻撃判定開始フレーム
			5.0,
			//攻撃判定終了フレーム
			30.0,
			//衝突判定範囲
			50.0,
			//派生可能か
			true
		},
		{
			//アニメーション
			Player::ANIMATION::THIRDATTACK,
			//モーショントータルフレーム
			90.0,
			//ボタン入力猶予開始フレーム
			25.0,
			//ボタン入力猶予終了フレーム
			54.0,
			//モーション切り替え開始フレーム
			0.0,
			//攻撃判定開始フレーム
			31.0,
			//攻撃判定終了フレーム
			54.0,
			//衝突判定範囲
			50.0,
			//派生可能か
			false
		}
	};
	for (int i = 0; i < 4; i++)
	{
		attack_state[i].SetState(attack[i]);
		mAtkManager->AddAttack(i, attack_state[i]);
	}
	


}

Player::~Player()
{
	delete mDraw;
	delete mCol;
	delete mWeapon;
	delete mAtkManager;
	MV1DetachAnim(mAnimHandle, mAnimAttachIndex);
}

void Player::RegisterAnimation()
{
	Character::RegisterAnimation();
}

void Player::Process()
{
	chara::Process();
	//衝突判定用の位置設定
	mCol->SetPos(mPos);
	mDraw->SetPos(mPos);
	//スティックが傾いているか
	if (!mAtkManager->IsAttackMotion())
	{
		if (GameXPad::GetInstance()->IsInputStickLeft())
		{
			//アニメーションを歩きに
			mAnimation = ANIMATION::WALK;
		}
		else
		{
			//アニメーションを待ちに
			mAnimation = ANIMATION::WAIT;
		}
	}
	
	//アニメーションが1フレーム前と違うのなら
	if (mAnimation != oldAnimation)
	{
		int old_attach_index = mAnimAttachIndex;
		//アニメーションのデタッチ
		MV1DetachAnim(mAnimHandle, mAnimAttachIndex);
		//アニメーションによってアタッチする番号を変更する
		switch (mAnimation)
		{
		//待機
		case ANIMATION::WAIT:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 0, -1, false);
			break;
		//歩行
		case ANIMATION::WALK:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 7, -1, false);
			break;
		//連続攻撃1撃目
		case ANIMATION::FIRSTATTACK:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 2, -1, false);
			break;
		//連続攻撃2撃目
		case ANIMATION::SECONDATTACK:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 3, -1, false);
			break;
		//連続攻撃3撃目
		case ANIMATION::THIRDATTACK:
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
	if(mAnimPlayTime >= mAnimTotalTime) { mAnimPlayTime = 0.0f; }
	//現再生時間をセット
	MV1SetAttachAnimTime(mAnimHandle, mAnimAttachIndex, mAnimPlayTime);
	oldAnimation = mAnimation;
	//攻撃処理更新
	mAtkManager->Update();
}

void Player::Render()
{
	chara::Render();
}
