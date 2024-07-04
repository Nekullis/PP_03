#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeTitle.h"
//����
ApplicationMain _gApplication;
bool ApplicationMain::Initialize(HINSTANCE instance)
{
	if (!base::Initialize(instance)) { return false; }
	//�O���[�o���N���X���̊֐�������
	_init = new std::thread(&ApplicationGlobal::Init, &_global);
	ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	return true;
}

bool ApplicationMain::Terminate()
{
	base::Terminate();
	return true;
}

bool ApplicationMain::Input()
{
	base::Input();
	return true;
}

bool ApplicationMain::Process()
{
	base::Process();
	/*if (_global._isLoad && _init != nullptr)
	{
		_init->detach();
		delete _init;
		_init = nullptr;
	}*/

	return true;
}

bool ApplicationMain::Render()
{
	base::Render();
	return true;
}
