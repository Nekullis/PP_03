#pragma once
#include "PolygonEffect.h"
class DamageEffect : public PolygonEffect
{
public:
	static DamageEffect* dmgInstance;
	struct PARTICLE
	{
		bool UseFlag;
		Vector3D Pos;
		Vector3D Velocity;
		COLOR_U8 Color;
	};
	DamageEffect(ModeBase* game);
	virtual ~DamageEffect();
	void Start(int allpolynum);
	void Process()override;
	void Render()override;
	//ゲッター
	static DamageEffect* GetInstance() { return dmgInstance; }
protected:
	class ObjectManager* mManager;
	class DrawPolygonComponent* mDrawPoly;
	std::vector<PARTICLE> mParticleList;
	//使用可能フラグ
	bool mUseFlag;
	//ポリゴン描画の際に使う構造体
	std::vector<VERTEX3D> mVertex;
	//頂点インデックス配列
	std::vector<unsigned short> mIndex;
	//総再生時間
	float mPlayTotalTime;
	//現再生時間
	float mNowPlayTime;
	//α値
	int mColorAlpha;
};

