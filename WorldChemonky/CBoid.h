#include "Cvector2D.h";
#include "CGameObject.h"

class CBoid:public CGameObject
{
private:
	CVector2D _mVelocity;
	float _mMaxSpeed;

public:
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	CVector2D Seek(CVector2D position, float forceValue);
	CVector2D Flee(CVector2D position, float forceValue, float radiusOfForceAplication);
	CVector2D Arrive(CVector2D position, float forceValue, float radiusOfForceAplication);
	CVector2D Pursue(CVector2D position, CVector2D direction,float velocity, float timePrediction);
	CVector2D Evade(CVector2D position, CVector2D direction, float velocity, float timePrediction, float radiusOfForceAplication);
	CVector2D Wander1(CVector2D SizeWorld, float radiusArrival, float timeSeek);
	CVector2D Wander2(float offset,float radiusNextPoint, float visionAngle);
};

