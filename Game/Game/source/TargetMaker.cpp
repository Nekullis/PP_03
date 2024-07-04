#include "TargetMaker.h"
#include "ObjectManager.h"
#include "CameraComponent.h"
#include "DrawBillboardComponent.h"
#include "GameCollision.h"
#include <iostream>
#include <sstream>
#include <iomanip>

TargetMaker::TargetMaker(ModeBase* game) :ObjectBase(game)
{
	mManager = ObjectManager::GetInstance();
	mPos = GameCollision::GetInstance()->GetTarget();
	mIsTargetting = false;
	mTexCnt = 0;
	mDraw = new DrawBillboardComponent(this);
	//�摜�p�X�̃n���h�����擾
	for (int i = 0; i < 60; ++i)
	{
		//stringstream�^�̕ϐ��錾
		std::stringstream ss;
		//�摜�p�X�̐�����ς��Ȃ���擾
		//setw(i)�͕��̐ݒ�Bi�ɓ��ꂽ���l�ŕ�(��)��ݒ肷��
		//setfill(i)�͐ݒ肳�ꂽ���𖄂߂鐔���̐ݒ�
		//������g�ݍ��킹�邱�Ƃŕ����񂪎w�肳�ꂽ���ɖ����Ȃ������� '0' �Ŗ��߂�ꐶ�������
		ss << "res/Maker/Maker_" << std::setw(2) << std::setfill('0') << i + 1 << ".png";
		//string�^�Ŏ擾
		std::string pass = std::move(ss.str());
		//�n���h���ϐ��ɑ��
		mTexHandle[i] = LoadGraph(pass.c_str());
	}
	mDraw->SetHandle(mTexHandle[mTexCnt]);
	mManager->AddBillboard(mDraw);
	mManager->Spawn(this);
}

TargetMaker::~TargetMaker()
{
	delete mDraw;
}

void TargetMaker::Process()
{
	mPos = GameCollision::GetInstance()->GetTarget();
	mTexCnt++;
	if (mTexCnt > 60) { mTexCnt = 0; }
	mDraw->SetHandle(mTexHandle[mTexCnt]);
}

void TargetMaker::Render()
{
}
