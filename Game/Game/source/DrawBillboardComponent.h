#pragma once
#include "AppFrame.h"
class DrawBillboardComponent : public Component
{
public:
	DrawBillboardComponent(class ObjectBase* owner, int updateowder = 150);
	virtual ~DrawBillboardComponent();
	void Update()override;
	//�Z�b�^�[
	void SetHandle(int handle) { mHandle = handle; }
protected:
	int mHandle;
};

