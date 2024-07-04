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
	//�Q�b�^�[
	static GameCollision* GetInstance() { return colInstance; }
	bool GetLockOn() { return mIsLock; }
	Vector3D GetTarget() { return mCamTarget; }
protected:
	//���b�N�I�����Ă��邩
	bool mIsLock;
	float mSearchRot;
	Vector3D mCamTarget;
};

