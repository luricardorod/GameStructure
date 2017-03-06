#pragma once
#include "CStates.h"
class CGarrison :
	public CStates
{
public:
	int Update(std::shared_ptr<CGameObject> unit);
	void OnEnter();
	void OnExit();
	CGarrison();
	~CGarrison();
};

