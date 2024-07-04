#include "CameraComponent.h"
#include "GameCollision.h"

CameraComponent* CameraComponent::cameraInstance = nullptr;
CameraComponent::CameraComponent(ObjectBase* owner, int updateowder) : Component(owner, updateowder)
{
	cameraInstance = this;
	//�����_������
	mTarget = { 0 };
	//�ʒu������
	mPos = { 0 };
	mDir = Vector3D(0, mOwner->GetRotation()._y, 0);
	//�ŒZ�`�拗��������
	mNear = 20;
	//�Œ��`�拗��������
	mFar = 50000;
	//�΂˒萔
	mSpring = 0.1;
	//�����萔
	mDampFactor = 0.8;
	mCurrentPos = mPos;
	mCurrentVelocity;
	//�Q�[���p�b�h�̎擾
	mPad = GameXPad::GetInstance();
	mOwner->AddComponent(this);
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Update()
{
	Component::Update();
	//�ʒu�ݒ�
	Vector3D pos;
	//�p�b�h���͂Ŋp�x����
	if (mPad->GetXRx() < 0) { mDir._y -= 0.05; }
	if (mPad->GetXRx() > 0) { mDir._y += 0.05; }
	
	
	//�����_�ݒ�
	Vector3D target;
	if(GameCollision::GetInstance()->GetLockOn()) 
	{ 
		//�J�����ʒu���v���[���[�ʒu�ɋ��^���W�n����ω��������W�n�𑫂������W�ɂ���
		pos = mOwner->GetPos() + MyMath::ConvertToCartesian(mDir, 1000);
		pos._y = 500;
		target = GameCollision::GetInstance()->GetTarget(); 
	}
	else 
	{ 
		//�J�����ʒu���v���[���[�ʒu�ɋ��^���W�n����ω��������W�n�𑫂������W�ɂ���
		pos = mOwner->GetPos() + MyMath::ConvertToCartesian(mDir, 700);
		//�㓪����菭�����߂̈ʒu�ɂ���
		pos._y += 300;
		target = Vector3D(mOwner->GetPos()); 
	}
	//mPos = pos;
	//�΂˗͌v�Z
	Vector3D springforce = -mSpring * (mCurrentPos - pos);
	//�����͌v�Z
	Vector3D dampforce = -mDampFactor * mCurrentVelocity;
	//�����͂��v�Z���Ă���
	Vector3D force = springforce + dampforce;
	Vector3D accseler = force;
	//���x�X�V
	mCurrentVelocity += accseler;
	//�ʒu�X�V
	mCurrentPos += mCurrentVelocity;
	mPos = mCurrentPos;
	//�J�����`�ʂ̍ŒZ�����A�Œ�������ݒ肷��
	SetCameraNearFar(mNear, mFar);
	//�J�����̈ʒu�ƒ����_�𔽉f����
	SetCameraPositionAndTarget_UpVecY(mCurrentPos.dxl(), target.dxl());
}




