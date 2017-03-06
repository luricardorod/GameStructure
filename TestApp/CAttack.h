#pragma once
#include "CStates.h"
class CAttack :
	public CStates
{
public:
	int Update(std::shared_ptr<CGameObject> unit);
	void OnEnter();
	void OnExit();
	CAttack();
	~CAttack();
};

