#include "CWorld.h"
#include "CBoid.h"
#include "CObstacle.h"
#include <stdlib.h>
#include <time.h>
#include "definitions.h"
#include "CWalker.h"
#include "CDFS.h"
#include "CBFS.h"
#include "CBestFS.h"
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

	std::vector<nodo>grafo;
	grafo.resize(12);
	grafo[0].m_conections.push_back((*new Conection(10, &grafo[0])));
	grafo[0].m_conections.push_back((*new Conection(10, &grafo[2])));
	grafo[0].m_conections.push_back((*new Conection(10, &grafo[8])));
	grafo[0].m_conections.push_back((*new Conection(10, &grafo[9])));
	grafo[0].m_id = 0;
	grafo[0].m_position.x = 4.0f;
	grafo[0].m_position.y = 13.0f;
	grafo[1].m_conections.push_back((*new Conection(10, &grafo[0])));
	grafo[1].m_conections.push_back((*new Conection(10, &grafo[2])));
	grafo[1].m_conections.push_back((*new Conection(10, &grafo[8])));
	grafo[1].m_conections.push_back((*new Conection(10, &grafo[3])));
	grafo[1].m_id = 1;
	grafo[1].m_position.x = 10.0f;
	grafo[1].m_position.y = 0.0f;
	grafo[2].m_conections.push_back((*new Conection(10, &grafo[0])));
	grafo[2].m_conections.push_back((*new Conection(10, &grafo[1])));
	grafo[2].m_conections.push_back((*new Conection(10, &grafo[4])));
	grafo[2].m_id = 2;
	grafo[2].m_position.x = 2.0f;
	grafo[2].m_position.y = 11.0f;
	grafo[3].m_conections.push_back((*new Conection(10, &grafo[1])));
	grafo[3].m_conections.push_back((*new Conection(10, &grafo[4])));
	grafo[3].m_id = 3;
	grafo[3].m_position.x = 0.0f;
	grafo[3].m_position.y = 6.0f;
	grafo[4].m_conections.push_back((*new Conection(10, &grafo[3])));
	grafo[4].m_conections.push_back((*new Conection(10, &grafo[2])));
	grafo[4].m_conections.push_back((*new Conection(10, &grafo[8])));
	grafo[4].m_conections.push_back((*new Conection(10, &grafo[5])));
	grafo[4].m_conections.push_back((*new Conection(10, &grafo[6])));
	grafo[4].m_id = 4;
	grafo[4].m_position.x = 2.0f;
	grafo[4].m_position.y = 8.0f;
	grafo[5].m_conections.push_back((*new Conection(10, &grafo[4])));
	grafo[5].m_conections.push_back((*new Conection(10, &grafo[9])));
	grafo[5].m_conections.push_back((*new Conection(10, &grafo[7])));
	grafo[5].m_conections.push_back((*new Conection(10, &grafo[10])));
	grafo[5].m_id = 5;
	grafo[5].m_position.x = 7.0f;
	grafo[5].m_position.y = 8.0f;
	grafo[6].m_conections.push_back((*new Conection(10, &grafo[4])));
	grafo[6].m_conections.push_back((*new Conection(10, &grafo[7])));
	grafo[6].m_id = 6;
	grafo[6].m_position.x = 3.0f;
	grafo[6].m_position.y = 3.0f;
	grafo[7].m_conections.push_back((*new Conection(10, &grafo[8])));
	grafo[7].m_conections.push_back((*new Conection(10, &grafo[5])));
	grafo[7].m_conections.push_back((*new Conection(10, &grafo[11])));
	grafo[7].m_conections.push_back((*new Conection(10, &grafo[6])));
	grafo[7].m_id = 7;
	grafo[7].m_position.x = 6.0f;
	grafo[7].m_position.y = 3.0f;
	grafo[8].m_conections.push_back((*new Conection(10, &grafo[0])));
	grafo[8].m_conections.push_back((*new Conection(10, &grafo[1])));
	grafo[8].m_conections.push_back((*new Conection(10, &grafo[4])));
	grafo[8].m_conections.push_back((*new Conection(10, &grafo[9])));
	grafo[8].m_conections.push_back((*new Conection(10, &grafo[7])));
	grafo[8].m_id = 8;
	grafo[8].m_position.x = 6.0f;
	grafo[8].m_position.y = 9.0f;
	grafo[9].m_conections.push_back((*new Conection(10, &grafo[0])));
	grafo[9].m_conections.push_back((*new Conection(10, &grafo[8])));
	grafo[9].m_conections.push_back((*new Conection(10, &grafo[5])));
	grafo[9].m_conections.push_back((*new Conection(10, &grafo[11])));
	grafo[9].m_id = 9;
	grafo[9].m_position.x = 8.0f;
	grafo[9].m_position.y = 11.0f;
	grafo[10].m_conections.push_back((*new Conection(10, &grafo[5])));
	grafo[10].m_conections.push_back((*new Conection(10, &grafo[11])));
	grafo[10].m_id = 10;
	grafo[10].m_position.x = 4.0f;
	grafo[10].m_position.y = 0.0f;
	grafo[11].m_conections.push_back((*new Conection(10, &grafo[9])));
	grafo[11].m_conections.push_back((*new Conection(10, &grafo[7])));
	grafo[11].m_conections.push_back((*new Conection(10, &grafo[4])));
	grafo[11].m_conections.push_back((*new Conection(10, &grafo[10])));
	grafo[11].m_position.x = 8.0f;
	grafo[11].m_position.y = 1.0f; 
	grafo[11].m_id = 11;


	std::vector<nodo*>pat;
	std::vector<nodo*>lo;
	std::vector<nodo*>raq;
	CDFS lu;
	lu.PathFinding(&grafo[1], &grafo[11], &pat, 0);
	CBFS la;
	la.PathFinding(&grafo[1], &grafo[11], &lo, 0);
	CBestFS el;
	el.PathFinding(&grafo[1], &grafo[11], &raq, 0);
	int lau;
	lau++;
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