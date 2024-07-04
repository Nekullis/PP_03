#include "ApplicationGlobal.h"
#include "ModeGameOver.h"
#include "ModeTitle.h"

bool ModeGameOver::Initialize()
{
	if (!ModeBase::Initialize()) { return false; }
	//‰æ‘œ‰Šú‰»
	mHandle = _global.mResManager->LoadGraph("res/Graph/GameClear/GameClear.png");
	//ƒQ[ƒ€ƒpƒbƒh	’Ç‰Á
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
		// ‚±‚Ìƒ‚[ƒh‚ðíœ—\–ñ
		ModeServer::GetInstance()->Del(this);
		// ŽŸ‚Ìƒ‚[ƒh‚ð“o˜^
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "game");
	}
	return true;
}

bool ModeGameOver::Render()
{
	ModeBase::Render();
	//‰æ‘œ•`‰æ
	DrawGraph(0, 0, mHandle, false);
	return true;
}
