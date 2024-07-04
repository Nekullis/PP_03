#include "InputComponent.h"
#include "CameraComponent.h"
#include "Player.h"

InputComponent::InputComponent(ObjectBase* owner, int updateowder) :MoveComponent(owner, updateowder)
{
	//コントローラー初期化
	mPad = new GameXPad();
}

InputComponent::~InputComponent()
{
}

void InputComponent::Update()
{
	mPad->Input();
	//アナログパッドの値をatan2関数で角度を得る
	float dir = atan2(-mPad->GetXLy(), -mPad->GetXLx());
	float com_dir_y = CameraComponent::GetInstance()->GetDir()._y;
	//アナログパッドが動いているのなら
	if(mPad->IsInputStickLeft())
	{
		//参照オブジェクトの位置を取得
		Vector3D pos = mOwner->GetPos();
		//セッターで得た速度を代入
		float speed = mForwardSpeed;
		//y軸の回転行列を得る
		Matrix3D matrix = ::MGetRotY(com_dir_y);
		//移動量を得る
		Vector3D move{ speed * cosf(dir) ,0,speed * sinf(dir) };
		//移動量とカメラの回転値の積を求め、カメラの向きと前方ベクトルを一致させる
		move = move * matrix;
		//位置に反映
		pos += move;
		//セッターでプレイヤーの位置情報に代入
		mOwner->SetPos(pos);
		//移動後の回転値を求める
		Vector3D rot = Vector3D(0, -(dir + MyMath::DegToRad(90.0f))+ com_dir_y, 0);
		//プレイヤーの回転値に反映
		mOwner->SetRotation(rot);
	}
	
}
