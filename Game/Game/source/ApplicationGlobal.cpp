#include "ApplicationGlobal.h"
ApplicationGlobal _global;
ApplicationGlobal::ApplicationGlobal()
{
	_isLoad = false;
	
}

ApplicationGlobal::~ApplicationGlobal()
{

}

bool ApplicationGlobal::Init()
{
	_isLoad = false;
	//�������������N���X��v�f���L�q
	mResManager->Init();
	_isLoad = true;
	return true;
}

