#pragma once
#include "AppFrame.h"
#include "DrawComponent.h"
class DrawPolygonComponent : public DrawComponent
{
public:
	DrawPolygonComponent(class ObjectBase* owner, int updateowder = 50);
	virtual ~DrawPolygonComponent();
	void Update()override;
	//ゲッター
	bool GetUseFlag() { return mUseFlag; }
	std::vector<VERTEX3D> GetVertex() { return mVertex; }
	std::vector<unsigned short> GetIndex() { return mIndex; }
	float GetTotalTime() { return mPlayTotalTime; }
	float GetPlayTime() { return mNowPlayTime; }
	COLOR_U8 GetColor() { return mColor; }
	int GetAlpha(){ return mColorAlpha; }
	//セッター
	void SetUseFlag(bool flag) { mUseFlag = flag; }
	void SetVertex(std::vector<VERTEX3D>& vertex);
	void SetIndeex(std::vector<unsigned short>& index);
	void SetAlpha(int alpha){ mColorAlpha = alpha; }
	void SetTotalTime(float time) { mPlayTotalTime = time; }
	void SetPlayTime(float time) { mNowPlayTime = time; }
protected:
	//使用可能フラグ
	bool mUseFlag;
	//ポリゴン描画の際に使う構造体
	std::vector<VERTEX3D> mVertex;
	int mVertexCnt;
	//頂点インデックス配列
	std::vector<unsigned short> mIndex;
	int mIndexCnt;
	//総再生時間
	float mPlayTotalTime;
	//現再生時間
	float mNowPlayTime;
	//カラー
	COLOR_U8 mColor;
	//α値
	int mColorAlpha;
};

