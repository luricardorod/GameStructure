#include "CWorld.h"
#include "CBoid.h"
#include "CObstacle.h"
#include <stdlib.h>
#include <time.h>
#include "definitions.h"
void CWorld::Init()
{
	/*
	for (int i = 0; i < 3; i++)
	{
		m_pGameObjects.push_back(std::make_shared<CObstacle>());
		m_pObstacles.push_back(m_pGameObjects.back());
	}

	CBoid cboid;
	cboid.SetListObstacle(&m_pObstacles);
	m_pGameObjects.push_back(std::make_shared<CBoid>(cboid));

	srand(time(NULL));
	for (auto &gameObject : m_pGameObjects) {

		gameObject->Init();
		float x = ((rand() % 201) / 100.0f) - 1.0f;
		float y = ((rand() % 201) / 100.0f) - 1.0f;
		//Sleep(100);
		CVector2D randomPosition(x, y);
		gameObject->SetPosition(randomPosition);
	}*/
	/*m_pGameObjects.push_back(std::make_shared<CObstacle>());
	m_pGameObjects.back()->Init();
	m_pGameObjects.back()->SetPosition(CVector2D(0, 0.5f));
	
	m_pGameObjects.push_back(std::make_shared<CObstacle>());
	m_pGameObjects.back()->Init();
	m_pGameObjects.back()->SetPosition(CVector2D(-0.25f, -0.43f));

	m_pGameObjects.push_back(std::make_shared<CObstacle>());
	m_pGameObjects.back()->Init();
	m_pGameObjects.back()->SetPosition(CVector2D(0.25f, -0.43f));*/

	CBoid cboid1;
	cboid1.SetListObstacle(&m_pGameObjects);
	m_pGameObjects.push_back(std::make_shared<CBoid>(cboid1));
	m_pGameObjects.back()->Init();
	m_pGameObjects.back()->SetPosition(CVector2D(.5f, 0));
	std::dynamic_pointer_cast<CBoid>(m_pGameObjects.back())->flag1 = true;

	CBoid cboid2;
	cboid2.SetListObstacle(&m_pGameObjects);
	m_pGameObjects.push_back(std::make_shared<CBoid>(cboid2));
	m_pGameObjects.back()->Init();
	m_pGameObjects.back()->SetPosition(CVector2D(0, 0));
		std::dynamic_pointer_cast<CBoid>(m_pGameObjects.back())->flag2 = true;

	CBoid cboid3;
	cboid3.SetListObstacle(&m_pGameObjects);
	m_pGameObjects.push_back(std::make_shared<CBoid>(cboid3));
	m_pGameObjects.back()->Init();
	m_pGameObjects.back()->SetPosition(CVector2D(-.5f, -.5f));
	std::dynamic_pointer_cast<CBoid>(m_pGameObjects.back())->flag2 = true;
	/*CBoid cboid3;
	cboid3.SetListObstacle(&m_pGameObjects);
	m_pGameObjects.push_back(std::make_shared<CBoid>(cboid3));
	m_pGameObjects.back()->Init();
	m_pGameObjects.back()->SetPosition(CVector2D(.5f, -.5f));*/

	m_aTypes = new CTypes[TYPES_SIZE];
	m_aFactions = new CFaction[FACTIONS_SIZE];
	m_aWeapons = new CWeaponType[WEAPONS_SIZE];


}

void CWorld::Destroy()
{
	for (auto &gameObject : m_pGameObjects) {
		gameObject->Destroy();
	}
}

void CWorld::Update(float delta)
{
	for (auto &gameObject : m_pGameObjects) {
		gameObject->Update(delta);
	}
}

void CWorld::Render()
{
	for (auto &gameObject : m_pGameObjects) {
		gameObject->Render();
	}
}

CTypes* CWorld::GetType(int id)
{
	return &m_aTypes[id];
}

CFaction* CWorld::GetFaction(int id)
{
	return &m_aFactions[id];
}

CWeaponType* CWorld::GetWeaponType(int id)
{
	return &m_aWeapons[id];
}

CWorld::CWorld()
{
	Init();
}


CWorld::~CWorld()
{
}