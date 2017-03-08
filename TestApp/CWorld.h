#pragma once

#include "CGameObject.h"
#include <vector>
#include <memory>
#include "CTypes.h"
#include "CFaction.h"
#include "CWeaponType.h"
#include "CVector2D.h"

class CWorld
{
public:
	std::vector<std::shared_ptr<CGameObject>> m_pGameObjects;

	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	CTypes* GetType(int id);
	CFaction* GetFaction(int id);
	CWeaponType* GetWeaponType(int id);
	CTypes* m_aTypes;
	CFaction* m_aFactions;
	CWeaponType* m_aWeapons;

	CWorld();
	~CWorld();
};