#include "stdafx.h"
#include "CWorld.h"


void CWorld::Init()
{
  //Use autos o iteradores c++11
	for (list<CGameObject*>::iterator gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++) {
		(*gameObject)->Init();
	}
}

void CWorld::Destroy()
{
	for (list<CGameObject*>::iterator gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++) {
		(*gameObject)->Destroy();
	}
}

void CWorld::Update(float delta)
{
	for (list<CGameObject*>::iterator gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++) {
		(*gameObject)->Update(delta);
	}
}

void CWorld::Render()
{
	for (list<CGameObject*>::iterator gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++) {
		(*gameObject)->Render();
	}
}

CWorld::CWorld()
{
}


CWorld::~CWorld()
{
}
