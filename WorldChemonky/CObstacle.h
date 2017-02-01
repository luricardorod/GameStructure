#pragma once
#include"CGameObject.h"

class CObstacle :public CGameObject
{
private:
	float m_Radius;
public:
	float GetRadius();
	void SetRadius(float radius);
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	CObstacle();
	~CObstacle();
};

