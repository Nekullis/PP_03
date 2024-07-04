#include"ApplicationGlobal.h"
#include "ModeGameClear.h"
#include "ModeTitle.h"

bool ModeGameClear::Initialize()
{
	if (!ModeBase::Initialize()) { return false; }
	mHandle = _global.mResManager->LoadGraph("res/Graph/GameClear/GameClear.png");
	mPad = new GameXPad();
	return true;
}

bool ModeGameClear::Terminate()
{
	ModeBase::Terminate();
	delete mPad;
	return true;
}

bool ModeGameClear::Process()
{
	ModeBase::Process();
	mPad->Input();
	if (mPad->GetXTrg(XINPUT_BUTTON_B))
	{
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "game");
	}
	return true;
}

bool ModeGameClear::Render()
{
	ModeBase::Render();
	DrawGraph(0, 0, mHandle, false);
	return true;
}
