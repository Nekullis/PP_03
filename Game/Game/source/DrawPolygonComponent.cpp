#include "DrawPolygonComponent.h"


DrawPolygonComponent::DrawPolygonComponent(ObjectBase* owner, int updateowder) :DrawComponent(owner, updateowder)
{
	mUseFlag = false;
	mPlayTotalTime = 0.0;
	mColorAlpha = 255;
	
}

DrawPolygonComponent::~DrawPolygonComponent()
{
	mVertex.clear();
	mIndex.clear();
}

void DrawPolygonComponent::Update()
{
	SetUseLighting(false);
	if (!mUseFlag) { return; }
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mColorAlpha);
	DrawPolygonIndexed3D(mVertex.data(), mVertexCnt, mIndex.data(), mIndexCnt, DX_NONE_GRAPH, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetUseLighting(true);

}

void DrawPolygonComponent::SetVertex(std::vector<VERTEX3D>& vertex)
{
	this->mVertex = vertex;
	this->mVertexCnt = vertex.size();
}

void DrawPolygonComponent::SetIndeex(std::vector<unsigned short>& index)
{
	this->mIndex = index;
	this->mIndexCnt = index.size() / 3;
}
