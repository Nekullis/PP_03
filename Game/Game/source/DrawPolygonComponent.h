#pragma once
#include "AppFrame.h"
#include "DrawComponent.h"
class DrawPolygonComponent : public DrawComponent
{
public:
	DrawPolygonComponent(class ObjectBase* owner, int updateowder = 50);
	virtual ~DrawPolygonComponent();
	void Update()override;
	//�Q�b�^�[
	bool GetUseFlag() { return mUseFlag; }
	std::vector<VERTEX3D> GetVertex() { return mVertex; }
	std::vector<unsigned short> GetIndex() { return mIndex; }
	float GetTotalTime() { return mPlayTotalTime; }
	float GetPlayTime() { return mNowPlayTime; }
	COLOR_U8 GetColor() { return mColor; }
	int GetAlpha(){ return mColorAlpha; }
	//�Z�b�^�[
	void SetUseFlag(bool flag) { mUseFlag = flag; }
	void SetVertex(std::vector<VERTEX3D>& vertex);
	void SetIndeex(std::vector<unsigned short>& index);
	void SetAlpha(int alpha){ mColorAlpha = alpha; }
	void SetTotalTime(float time) { mPlayTotalTime = time; }
	void SetPlayTime(float time) { mNowPlayTime = time; }
protected:
	//�g�p�\�t���O
	bool mUseFlag;
	//�|���S���`��̍ۂɎg���\����
	std::vector<VERTEX3D> mVertex;
	int mVertexCnt;
	//���_�C���f�b�N�X�z��
	std::vector<unsigned short> mIndex;
	int mIndexCnt;
	//���Đ�����
	float mPlayTotalTime;
	//���Đ�����
	float mNowPlayTime;
	//�J���[
	COLOR_U8 mColor;
	//���l
	int mColorAlpha;
};

