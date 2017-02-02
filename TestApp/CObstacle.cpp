#include "CObstacle.h"

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
	m_Radius = .02f;
}

void CObstacle::Destroy()
{
}

void CObstacle::Update(float delta)
{
	m_PrimitiveInstance->TranslateAbsolute(m_CVec2Position.x, m_CVec2Position.y, 0);
	m_PrimitiveInstance->Update();
}

void CObstacle::Render()
{
	m_PrimitiveInstance->Draw();
}

unsigned short CObstacle::GetClassId()
{
	return CLASSOBSTACLE;
}

CObstacle::CObstacle()
{
	Init();
}


CObstacle::~CObstacle()
{
}
