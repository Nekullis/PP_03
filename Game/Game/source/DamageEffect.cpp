#include "DamageEffect.h"
#include "ObjectManager.h"
#include "DrawPolygonComponent.h"

DamageEffect* DamageEffect::dmgInstance = nullptr;
DamageEffect::DamageEffect(ModeBase* game) :PolygonEffect(game)
{
	dmgInstance = this;
	mManager = ObjectManager::GetInstance();
	mPlayTotalTime = 60;
	
	mColorAlpha = 255;
	mManager->Spawn(this);
}

DamageEffect::~DamageEffect()
{
	delete mDrawPoly;
	mIndex.clear();
	mVertex.clear();
}

void DamageEffect::Start(int allpolynum)
{
	if (mDrawPoly != nullptr)
	{
		delete mDrawPoly;
		mDrawPoly = nullptr;
	}
	mParticleList.clear();
	mNowPlayTime = 0;
	mUseFlag = true;
	for (int i = 0; i < allpolynum; i++)
	{
		PARTICLE particle;
		particle.Pos = mPos;
		particle.Velocity._x = (float)(rand() % 20 - 10);
		particle.Velocity._y = (float)(rand() % 20 - 10);
		particle.Velocity._z = (float)(rand() % 20 - 10);
		COLOR_U8 color = GetColorU8(255, rand() % 10, rand() % 10, mColorAlpha);
		particle.Color = color;
		mParticleList.push_back(particle);
	}
	mDrawPoly = new DrawPolygonComponent(this);
	mDrawPoly->SetUseFlag(mUseFlag);
}

void DamageEffect::Process()
{
	if (!mUseFlag) { return; }
	mNowPlayTime++;
	if (mNowPlayTime > mPlayTotalTime)
	{ 
		mUseFlag = false;
		mParticleList.clear();
		return;
	}
	for (auto&& particle : mParticleList)
	{
		particle.Pos._x += particle.Velocity._x * 0.5;
		particle.Pos._y += particle.Velocity._y * 0.5;
		particle.Pos._z += particle.Velocity._z * 0.5;
	}
	int alpha = (mPlayTotalTime > 0) ? 255 * ((mPlayTotalTime - mNowPlayTime) / mPlayTotalTime) : 0;
	std::vector<VERTEX3D> vertices;
	std::vector<unsigned short> index;
	for (auto&& particle : mParticleList)
	{
		VERTEX3D vertex;
		for (int i = 0; i < 4; ++i)
		{
			vertex.pos = Vector3D(particle.Pos._x + (i == 1 || i == 2 ? 5 : -5), particle.Pos._y + (i >=  2 ? 5 : -5), particle.Pos._z).dxl();
			vertex.dif = particle.Color;
			vertices.push_back(vertex);
		}
		int base_index = vertices.size() - 4;
		index.push_back(base_index);
		index.push_back(base_index + 1);
		index.push_back(base_index + 2);
		index.push_back(base_index);
		index.push_back(base_index + 2);
		index.push_back(base_index + 3);
	}
	mDrawPoly->SetVertex(vertices);
	mDrawPoly->SetIndeex(index);
	mDrawPoly->SetTotalTime(mPlayTotalTime);
	mDrawPoly->SetPlayTime(mNowPlayTime);
	mDrawPoly->SetUseFlag(mUseFlag);
	mDrawPoly->SetAlpha(alpha);
}

void DamageEffect::Render()
{
}
