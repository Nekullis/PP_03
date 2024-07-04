#pragma once
#include "AppFrame.h"
class TargetMaker : public ObjectBase
{
public:
	TargetMaker(ModeBase* game);
	virtual ~TargetMaker();
	void Process()override;
	void Render()override;
	//�Q�b�^�[
	int GetHandle() { return mTexHandle[mTexCnt]; }
protected:
	int mTexCnt;
	int mTexHandle[60];
	class ObjectManager* mManager;
	class DrawBillboardComponent* mDraw;
};

