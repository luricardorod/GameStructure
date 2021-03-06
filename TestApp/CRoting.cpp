#include "CRoting.h"



int CRoting::Update(std::shared_ptr<CUnits> unit, float deltaTime)
{
	unit->m_fRotingTimer += deltaTime;
	if (unit->m_fRotingTimer > unit->m_World->GetType(unit->m_iIdType)->m_fRotingTime)
	{
		unit->Destroy();
	}
	return COUNTSTATES;
}

void CRoting::OnEnter(CUnits *unit)
{
	unit->m_fRotingTimer = 0;
	unit->m_bSelectable = 0;
}

void CRoting::OnExit(CUnits *unit)
{
}

CRoting::CRoting()
{
}


CRoting::~CRoting()
{
}
