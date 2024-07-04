#include "Player.h"
#include "AppFrame.h"
#include "ObjectManager.h"
#include "AttackManager.h"
#include "DrawComponent.h"
#include "CameraComponent.h"
#include "InputComponent.h"
#include "CapsuleColComponent.h"
#include "Weapon.h"
#include "WeaponColComponent.h"
#include "AttackState.h"

Player* Player::plInstance = nullptr;
Player::Player(ModeBase* game):chara(game)
{
	plInstance = this;
	mManager = ObjectManager::GetInstance();
	mHp = 100;
	//�ҋ@��Ԃ�
	mAnimation= ANIMATION::WAIT;
	//�ʒu������
	mPos = Vector3D(0, 100, 0);
	//����������
	mRotation = Vector3D(0, MyMath::DegToRad(180), 0);
	//�����A�j���[�V�����A�^�b�`�ԍ��ݒ�
	mAttachNum = 0;
	//�A�j���[�V�����o�^
	RegisterAnimation();

	//�`��p�R���|�[�l���g�ǉ�
	//�v���C���[�`��p�R���|�[�l���g�ǉ�
	mDraw = new DrawComponent(this);
	//�p�X�����Ă���
	const char* pass = "res/Model/Character/Player/Player.mv1";
	//�Z�b�^�[�Ńp�X��o�^
	mDraw->LoadPass(pass);
	//�A�j���[�V�����p�Ƀ��f���n���h���擾
	mAnimHandle = mDraw->GetHandle();
	//�v���C���[�ɕ`��p�R���|�[�l���g�o�^
	mManager->AddDraw(mDraw);

	//�I�u�W�F�N�g(����)�ǉ�
	//���평����
	mWeapon = new Weapon(game);
	//����̏Փ˔���R���|�[�l���g�̃O���[�v���v���C���[��
	mWeapon->GetColComponent()->SetGroup(CollisionComponent::COLLISIONGROUP::PLAYER);
	//���피�a������
	float weapon_rad = 50.0;
	mWeapon->SetRadius(weapon_rad);
	//���������t���[���ݒ�
	int frame_index= MV1SearchFrame(mAnimHandle, "joint_sword");
	mWeapon->SetFrameIndex(frame_index);
	mWeapon->SetEquipHandle(mAnimHandle);

	//���͏����̃R���|�[�l���g�ǉ�
	//���͏����̃R���|�[�l���g������
	InputComponent* input = new InputComponent(this);
	//�v���C���[���x������
	input->SetForwardSpeed(20);

	//�J�����R���|�[�l���g�ǉ�
	//�v���C���[�ɃJ�����R���|�[�l���g�������A�ǉ�
	CameraComponent* camera = new CameraComponent(this);

	//�Փ˔���p�R���|�[�l���g�ǉ�
	//�Փ˔���p�R���|�[�l���g������
	mCol = new CapsuleColComponent(this);
	//�Փ˔���R���|�[�l���g�̃O���[�v���v���C���[��
	mCol->SetGroup(CollisionComponent::COLLISIONGROUP::PLAYER);
	//���a�ݒ�
	float col_rad = 30.0;
	mCol->SetRadius(col_rad);
	//�����̒����ݒ�
	float line_seg = 170.0;
	mCol->SetSeg(line_seg);
	//�}�l�[�W���[�Ƀv���C���[�o�^
	mManager->Spawn(this);

	//�U���ǉ�
	//�U���}�l�[�W���[������
	mAtkManager = new AttackManager();
	AttackState attack_state[4];
	AttackState::ATTACK attack[4] =
	{
		{
			//�A�j���[�V����
			Player::ANIMATION::NONE,
			//���[�V�����g�[�^���t���[��
			0.0,
			//�{�^�����͗P�\�J�n�t���[��
			0.0,
			//�{�^�����͗P�\�I���t���[��
			0.0,
			//���[�V�����؂�ւ��J�n�t���[��
			0.0,
			//�U������J�n�t���[��
			0.0,
			//�U������I���t���[��
			0.0,
			//�Փ˔���͈�
			0.0,
			//�h���\��
			true
		},
		{
			//�A�j���[�V����
			Player::ANIMATION::FIRSTATTACK,
			//���[�V�����g�[�^���t���[��
			65.0,
			//�{�^�����͗P�\�J�n�t���[��
			15.0,
			//�{�^�����͗P�\�I���t���[��
			60.0,
			//���[�V�����؂�ւ��J�n�t���[��
			40.0,
			//�U������J�n�t���[��
			25.0,
			//�U������I���t���[��
			35.0,
			//�Փ˔���͈�
			50.0,
			//�h���\��
			true
		},
		{
			//�A�j���[�V����
			Player::ANIMATION::SECONDATTACK,
			//���[�V�����g�[�^���t���[��
			72.0,
			//�{�^�����͗P�\�J�n�t���[��
			15.0,
			//�{�^�����͗P�\�I���t���[��
			70.0,
			//���[�V�����؂�ւ��J�n�t���[��
			28.0,
			//�U������J�n�t���[��
			5.0,
			//�U������I���t���[��
			30.0,
			//�Փ˔���͈�
			50.0,
			//�h���\��
			true
		},
		{
			//�A�j���[�V����
			Player::ANIMATION::THIRDATTACK,
			//���[�V�����g�[�^���t���[��
			90.0,
			//�{�^�����͗P�\�J�n�t���[��
			25.0,
			//�{�^�����͗P�\�I���t���[��
			54.0,
			//���[�V�����؂�ւ��J�n�t���[��
			0.0,
			//�U������J�n�t���[��
			31.0,
			//�U������I���t���[��
			54.0,
			//�Փ˔���͈�
			50.0,
			//�h���\��
			false
		}
	};
	for (int i = 0; i < 4; i++)
	{
		attack_state[i].SetState(attack[i]);
		mAtkManager->AddAttack(i, attack_state[i]);
	}
	


}

Player::~Player()
{
	delete mDraw;
	delete mCol;
	delete mWeapon;
	delete mAtkManager;
	MV1DetachAnim(mAnimHandle, mAnimAttachIndex);
}

void Player::RegisterAnimation()
{
	Character::RegisterAnimation();
}

void Player::Process()
{
	chara::Process();
	//�Փ˔���p�̈ʒu�ݒ�
	mCol->SetPos(mPos);
	mDraw->SetPos(mPos);
	//�X�e�B�b�N���X���Ă��邩
	if (!mAtkManager->IsAttackMotion())
	{
		if (GameXPad::GetInstance()->IsInputStickLeft())
		{
			//�A�j���[�V�����������
			mAnimation = ANIMATION::WALK;
		}
		else
		{
			//�A�j���[�V������҂���
			mAnimation = ANIMATION::WAIT;
		}
	}
	
	//�A�j���[�V������1�t���[���O�ƈႤ�̂Ȃ�
	if (mAnimation != oldAnimation)
	{
		int old_attach_index = mAnimAttachIndex;
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(mAnimHandle, mAnimAttachIndex);
		//�A�j���[�V�����ɂ���ăA�^�b�`����ԍ���ύX����
		switch (mAnimation)
		{
		//�ҋ@
		case ANIMATION::WAIT:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 0, -1, false);
			break;
		//���s
		case ANIMATION::WALK:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 7, -1, false);
			break;
		//�A���U��1����
		case ANIMATION::FIRSTATTACK:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 2, -1, false);
			break;
		//�A���U��2����
		case ANIMATION::SECONDATTACK:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 3, -1, false);
			break;
		//�A���U��3����
		case ANIMATION::THIRDATTACK:
			mAnimAttachIndex = MV1AttachAnim(mAnimHandle, 4, -1, false);
			break;
		}
		//�Đ����ԃ��Z�b�g
		mAnimPlayTime = 0;
		//���Đ����ԃZ�b�g
		mAnimTotalTime = MV1GetAttachAnimTotalTime(mAnimHandle, mAnimAttachIndex);
	}
	//�A�j���[�V�����J�E���g���Z
	mAnimPlayTime += 1.0f;
	//���Đ����Ԃɓ��B�����烊�Z�b�g
	if(mAnimPlayTime >= mAnimTotalTime) { mAnimPlayTime = 0.0f; }
	//���Đ����Ԃ��Z�b�g
	MV1SetAttachAnimTime(mAnimHandle, mAnimAttachIndex, mAnimPlayTime);
	oldAnimation = mAnimation;
	//�U�������X�V
	mAtkManager->Update();
}

void Player::Render()
{
	chara::Render();
}
