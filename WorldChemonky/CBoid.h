#include "Cvector2D.h";
#include "CGameObject.h"

class CBoid:public CGameObject
{
private:
	//float _mVelocity;
	CVector2D _mDirection;
	CVector2D _mVelocity; //El standard de variables miembro debería de ser "m_"
	float _mMaxSpeed;

public:
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();

	CVector2D Seek(CVector2D position, float forceSeek);
	CVector2D Flee(CVector2D position, float forceFlee, float radiusOfForceAplication);
	CVector2D Arrive(CVector2D position, float forceArrive, float radiusOfForceAplication);
	CVector2D Pursue(CVector2D position, CVector2D direction,float velocity, float timePrediction, float forcePersue);
	CVector2D Evade(CVector2D position, CVector2D direction, float velocity, float timePrediction, float radiusOfForceAplication, float forceEvade);
	CVector2D Wander1(CVector2D SizeWorld, float radiusArrival, float timeLimitSeek, float forceWander1, float delta);
	CVector2D Wander2(float offset,float radiusNextPoint, float visionAngle, float forceWander2);
	//Faltan constructores y destructor virtual
};

