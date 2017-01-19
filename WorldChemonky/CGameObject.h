#pragma once
#include "CVector2D.h"

class CGameObject
{
public:
	CVector2D _mPosition;
	virtual void Init();
	virtual void Destroy();
	virtual void Update(float delta);
	virtual void Render();
	~CGameObject();
};

