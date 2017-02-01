#include "stdafx.h"
#include "CWorld.h"


void CWorld::Init()
{
  //Use autos o iteradores c++11
	for (auto &gameObject : *m_pGameObjects) {
		gameObject->Init();
	}
}

void CWorld::Destroy()
{
	for (auto &gameObject : *m_pGameObjects) {
		gameObject->Destroy();
	}
}

void CWorld::Update(float delta)
{
	for (auto &gameObject : *m_pGameObjects) {
		gameObject->Update(delta);
	}
}

void CWorld::Render()
{
	for (auto &gameObject : *m_pGameObjects) {
		gameObject->Render();
	}
}

CWorld::CWorld()
{
}


CWorld::~CWorld()
{
}
