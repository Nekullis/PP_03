#include "Stage.h"
#include "DrawComponent.h"
#include "ObjectManager.h"
Stage* Stage::stageInstance = nullptr;
Stage::Stage(ModeBase* game):ObjectBase(game)
{
	stageInstance = this;
	mPos = Vector3D(0, -100, 0);
	mRotation = Vector3D(0, 0, 0);
	mManager = ObjectManager::GetInstance();
	//ステージ描画用コンポーネント初期化
	DrawComponent* draw_stage = new DrawComponent(this);
	//パスを入れておく
	const char* pass_stage = "res/Model/Stage/StageModel.mv1";
	//セッターでパスを登録
	draw_stage->LoadPass(pass_stage);
	//ステージ位置設定
	Vector3D stage_pos = Vector3D(0, -10, 0);
	draw_stage->SetPos(stage_pos);
	mManager->AddDraw(draw_stage);
	//マネージャーにステージ登録
	mManager->Spawn(this);
}

Stage::~Stage()
{
}

void Stage::Process()
{
	ObjectBase::Process();
}

void Stage::Render()
{
	ObjectBase::Render();
}
