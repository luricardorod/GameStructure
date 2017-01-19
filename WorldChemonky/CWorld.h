#pragma once
#include "CGameObject.h"
#include <list>
using namespace std;
class CWorld
{
public:
	list<CGameObject *> gameObjects;
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	CWorld();
	~CWorld();
};

