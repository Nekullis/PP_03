#pragma once
#include "AppFrame.h"
class MoveComponent : public Component
{
public:
	MoveComponent(class ObjectBase* owner, int updateowder = 10);
	virtual ~MoveComponent();
	//�X�V
	void Update()override;
	//�Q�b�^�[
	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	//�Z�b�^�[
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
protected:
	//��]����(���W�A��/�b)
	float mAngularSpeed;
	//�O�i�^������(�P�ʒ�/�b)
	float mForwardSpeed;
};

