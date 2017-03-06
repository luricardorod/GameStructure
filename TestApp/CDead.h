#pragma once
#include "CStates.h"
class CDead :
	public CStates
{
public:
	int Update(std::shared_ptr<CGameObject> unit);
	void OnEnter();
	void OnExit();
	CDead();
	~CDead();
};

