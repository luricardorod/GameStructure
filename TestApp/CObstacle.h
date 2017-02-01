#pragma once
#include"CGameObject.h"

class CObstacle :public CGameObject
{
private:
	float m_Radius;
public:
		void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	virtual unsigned short GetClassId();

	float GetRadius();
	void SetRadius(float radius);

	CObstacle();
	~CObstacle();
};

