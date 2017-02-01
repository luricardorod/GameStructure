#pragma once

#include "CGameObject.h"
#include "CObstacle.h"
#include <list>
#include <vector>
#include <memory>

class CWorld
{
public:
	std::list<std::shared_ptr<CGameObject>> m_pGameObjects;
	std::vector<std::shared_ptr<CObstacle>> m_pObstacles;

	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	CWorld();
	~CWorld();
};