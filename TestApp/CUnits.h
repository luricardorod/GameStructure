#pragma once
#include "CVector2D.h"
#include "CGameObject.h"
#include <vector>
#include <memory>
#include "CStates.h"

class CUnits:public CGameObject
{
public:
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	unsigned short GetClassId();

	int m_iId;
	int m_iIdType;
	int m_iIdFaction;
	CVector2D m_v2Direction;
	float m_fHp;
	CStates* m_State;
	int m_iGroupId;
	std::vector<std::shared_ptr<CGameObject>>* m_vQueueConstruction;
	std::vector<std::shared_ptr<CGameObject>>* m_vListaGarrison;
	float m_ReloadTime;
	float m_fRotingTimer;
	CUnits *m_UnitInteract;
	CUnits();
	~CUnits();
};
	
