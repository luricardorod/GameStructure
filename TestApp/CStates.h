#pragma once
#include "CWorld.h"
#include <memory>
#include "CUnits.h"
#include "CTypes.h"
#include "CVector2D.h"
#include "definitions.h"
class CStates
{
public:
	virtual int Update(std::shared_ptr<CUnits> unit, float deltaTime) = 0;
	virtual void OnEnter(CUnits *unit) = 0;
	virtual void OnExit(CUnits *unit) = 0;
	virtual ~CStates() {};
};

