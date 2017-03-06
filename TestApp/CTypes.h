#pragma once
#include <vector>
#include <memory>
class CTypes
{
public:
	int m_iID;
	int m_iMaxGarrison;
	int m_iProductionCosts;
	bool m_bCanRecolect;
	bool m_bCanBuild;
	bool m_bIsBelic;
	bool m_CanGarrison;
	bool m_CanGroup;
	float m_fVisionRange;
	float m_fMaxSpeed;
	float m_fMaxHP;
	float m_fConstruictionTime;
	float m_fRotingTime;
	float m_fConstructionTypes;
	std::vector<std::shared_ptr<int>> m_viWeapons;
	std::vector<std::shared_ptr<int>> m_viArmors;
	std::vector<std::shared_ptr<int>> m_viTerrainType;
		//- TerrainType
		//-> - Stands
		//->MaxOrders
	CTypes();
	~CTypes();
};

