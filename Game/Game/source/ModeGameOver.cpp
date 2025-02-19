#include "ApplicationGlobal.h"
#include "ModeGameOver.h"
#include "ModeTitle.h"

bool ModeGameOver::Initialize()
{
	if (!ModeBase::Initialize()) { return false; }
	//画像初期化
	mHandle = _global.mResManager->LoadGraph("res/Graph/GameClear/GameClear.png");
	//ゲームパッド	追加
	mPad = new GameXPad();
	return true;
}

bool ModeGameOver::Terminate()
{
	ModeBase::Terminate();
	delete mPad;
	return true;
}

bool ModeGameOver::Process()
{
	ModeBase::Process();
	mPad->Input();
	if (mPad->GetXTrg(XINPUT_BUTTON_B))
	{
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);
		// 次のモードを登録
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "game");
	}
	return true;
}

bool ModeGameOver::Render()
{
	ModeBase::Render();
	//画像描画
	DrawGraph(0, 0, mHandle, false);
	return true;
}
