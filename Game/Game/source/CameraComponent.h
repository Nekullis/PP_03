#pragma once
#include <utility>
#include "AppFrame.h"
//�Q�[�����̃J���������S�ʂ̃N���X
class CameraComponent : public Component
{
public:
	CameraComponent(ObjectBase* owner,int updateowder = 100);
	virtual ~CameraComponent();
	static CameraComponent* cameraInstance;
	void Update()override;
	//�Q�b�^�[
	static CameraComponent* GetInstance() { return cameraInstance; }
	Vector3D GetTarget() { return mTarget; }
	Vector3D GetDir() { return mDir; }
	Vector3D GetPos() { return mPos; }
	//�Z�b�^�[
	void SetTarget(Vector3D vec) { mTarget = vec; }
protected:
	GameXPad* mPad;
	//�J�����ʒu
	Vector3D mPos;
	Vector3D mDir;
	//�J���������_
	Vector3D mTarget;
	//�ŒZ�`�拗��
	float mNear;
	//�Œ��`�拗��
	float mFar;
	//�΂˒萔
	float mSpring;
	//�����萔
	float mDampFactor;
	//�ʒu�Ƒ��x
	Vector3D mCurrentPos;
	Vector3D mCurrentVelocity;
};

