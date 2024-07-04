#include "Weapon.h"
#include "WeaponColComponent.h"
#include "DrawComponent.h"
#include "ObjectManager.h"

Weapon::Weapon(ModeBase* game) :ObjectBase(game)
{
	mManager = ObjectManager::GetInstance();
	mFrameIndex = 0;

	//�`��p�R���|�[�l���g�ǉ�
	mDraw = new DrawComponent(this);
	//�p�X�����Ă���
	const char* pass = "res/Model/JointWeapon/Axe.mv1";
	mDraw->LoadPass(pass);
	//�A�j���[�V�����p�Ƀ��f���n���h���擾
	mAnimHandle = mDraw->GetHandle();
	//�v���C���[�ɕ`��p�R���|�[�l���g�o�^
	mManager->AddDraw(mDraw);

	mCol = new WeaponColComponent(this);
	//���a�ݒ�
	float rad = 30.0;
	mCol->SetRadius(rad);
	//�����̒����ݒ�
	float line_seg = 150.0;
	mCol->SetSeg(line_seg);
	
	mManager->Spawn(this);
}

Weapon::~Weapon()
{
}

void Weapon::Process()
{
	//����̑�������ʒu���t���[������擾����
	MATRIX matrix_dxl = MV1GetFrameLocalWorldMatrix(mEquipModelHandle,mFrameIndex);
	//�ʒu��ݒ肷��
	MV1SetMatrix(mAnimHandle, matrix_dxl);
	//�������镐��̈ʒu���}�g���b�N�X���g���ĕϊ����擾����
	mPos = VTransform(Vector3D(0.0, 0.0, 0.0).dxl(), matrix_dxl);
	mTopPos= VTransform(Vector3D(0.0, mCol->GetSeg(), 0.0).dxl(), matrix_dxl);
	//�ʒu���Փ˔���R���|�[�l���g�ɐݒ肷��
	mCol->SetPos(mPos);
	mCol->SetTopPos(mTopPos);
}

void Weapon::Render()
{
}
