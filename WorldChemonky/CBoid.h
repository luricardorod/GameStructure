#include "Cvector2D.h";
#include "CGameObject.h"

#define FORCESEEK 1
#define FORCEFLEE 1
#define FORCEARRIVE 1
#define FORCEPERSUE 1
#define FORCEEVADE 1
#define FORCEWANDER1 1
#define FORCEWANDER2 1
#define RADIUSARRIVE 1

class CBoid:public CGameObject
{
private:
	CVector2D m_Cvec2dDirection;
	CVector2D m_Cvec2dPosition;
	float m_fVelocity;
	float m_fMaxSpeed;

public:
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();

	CVector2D Seek(CVector2D position, float magnitudeForce);
	CVector2D Flee(CVector2D position, float radiusOfForceAplication, float magnitudeForce);
	CVector2D Arrive(CVector2D position, float radiusOfForceAplication, float magnitudeForce);
	CVector2D Pursue(CVector2D position, CVector2D direction,float velocity, float timePrediction, float magnitudeForce);
	CVector2D Evade(CVector2D position, CVector2D direction, float velocity, float timePrediction, float radiusOfForceAplication, float magnitudeForce);
	CVector2D Wander1(CVector2D SizeWorld, float radiusArrival, float timeLimitSeek, float delta, float magnitudeForce);
	CVector2D Wander2(float offset,float radiusNextPoint, float visionAngle, float magnitudeForce);
	
	CBoid();
	virtual ~CBoid();
};

