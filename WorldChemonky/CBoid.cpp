#include "stdafx.h"
#include "CBoid.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

void CBoid::Init() {
	srand(time(NULL));
}

void CBoid::Destroy() {
}

void CBoid::Update(float delta) {

  //Y donde inicialicé Velocity??? MaxSpeed???
	if (Magnity(_mVelocity) > _mMaxSpeed)
	{
		_mVelocity = Normalize(_mVelocity) * _mMaxSpeed;
	}
	_mPosition = _mPosition + _mVelocity * delta;
}
//Facilite la legibilidad, los espacios sirven para algo
void CBoid::Render() {
}

//Sea congruente con los parámetros, forceValue puede ser un valor por default? cual?
CVector2D CBoid::Seek(CVector2D position, float forceSeek) {
	return Normalize(position - _mPosition) * forceSeek;
}

//Si forceValue y el radio pueden ser considerados constantes, pueden tener defaults? en que orden irían?
CVector2D CBoid::Flee(CVector2D position, float forceFlee, float radiusOfForceAplication) {
	CVector2D direction = _mPosition - position;
	if (Magnity(direction) < radiusOfForceAplication) 
	{
		return Normalize(direction) * forceFlee;
	}
	return CVector2D(0, 0);
}

//Si forceValue y el radio pueden ser considerados constantes, pueden tener defaults? en que orden irían?
	//Los radios pueden ser 0?, que pasa si la fuerza es 0?
CVector2D CBoid::Arrive(CVector2D position, float forceArrive, float radiusOfForceAplication) {
	CVector2D arriveForce = Seek(position, forceArrive);

	float distance = Magnity(position - _mPosition);
	if (distance < radiusOfForceAplication)
	{
    //Justo por esto debería tener operador *=
		arriveForce = arriveForce * (distance / radiusOfForceAplication);
	}

	return arriveForce;
}

CVector2D CBoid::Pursue(CVector2D position, CVector2D direction, float velocity, float timePrediction, float forcePersue)
{
	CVector2D futurePosition = position + (direction*velocity*timePrediction);
	float distanceTarget = Magnity(position - _mPosition);
	float radioPrediction = Magnity(futurePosition - position);

	if (distanceTarget > radioPrediction)
	{
		return Normalize(futurePosition - _mPosition) * forcePersue;
	}
	return Normalize(futurePosition*(distanceTarget/ radioPrediction) - _mPosition) * forcePersue;
}

CVector2D CBoid::Evade(CVector2D position, CVector2D direction, float velocity, float timePrediction, float radiusOfForceAplication, float forceEvade)
{
	CVector2D futurePosition = position + (direction*velocity*timePrediction);
	float distanceTarget = Magnity(position - _mPosition);
	float radioPrediction = Magnity(futurePosition - position);

	if (distanceTarget > radioPrediction)
	{
		if (Magnity(_mPosition-futurePosition) > radiusOfForceAplication)
		{
			return CVector2D(0, 0);
		}
		return Normalize(_mPosition - futurePosition) * forceEvade;
	}
	return Normalize(_mPosition - futurePosition*(distanceTarget / radioPrediction)) * forceEvade;
}

CVector2D CBoid::Wander2(float offset, float radiusNextPoint, float visionAngle, float forceWander2)
{
	CVector2D projectedPoint = _mPosition + (_mDirection*offset);
	float angleBoid = atanf(_mDirection.y / _mDirection.x);

	float angleInVision = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / visionAngle));
	angleInVision = angleInVision - (visionAngle / 2);

	CVector2D pointInAngleVision(cosf(angleBoid + angleInVision)*radiusNextPoint, sin(angleBoid + angleInVision)*radiusNextPoint);

	CVector2D target = projectedPoint + pointInAngleVision;

	return Seek(target, forceWander2);
}

CVector2D CBoid::Wander1(CVector2D SizeWorld, float radiusArrival, float timeLimitSeek, float forceWander1, float delta)
{
	static float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / SizeWorld.x));
	static float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / SizeWorld.y));
	static float timeSeek = 0;
	static CVector2D randomTarget(x, y);

	float distance = Magnity(randomTarget - _mPosition);
	timeSeek += delta;

	if (timeSeek > timeLimitSeek || distance < radiusArrival)
	{
		randomTarget.x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / SizeWorld.x));
		randomTarget.y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / SizeWorld.y));
	}
	return Seek(randomTarget, forceWander1);
}
