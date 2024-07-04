#include "ApplicationGlobal.h"
#include "ModeGameOver.h"
#include "ModeTitle.h"

bool ModeGameOver::Initialize()
{
	if (!ModeBase::Initialize()) { return false; }
	//�摜������
	mHandle = _global.mResManager->LoadGraph("res/Graph/GameClear/GameClear.png");
	//�Q�[���p�b�h	�ǉ�
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
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "game");
	}
	return true;
}

bool ModeGameOver::Render()
{
	ModeBase::Render();
	//�摜�`��
	DrawGraph(0, 0, mHandle, false);
	return true;
}
