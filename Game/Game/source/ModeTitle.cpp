#include "ModeTitle.h"
#include "AppFrame.h"
#include "ApplicationGlobal.h"
#include "InputComponent.h"
#include "ModeGame.h"

bool ModeTitle::Initialize()
{
	if (!base::Initialize()) { return false; }
	mHandle = _global.mResManager->LoadGraph("res/Graph/Title/DivienGame_Title.png");
	mPad = new GameXPad();
	return true;
}

bool ModeTitle::Terminate()
{
	base::Terminate();
	delete mPad;
	return true;
}

bool ModeTitle::Process()
{
	base::Process();
	mPad->Input();
	if (mPad->GetXTrg(XINPUT_BUTTON_B))
	{
		// ‚±‚Ìƒ‚[ƒh‚ðíœ—\–ñ
		ModeServer::GetInstance()->Del(this);
		// ŽŸ‚Ìƒ‚[ƒh‚ð“o˜^
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	}
	return true;
}

bool ModeTitle::Render()
{
	base::Render();
	DrawGraph(0, 0, mHandle, false);
	return true;
}
