#pragma once
#include <utility>
#include "AppFrame.h"
//ゲーム内のカメラ処理全般のクラス
class CameraComponent : public Component
{
public:
	CameraComponent(ObjectBase* owner,int updateowder = 100);
	virtual ~CameraComponent();
	static CameraComponent* cameraInstance;
	void Update()override;
	//ゲッター
	static CameraComponent* GetInstance() { return cameraInstance; }
	Vector3D GetTarget() { return mTarget; }
	Vector3D GetDir() { return mDir; }
	Vector3D GetPos() { return mPos; }
	//セッター
	void SetTarget(Vector3D vec) { mTarget = vec; }
protected:
	GameXPad* mPad;
	//カメラ位置
	Vector3D mPos;
	Vector3D mDir;
	//カメラ注視点
	Vector3D mTarget;
	//最短描画距離
	float mNear;
	//最長描画距離
	float mFar;
	//ばね定数
	float mSpring;
	//減衰定数
	float mDampFactor;
	//位置と速度
	Vector3D mCurrentPos;
	Vector3D mCurrentVelocity;
};

