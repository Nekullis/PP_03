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
	//�Q�b�^�[
	static DamageEffect* GetInstance() { return dmgInstance; }
protected:
	class ObjectManager* mManager;
	class DrawPolygonComponent* mDrawPoly;
	std::vector<PARTICLE> mParticleList;
	//�g�p�\�t���O
	bool mUseFlag;
	//�|���S���`��̍ۂɎg���\����
	std::vector<VERTEX3D> mVertex;
	//���_�C���f�b�N�X�z��
	std::vector<unsigned short> mIndex;
	//���Đ�����
	float mPlayTotalTime;
	//���Đ�����
	float mNowPlayTime;
	//���l
	int mColorAlpha;
};

