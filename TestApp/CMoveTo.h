#pragma once
#include "CStates.h"
class CMoveTo :
	public CStates
{
public:
	int Update(std::shared_ptr<CGameObject> unit);
	void OnEnter();
	void OnExit();
	CMoveTo();
	~CMoveTo();
};

