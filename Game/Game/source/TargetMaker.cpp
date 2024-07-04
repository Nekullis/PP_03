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
	//画像パスのハンドルを取得
	for (int i = 0; i < 60; ++i)
	{
		//stringstream型の変数宣言
		std::stringstream ss;
		//画像パスの数字を変えながら取得
		//setw(i)は幅の設定。iに入れた数値で幅(桁)を設定する
		//setfill(i)は設定された幅を埋める数字の設定
		//これらを組み合わせることで文字列が指定された幅に満たない部分が '0' で埋められ生成される
		ss << "res/Maker/Maker_" << std::setw(2) << std::setfill('0') << i + 1 << ".png";
		//string型で取得
		std::string pass = std::move(ss.str());
		//ハンドル変数に代入
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
