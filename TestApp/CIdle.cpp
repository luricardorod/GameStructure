#include "CIdle.h"
#include "CUnits.h"

int CIdle::Update(std::shared_ptr<CGameObject> unit)
{
	CUnits *tempUnit = std::dynamic_pointer_cast<CUnits>(unit).get();
	/*if (isbelic)
	{
			m_UnityInteract = Unidad Enemiga ceeercana
		if (m_UnityInteract)
		{
			
		}
	}
	return*/
	return COUNTSTATES;
}

void CIdle::OnEnter()
{
}

void CIdle::OnExit()
{
}

CIdle::CIdle()
{
}


CIdle::~CIdle()
{
}
