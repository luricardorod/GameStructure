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
#define FORCEWANDER1 1
#define FORCEWANDER2 1
#define RADIUSARRIVE 1
#define STRONGFORCE 10000
#define OFFSETAVOIDANCE .1

class CBoid :public CGameObject
{
private:
	CVector2D m_CVec2Direction;
	float m_fVelocity;
	float m_fMaxSpeed;
	std::vector<std::shared_ptr<CObstacle>>* m_pObstacleList;
	float m_fRadiusSizeBoid;
public:
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	virtual unsigned short GetClassId();

	CVector2D Seek(CVector2D position, float magnitudeForce);
	CVector2D Flee(CVector2D position, float radiusOfForceAplication, float magnitudeForce);
	CVector2D Arrive(CVector2D position, float radiusOfForceAplication, float magnitudeForce);
	CVector2D Pursue(CVector2D position, CVector2D direction, float velocity, float timePrediction, float magnitudeForce);
	CVector2D Evade(CVector2D position, CVector2D direction, float velocity, float timePrediction, float radiusOfForceAplication, float magnitudeForce);
	CVector2D Wander1(CVector2D SizeWorld, float radiusArrival, float timeLimitSeek, float delta, float magnitudeForce);
	CVector2D Wander2(float offset, float radiusNextPoint, float visionAngle, float magnitudeForce);
	CVector2D ObstacleAvoidance1();
	CVector2D ObstacleAvoidance2();

	void SetListObstacle(std::vector<std::shared_ptr<CObstacle>>*);
	CBoid();
	virtual ~CBoid();
};

