#include "ModeGame.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyMob.h"
#include "TargetMaker.h"
#include "ObjectManager.h"
#include "GameCollision.h"
#include "DamageEffect.h"
#include "CollisionManager.h"
#include "ModeGameClear.h"

ModeGame* ModeGame::gameInstance = nullptr;
bool ModeGame::Initialize()
{
	gameInstance = this;
	if (!ModeBase::Initialize()) { return false; }
	mGameClearFlag = false;
	//オブジェクトマネージャー初期化
	mObjManager = new ObjectManager();
	//コリジョン系統のクラス初期化
	mGameCol = new GameCollision();
	mColManager = new CollisionManager();
	Register();
	return true;
}

bool ModeGame::Terminate()
{
	ModeBase::Terminate();
	delete mObjManager;
	delete mGameCol;
	delete mColManager;
	delete mPlayer;
	delete mEnemy;
	delete mStage;
	return true;
}

void ModeGame::Register()
{
	//プレイヤー追加
	mPlayer = new Player(this);
	////マーカー追加
	//TargetMaker* maker = new TargetMaker(this);
	//敵追加
	mEnemy = new EnemyMob(this);
	mEnemy->SetPos(Vector3D(-500, 100, 1000));
	mDamageEffect = new DamageEffect(this);
	//ステージ追加
	mStage = new Stage(this);
}

bool ModeGame::Process()
{
	//各プロセスの更新
	ModeBase::Process();
	mColManager->Update();
	mObjManager->Process();
	mGameCol->Update();
	if (mGameClearFlag)
	{
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);
		// 次のモードを登録
		ModeServer::GetInstance()->Add(new ModeGameClear(), 1, "clear");
	}
	return true;
}

bool ModeGame::Render()
{
	//zバッファー有効化
	SetUseZBuffer3D(true);
	//zバッファー書き込み設定
	SetWriteZBuffer3D(true);
	//ライト有効化
	SetUseLighting(true);
	//ライトタイプをディレクショナルタイプに設定
	ChangeLightTypeDir(Vector3D(0,-1,1).dxl());
	ModeBase::Render();
	mObjManager->Render();
	return true;
}




