#pragma once
#include "CStates.h"
class CIdle :
	public CStates
{
public:
	int Update(std::shared_ptr<CGameObject> unit);
	void OnEnter();
	void OnExit();
	CIdle();
	~CIdle();
};

