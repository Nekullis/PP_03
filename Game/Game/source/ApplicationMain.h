#pragma once
#include "AppFrame.h"
//#include <thread>
//�A�v���P�[�V�����̃��C�������B�������烂�[�h�ψڂȂǂ��s���N���X
class ApplicationMain : public ApplicationBase
{
	using base = ApplicationBase;
public:
	bool Initialize(HINSTANCE instance)override;
	bool Terminate()override;
	bool Input();
	bool Process();
	bool Render();
protected:
	//������
	std::thread* _init;
};

