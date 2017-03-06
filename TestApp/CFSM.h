#pragma once
#include "CStates.h"
#include "CUnits.h"
#include <vector>
#include <memory>
class CFSM
{
public:
	CStates** m_States;
	void SetState(CUnits *unit, CStates *state);
	void Update();

	std::vector<std::shared_ptr<CUnits>> m_pUnits;
	CFSM();
	~CFSM();
};

