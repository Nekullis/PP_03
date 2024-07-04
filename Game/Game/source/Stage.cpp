#include "Stage.h"
#include "DrawComponent.h"
#include "ObjectManager.h"
Stage* Stage::stageInstance = nullptr;
Stage::Stage(ModeBase* game):ObjectBase(game)
{
	stageInstance = this;
	mPos = Vector3D(0, -100, 0);
	mRotation = Vector3D(0, 0, 0);
	mManager = ObjectManager::GetInstance();
	//�X�e�[�W�`��p�R���|�[�l���g������
	DrawComponent* draw_stage = new DrawComponent(this);
	//�p�X�����Ă���
	const char* pass_stage = "res/Model/Stage/StageModel.mv1";
	//�Z�b�^�[�Ńp�X��o�^
	draw_stage->LoadPass(pass_stage);
	//�X�e�[�W�ʒu�ݒ�
	Vector3D stage_pos = Vector3D(0, -10, 0);
	draw_stage->SetPos(stage_pos);
	mManager->AddDraw(draw_stage);
	//�}�l�[�W���[�ɃX�e�[�W�o�^
	mManager->Spawn(this);
}

Stage::~Stage()
{
}

void Stage::Process()
{
	ObjectBase::Process();
}

void Stage::Render()
{
	ObjectBase::Render();
}
