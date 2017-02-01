#include "stdafx.h"
#include "Obstacle.h"


float CObstacle::GetRadius()
{
	return m_Radius;
}

void CObstacle::SetRadius(float radius)
{
	m_Radius = radius;
}

void CObstacle::Init()
{
	m_Radius = 1;
}

void CObstacle::Destroy()
{
}

void CObstacle::Update(float delta)
{
}

void CObstacle::Render()
{
}

CObstacle::CObstacle()
{
	Init();
}


CObstacle::~CObstacle()
{
}
