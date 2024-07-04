#include "InputComponent.h"
#include "CameraComponent.h"
#include "Player.h"

InputComponent::InputComponent(ObjectBase* owner, int updateowder) :MoveComponent(owner, updateowder)
{
	//�R���g���[���[������
	mPad = new GameXPad();
}

InputComponent::~InputComponent()
{
}

void InputComponent::Update()
{
	mPad->Input();
	//�A�i���O�p�b�h�̒l��atan2�֐��Ŋp�x�𓾂�
	float dir = atan2(-mPad->GetXLy(), -mPad->GetXLx());
	float com_dir_y = CameraComponent::GetInstance()->GetDir()._y;
	//�A�i���O�p�b�h�������Ă���̂Ȃ�
	if(mPad->IsInputStickLeft())
	{
		//�Q�ƃI�u�W�F�N�g�̈ʒu���擾
		Vector3D pos = mOwner->GetPos();
		//�Z�b�^�[�œ������x����
		float speed = mForwardSpeed;
		//y���̉�]�s��𓾂�
		Matrix3D matrix = ::MGetRotY(com_dir_y);
		//�ړ��ʂ𓾂�
		Vector3D move{ speed * cosf(dir) ,0,speed * sinf(dir) };
		//�ړ��ʂƃJ�����̉�]�l�̐ς����߁A�J�����̌����ƑO���x�N�g������v������
		move = move * matrix;
		//�ʒu�ɔ��f
		pos += move;
		//�Z�b�^�[�Ńv���C���[�̈ʒu���ɑ��
		mOwner->SetPos(pos);
		//�ړ���̉�]�l�����߂�
		Vector3D rot = Vector3D(0, -(dir + MyMath::DegToRad(90.0f))+ com_dir_y, 0);
		//�v���C���[�̉�]�l�ɔ��f
		mOwner->SetRotation(rot);
	}
	
}
