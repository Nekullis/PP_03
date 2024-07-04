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
	//初期化したいクラスや要素を記述
	mResManager->Init();
	_isLoad = true;
	return true;
}

