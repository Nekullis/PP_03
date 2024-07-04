#include "Weapon.h"
#include "WeaponColComponent.h"
#include "DrawComponent.h"
#include "ObjectManager.h"

Weapon::Weapon(ModeBase* game) :ObjectBase(game)
{
	mManager = ObjectManager::GetInstance();
	mFrameIndex = 0;

	//描画用コンポーネント追加
	mDraw = new DrawComponent(this);
	//パスを入れておく
	const char* pass = "res/Model/JointWeapon/Axe.mv1";
	mDraw->LoadPass(pass);
	//アニメーション用にモデルハンドル取得
	mAnimHandle = mDraw->GetHandle();
	//プレイヤーに描画用コンポーネント登録
	mManager->AddDraw(mDraw);

	mCol = new WeaponColComponent(this);
	//半径設定
	float rad = 30.0;
	mCol->SetRadius(rad);
	//線分の長さ設定
	float line_seg = 150.0;
	mCol->SetSeg(line_seg);
	
	mManager->Spawn(this);
}

Weapon::~Weapon()
{
}

void Weapon::Process()
{
	//武器の装備する位置をフレームから取得する
	MATRIX matrix_dxl = MV1GetFrameLocalWorldMatrix(mEquipModelHandle,mFrameIndex);
	//位置を設定する
	MV1SetMatrix(mAnimHandle, matrix_dxl);
	//装備する武器の位置をマトリックスを使って変換し取得する
	mPos = VTransform(Vector3D(0.0, 0.0, 0.0).dxl(), matrix_dxl);
	mTopPos= VTransform(Vector3D(0.0, mCol->GetSeg(), 0.0).dxl(), matrix_dxl);
	//位置を衝突判定コンポーネントに設定する
	mCol->SetPos(mPos);
	mCol->SetTopPos(mTopPos);
}

void Weapon::Render()
{
}
