#include "Cvector2D.h";
#include "CGameObject.h"
#include "CObstacle.h"
#include <memory>
#include <vector>

#define FORCESEEK 5
#define FORCEFLEE 1
#define FORCEARRIVE 1
#define FORCEPERSUE 1
#define FORCEEVADE 1
#define FORCEWANDER1 25
#define FORCEWANDER2 1
#define RADIUSARRIVE 1
#define STRONGFORCE 10000
#define OFFSETAVOIDANCE .1
#define RADIOFLOCKING .5

class CBoid :public CGameObject
{
private:
	CVector2D m_CVec2Direction;
	float m_fVelocity;
	float m_fMaxSpeed;
	std::vector<std::shared_ptr<CGameObject>>* m_pGameObjects;
	std::vector<CVector2D> m_pPath;
	unsigned short m_usPathIndex;

	float m_fRadiusSizeBoid;
public:
	bool flag1 = true, flag2 = true;
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	bool m_bFlagPatrol2;
	unsigned short GetClassId();

	CVector2D Seek(CVector2D position, float magnitudeForce);
	CVector2D Flee(CVector2D position, float radiusOfForceAplication, float magnitudeForce);
	CVector2D Arrive(CVector2D position, float radiusOfForceAplication, float magnitudeForce);
	CVector2D Pursue(CVector2D position, CVector2D direction, float velocity, float timePrediction, float magnitudeForce);
	CVector2D Evade(CVector2D position, CVector2D direction, float velocity, float timePrediction, float radiusOfForceAplication, float magnitudeForce);
	CVector2D Wander1(CVector2D SizeWorld, float radiusArrival, float timeLimitSeek, float delta, float magnitudeForce);
	CVector2D Wander2(float offset, float radiusNextPoint, float visionAngle, float magnitudeForce);
	CVector2D Circle(float radioOrbita, float radioArrive);
	CVector2D ObstacleAvoidance1();
	CVector2D ObstacleAvoidance2();
	CVector2D FollowPath1(float magnitudeForce, float radioArrive, unsigned short typePatrol);
	CVector2D FollowPath2(float magnitudeForce, float radioArrive, float distanceMaxPath, unsigned short typePatrol);

	CVector2D Direction();
	CVector2D Separation(float magnitudeForce);
	CVector2D Cohesion(float magnitudeForce);
	CVector2D Flocking(float magnitudForce, float magnitudSeparationForce, float magnitudCoheisonForce);

	void SetListObstacle(std::vector<std::shared_ptr<CGameObject>>* gameObjectsList);
	CVector2D GetDirection();
	CBoid();
	virtual ~CBoid();
};

