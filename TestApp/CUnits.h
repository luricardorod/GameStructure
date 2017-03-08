#pragma once
#include "CGameObject.h"
#include <memory>
#include <vector>
#include "CVector2D.h"
class CWorld;
class CUnits :public CGameObject
{
public:
	void Init(int idType);
	void Destroy();
	void Update(float delta);
	void Render();
	unsigned short GetClassId();

	int m_iId;
	int m_iIdType;
	int m_iIdFaction;
	CVector2D m_v2Direction;
	float m_fHp;
	int m_State;
	int m_iGroupId;
	bool m_bSelectable;
	std::vector<std::shared_ptr<CGameObject>>* m_vQueueConstruction;
	std::vector<std::shared_ptr<CGameObject>>* m_vListaGarrison;
	float m_fReloadTime;
	float m_fRotingTimer;
	float m_fConstructionTimer;
	CUnits *m_UnitInteract;
	CWorld *m_World;
	CVector2D m_v2Coordinates;
	bool EnemyInVisionRange();
	bool IsAnEnemyFaction(int id);
	bool IsBelic();
	bool CanEnter(CUnits* unit);
	CUnits();
	~CUnits();
};
	
