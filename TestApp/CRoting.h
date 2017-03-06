#pragma once
#include "CStates.h"
class CRoting :
	public CStates
{
public:
	int Update(std::shared_ptr<CGameObject> unit);
	void OnEnter();
	void OnExit();
	CRoting();
	~CRoting();
};

