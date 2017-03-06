#pragma once
#include "CGameObject.h"
#include <memory>
enum STATES
{
	STATEIDLE,
	STATEMOVETO,
	STATEATTACK,
	STATEDEAD,
	STATEROTING,
	STATERECOLLECT,
	STATEBUILD,
	STATEGARRISON,
	COUNTSTATES
};
class CStates
{
public:
	virtual int Update(std::shared_ptr<CGameObject> unit) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual ~CStates() {};
};

