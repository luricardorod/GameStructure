#pragma once
#include "CStates.h"
class CRecollect :
	public CStates
{
public:
	int Update(std::shared_ptr<CGameObject> unit);
	void OnEnter();
	void OnExit();
	CRecollect();
	~CRecollect();
};

