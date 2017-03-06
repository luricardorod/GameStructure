#include "CFSM.h"
#include "CIdle.h";
#include "CMoveTo.h";
#include "CAttack.h";
#include "CDead.h";
#include "CRoting.h";
#include "CRecollect.h";
#include "CBuild.h";
#include "CGarrison.h";

void CFSM::SetState(CUnits *unit, CStates * state)
{
	unit->m_State->OnExit();
	unit->m_State = state;
	unit->m_State->OnEnter();

}

void CFSM::Update()
{
	for (auto &unit : m_pUnits) {
		int idState = unit->m_State->Update(unit);
		if (idState != COUNTSTATES)
		{
			SetState(unit.get(), m_States[idState]);
		};
	}
}

CFSM::CFSM()
{
	m_States = new CStates*[COUNTSTATES];
	m_States[STATEIDLE] = new CIdle();
	m_States[STATEMOVETO] = new CMoveTo();
	m_States[STATEATTACK] = new CAttack();
	m_States[STATEDEAD] = new CDead();
	m_States[STATEROTING] = new CRoting();
	m_States[STATERECOLLECT] = new CRecollect();
	m_States[STATEBUILD] = new CBuild();
	m_States[STATEGARRISON] = new CGarrison();
}


CFSM::~CFSM()
{
}
