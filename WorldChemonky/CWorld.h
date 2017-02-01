#pragma once

#include "CGameObject.h"
#include <list>
#include <memory>

class CWorld
{
public:
	std::shared_ptr<std::list<CGameObject*>> m_pGameObjects;
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	CWorld();
	~CWorld();
};