#pragma once
#include "CStates.h"
class CBuild :
	public CStates
{
public:
	int Update(std::shared_ptr<CGameObject> unit);
	void OnEnter();
	void OnExit();
	CBuild();
	~CBuild();
};

