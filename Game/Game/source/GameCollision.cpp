#include "GameCollision.h"
#include "CameraComponent.h"
#include "ObjectManager.h"
#include "InputComponent.h"
#include "Player.h"
#include "Stage.h"

GameCollision* GameCollision::colInstance = nullptr;
GameCollision::GameCollision()
{
	colInstance = this;
	mIsLock = false;
	mSearchRot = 0;
	mCamTarget = Vector3D(0,0,0);
}

GameCollision::~GameCollision()
{
}

void GameCollision::Update()
{
	CameraTerget();
}

void GameCollision::CameraTerget()
{
	Vector3D tarpos = Vector3D(0.0, 0.0, 0.0);
	CameraComponent* camera = CameraComponent::GetInstance();
	GameXPad* pad = GameXPad::GetInstance();
	std::list<ObjectBase*> object_list = ObjectManager::GetInstance()->GetObjectList();
	//���b�N�I���p�g���K�����͂��ꂽ
	if (pad->GetXTrg(XINPUT_BUTTON_LEFT_THUMB)) { mIsLock = 1 - mIsLock; }
	if (mIsLock)
	{
		//�J�����ʒu����
		Vector3D cam_s_dis = camera->GetPos();
		//�J���������_��]�p(y���̉�]�s��)
		Matrix3D rot_y = ::MGetRotY(mSearchRot);
		//�J�����̃��b�N�I���Ɏg�������A�J�����̈ʒu����̍����l
		Vector3D add = Vector3D(0.0, 0.0, 2000.0);
		//�J�����ʒu�ƍ����̉��Z�������ɉ�]�l������
		Vector3D cam_e_dis = cam_s_dis + add * rot_y;
		//�ł��߂��G��T�����߂̋���
		float closest_distance = FLT_MAX; 
		Vector3D closest_enemy_pos;
		//�����Ɛ����̍ŒZ���������߂�ۂɎg���ϐ��B����邾���ł����̂Ŏ��ہA�l�͎g���Ă��Ȃ�
		Vector3D v1m = Vector3D(0.0, 0.0, 0.0);
		Vector3D v2m = Vector3D(0.0, 0.0, 0.0);
		double t1 = 0.0;
		double t2 = 0.0;
		//�I�u�W�F�N�g�̐�������
		for (auto&& obj : object_list)
		{
			//�G�ȊO�͌��ɓ���Ȃ�
			if (!obj->GetIsTarget()) { continue; }
			//�G�̈ʒu
			Vector3D enemy_pos = obj->GetPos();
			//�G�̍������l��
			Vector3D enemy_top_pos = enemy_pos + Vector3D(0.0f, 100.0f, 0.0f); 
			//�����Ɛ����̍ŒZ���������߂�
			float len = MyMath::DisSegAndSeg(cam_s_dis, cam_e_dis, v1m, t1, enemy_pos, enemy_top_pos, v2m, t2);
			//�ŒZ���������̍ő�l�����������G�̃J�����p���a�����傫���Ƃ�
			if(len < closest_distance && len <= 1500.0f)
			{
				//�ŒZ�����̍X�V
				closest_distance = len;
				//�����_�̕ύX
				closest_enemy_pos = enemy_pos;
				//���b�N�I����true��
				mIsLock = true;
			}
		}
		//�ł��߂��G���^�[�Q�b�g
		mCamTarget = closest_enemy_pos;
	}
	
}


