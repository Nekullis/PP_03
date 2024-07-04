#pragma once
#include "AppFrame.h"
class GameCollision
{
public:
	static GameCollision* colInstance;
	GameCollision();
	virtual ~GameCollision();
	void Update();
	void CameraTerget();
	//ゲッター
	static GameCollision* GetInstance() { return colInstance; }
	bool GetLockOn() { return mIsLock; }
	Vector3D GetTarget() { return mCamTarget; }
protected:
	//ロックオンしているか
	bool mIsLock;
	float mSearchRot;
	Vector3D mCamTarget;
};

