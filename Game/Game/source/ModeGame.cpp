#include "ModeGame.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyMob.h"
#include "TargetMaker.h"
#include "ObjectManager.h"
#include "GameCollision.h"
#include "DamageEffect.h"
#include "CollisionManager.h"
#include "ModeGameClear.h"

ModeGame* ModeGame::gameInstance = nullptr;
bool ModeGame::Initialize()
{
	gameInstance = this;
	if (!ModeBase::Initialize()) { return false; }
	mGameClearFlag = false;
	//�I�u�W�F�N�g�}�l�[�W���[������
	mObjManager = new ObjectManager();
	//�R���W�����n���̃N���X������
	mGameCol = new GameCollision();
	mColManager = new CollisionManager();
	Register();
	return true;
}

bool ModeGame::Terminate()
{
	ModeBase::Terminate();
	delete mObjManager;
	delete mGameCol;
	delete mColManager;
	delete mPlayer;
	delete mEnemy;
	delete mStage;
	return true;
}

void ModeGame::Register()
{
	//�v���C���[�ǉ�
	mPlayer = new Player(this);
	////�}�[�J�[�ǉ�
	//TargetMaker* maker = new TargetMaker(this);
	//�G�ǉ�
	mEnemy = new EnemyMob(this);
	mEnemy->SetPos(Vector3D(-500, 100, 1000));
	mDamageEffect = new DamageEffect(this);
	//�X�e�[�W�ǉ�
	mStage = new Stage(this);
}

bool ModeGame::Process()
{
	//�e�v���Z�X�̍X�V
	ModeBase::Process();
	mColManager->Update();
	mObjManager->Process();
	mGameCol->Update();
	if (mGameClearFlag)
	{
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeGameClear(), 1, "clear");
	}
	return true;
}

bool ModeGame::Render()
{
	//z�o�b�t�@�[�L����
	SetUseZBuffer3D(true);
	//z�o�b�t�@�[�������ݐݒ�
	SetWriteZBuffer3D(true);
	//���C�g�L����
	SetUseLighting(true);
	//���C�g�^�C�v���f�B���N�V���i���^�C�v�ɐݒ�
	ChangeLightTypeDir(Vector3D(0,-1,1).dxl());
	ModeBase::Render();
	mObjManager->Render();
	return true;
}




