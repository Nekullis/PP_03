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
	//ロックオン用トリガが入力された
	if (pad->GetXTrg(XINPUT_BUTTON_LEFT_THUMB)) { mIsLock = 1 - mIsLock; }
	if (mIsLock)
	{
		//カメラ位置を代入
		Vector3D cam_s_dis = camera->GetPos();
		//カメラ注視点回転角(y軸の回転行列)
		Matrix3D rot_y = ::MGetRotY(mSearchRot);
		//カメラのロックオンに使う線分、カメラの位置からの差分値
		Vector3D add = Vector3D(0.0, 0.0, 2000.0);
		//カメラ位置と差分の加算しそこに回転値を入れる
		Vector3D cam_e_dis = cam_s_dis + add * rot_y;
		//最も近い敵を探すための距離
		float closest_distance = FLT_MAX; 
		Vector3D closest_enemy_pos;
		//線分と線分の最短距離を求める際に使う変数。入れるだけでいいので実際、値は使っていない
		Vector3D v1m = Vector3D(0.0, 0.0, 0.0);
		Vector3D v2m = Vector3D(0.0, 0.0, 0.0);
		double t1 = 0.0;
		double t2 = 0.0;
		//オブジェクトの数だけ回す
		for (auto&& obj : object_list)
		{
			//敵以外は候補に入れない
			if (!obj->GetIsTarget()) { continue; }
			//敵の位置
			Vector3D enemy_pos = obj->GetPos();
			//敵の高さを考慮
			Vector3D enemy_top_pos = enemy_pos + Vector3D(0.0f, 100.0f, 0.0f); 
			//線分と線分の最短距離を求める
			float len = MyMath::DisSegAndSeg(cam_s_dis, cam_e_dis, v1m, t1, enemy_pos, enemy_top_pos, v2m, t2);
			//最短距離が今の最大値よりも小さく敵のカメラ用半径よりも大きいとき
			if(len < closest_distance && len <= 1500.0f)
			{
				//最短距離の更新
				closest_distance = len;
				//注視点の変更
				closest_enemy_pos = enemy_pos;
				//ロックオンをtrueに
				mIsLock = true;
			}
		}
		//最も近い敵をターゲット
		mCamTarget = closest_enemy_pos;
	}
	
}


