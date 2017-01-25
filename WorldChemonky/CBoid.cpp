#include "stdafx.h"
#include "CBoid.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

void CBoid::Init() {
	srand(time(NULL));
	m_Cvec2dDirection = CVector2D(1, 1);
	m_Cvec2dDirection = m_Cvec2dDirection.Normalize();
	m_Cvec2dPosition = CVector2D(0, 0);
	m_fVelocity = 0;
	m_fMaxSpeed = 100;
}

void CBoid::Destroy() {
}

void CBoid::Update(float delta) {
	CVector2D SteeringForce(0, 0);
	CVector2D target(30, -40);

	SteeringForce += Arrive(target, 20, FORCESEEK);
	m_fVelocity = SteeringForce.Truncate(m_fMaxSpeed) * delta;
	m_Cvec2dDirection = (m_Cvec2dDirection + SteeringForce.Normalize()).Normalize();
	m_Cvec2dPosition += m_Cvec2dDirection * m_fVelocity;

	printf("x=%f \n y=%f \n", m_Cvec2dPosition.x, m_Cvec2dPosition.y);
}

void CBoid::Render() {
}

CVector2D CBoid::Seek(CVector2D position, float magnitudeForce) {
	CVector2D forceSeek = position - m_Cvec2dPosition;
	return forceSeek.Normalize() * magnitudeForce;
}

CVector2D CBoid::Flee(CVector2D position, float radiusOfForceAplication, float magnitudeForce) {
	CVector2D forceFlee = _mPosition - position;
	if (forceFlee.Magnitude() < radiusOfForceAplication) 
	{
		return forceFlee.Normalize() * magnitudeForce;
	}
	return CVector2D(0, 0);
}

CVector2D CBoid::Arrive(CVector2D position, float radiusOfForceAplication, float magnitudeForce) {
	CVector2D arriveForce = Seek(position, magnitudeForce);

	float distance = (position - _mPosition).Magnitude();
	if (distance < radiusOfForceAplication && radiusOfForceAplication != 0)
	{
		arriveForce *= (distance / radiusOfForceAplication);
	}

	return arriveForce;
}

CVector2D CBoid::Pursue(CVector2D position, CVector2D direction, float velocity, float timePrediction, float magnitudeForce)
{
	CVector2D futurePosition = position + (direction*velocity*timePrediction);
	float distanceTarget = (position - m_Cvec2dPosition).Magnitude();
	float radioPrediction = (futurePosition - position).Magnitude();

	if (distanceTarget > radioPrediction)
	{
		return (futurePosition - m_Cvec2dPosition).Normalize() * magnitudeForce;
	}
	return (futurePosition*(distanceTarget / radioPrediction) - m_Cvec2dPosition).Normalize() * magnitudeForce;
}

CVector2D CBoid::Evade(CVector2D position, CVector2D direction, float velocity, float timePrediction, float radiusOfForceAplication, float magnitudeForce)
{
	CVector2D futurePosition = position + (direction*velocity*timePrediction);
	float distanceTarget = (position - m_Cvec2dPosition).Magnitude();
	float radioPrediction = (futurePosition - position).Magnitude();


	if (distanceTarget > radioPrediction)
	{
		if ((m_Cvec2dPosition - futurePosition).Magnitude() > radiusOfForceAplication)
		{
			return CVector2D(0, 0);
		}
		return (m_Cvec2dPosition - futurePosition * magnitudeForce);
	}
	return (m_Cvec2dPosition - futurePosition * (distanceTarget / radioPrediction)).Normalize() * magnitudeForce;
}

CVector2D CBoid::Wander2(float offset, float radiusNextPoint, float visionAngle, float magnitudeForce)
{
	CVector2D projectedPoint = _mPosition + (m_Cvec2dDirection*offset);
	float angleBoid = atanf(m_Cvec2dDirection.y / m_Cvec2dDirection.x);

	float angleInVision = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / visionAngle));
	angleInVision = angleInVision - (visionAngle / 2);

	CVector2D pointInAngleVision(cosf(angleBoid + angleInVision)*radiusNextPoint, sin(angleBoid + angleInVision)*radiusNextPoint);

	CVector2D target = projectedPoint + pointInAngleVision;

	return Seek(target, magnitudeForce);
}

CVector2D CBoid::Wander1(CVector2D SizeWorld, float radiusArrival, float timeLimitSeek, float delta, float magnitudeForce)
{
	static float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / SizeWorld.x));
	static float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / SizeWorld.y));
	static float timeSeek = 0;
	static CVector2D randomTarget(x, y);

	float distance = (randomTarget - m_Cvec2dPosition).Magnitude();
	timeSeek += delta;

	if (timeSeek > timeLimitSeek || distance < radiusArrival)
	{
		randomTarget.x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / SizeWorld.x));
		randomTarget.y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / SizeWorld.y));
	}
	return Seek(randomTarget, magnitudeForce);
}

CBoid::CBoid()
{
	Init();
}

CBoid::~CBoid()
{
	Destroy();
}
