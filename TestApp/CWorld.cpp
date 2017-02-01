#include "CWorld.h"
#include "CBoid.h"
#include "CObstacle.h"
#include <stdlib.h>
#include <time.h>

void CWorld::Init()
{

	for (int i = 0; i < 20; i++)
	{
		CObstacle cobstacle;
		m_pGameObjects.push_back(std::make_shared<CObstacle>(cobstacle));
		m_pObstacles.push_back(std::make_shared<CObstacle>(cobstacle));
	}
	CBoid cboid;
	cboid.SetListObstacle(&m_pObstacles);
	m_pGameObjects.push_back(std::make_shared<CBoid>(cboid));
	srand(time(NULL));
	for (auto &gameObject : m_pGameObjects) {

		gameObject->Init();
		float x = ((rand() % 201) / 100.0f) - 1.0f;
		float y = ((rand() % 201) / 100.0f) - 1.0f;
		Sleep(100);
		CVector2D randomPosition(x, y);
		gameObject->SetPosition(randomPosition);
	}
	printf("ol");
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

CWorld::CWorld()
{
	Init();
}


CWorld::~CWorld()
{
}
