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
	m_fMaxSpeed = 10;
	m_fRadiusSizeBoid = 1;
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

	//printf("x=%f \n y=%f \n", m_Cvec2dPosition.x, m_Cvec2dPosition.y);
	printf("%f\n", m_Cvec2dPosition.y);

}

void CBoid::Render() {
}

CVector2D CBoid::Seek(CVector2D position, float magnitudeForce) {
	CVector2D forceSeek = position - m_Cvec2dPosition;
	return forceSeek.Normalize() * magnitudeForce;
}

CVector2D CBoid::Flee(CVector2D position, float radiusOfForceAplication, float magnitudeForce) {
	CVector2D forceFlee = m_Cvec2dPosition - position;
	if (forceFlee.Magnitude() < radiusOfForceAplication) 
	{
		return forceFlee.Normalize() * magnitudeForce;
	}
	return CVector2D(0, 0);
}

CVector2D CBoid::Arrive(CVector2D position, float radiusOfForceAplication, float magnitudeForce) {
	CVector2D arriveForce = Seek(position, magnitudeForce);

	float distance = (position - m_Cvec2dPosition).Magnitude();

	if (distance < radiusOfForceAplication && radiusOfForceAplication != 0)
	{
		arriveForce *= (distance / radiusOfForceAplication);
	}

	return arriveForce;
}

CVector2D CBoid::Pursue(CVector2D position, CVector2D direction, float velocity, float timePrediction, float magnitudeForce)
{
	CVector2D futurePosition = position + (direction*velocity*timePrediction);
	float distanceTarget = (position - m_CVec2Position).Magnitude();
	float radioPrediction = (futurePosition - position).Magnitude();

	if (distanceTarget > radioPrediction)
	{
		return (futurePosition - m_CVec2Position).Normalize() * magnitudeForce;
	}
	return (futurePosition*(distanceTarget / radioPrediction) - m_CVec2Position).Normalize() * magnitudeForce;
}

CVector2D CBoid::Evade(CVector2D position, CVector2D direction, float velocity, float timePrediction, float radiusOfForceAplication, float magnitudeForce)
{
	CVector2D futurePosition = position + (direction*velocity*timePrediction);
	float distanceTarget = (position - m_CVec2Position).Magnitude();
	float radioPrediction = (futurePosition - position).Magnitude();


	if (distanceTarget > radioPrediction)
	{
		if ((m_CVec2Position - futurePosition).Magnitude() > radiusOfForceAplication)
		{
			return CVector2D(0, 0);
		}
		return ((m_CVec2Position - futurePosition).Normalize() * magnitudeForce);
	}
	return (m_CVec2Position - futurePosition * (distanceTarget / radioPrediction)).Normalize() * magnitudeForce;
}

CVector2D CBoid::Wander2(float offset, float radiusNextPoint, float visionAngle, float magnitudeForce)
{
	CVector2D projectedPoint = m_Cvec2dPosition + (m_Cvec2dDirection*offset);
	float angleBoid = atanf(m_Cvec2dDirection.y / m_Cvec2dDirection.x);

	float angleInVision = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / visionAngle));
	angleInVision = angleInVision - (visionAngle / 2);

	CVector2D pointInAngleVision(cosf(angleBoid + angleInVision)*radiusNextPoint, sin(angleBoid + angleInVision)*radiusNextPoint);

	CVector2D target = projectedPoint + pointInAngleVision;

	return Seek(target, magnitudeForce);
}

CVector2D CBoid::ObstacleAvoidance1()
{
	CVector2D finalFuturePosition = m_CVec2Position + m_CVec2Direction * m_fVelocity * OFFSETAVOIDANCE;
	CVector2D halfFuturePosition = finalFuturePosition * 0.5f;

	float distanceMoreClose = 10000;
	CVector2D obstacleForce;

	for (auto &obstacle : *m_pObstacleList) {
		float addRadius = obstacle.GetRadius() + m_fRadiusSizeBoid;
		CVector2D obstaclePosition = obstacle.GetPosition();

		if ((obstaclePosition - m_CVec2Position).Magnitude() < addRadius)
		{
			if (distanceMoreClose > (obstaclePosition - m_CVec2Position).Magnitude())
			{
				obstacleForce = (m_CVec2Position - obstaclePosition).Normalize() * STRONGFORCE;
			}
		}
		if ((obstaclePosition - halfFuturePosition).Magnitude() < addRadius)
		{
			if (distanceMoreClose > (obstaclePosition - halfFuturePosition).Magnitude())
			{
				obstacleForce = (halfFuturePosition - obstaclePosition).Normalize() * STRONGFORCE;
			}
		}
		if ((obstaclePosition - finalFuturePosition).Magnitude() < addRadius)
		{
			if (distanceMoreClose > (obstaclePosition - finalFuturePosition).Magnitude())
			{
				obstacleForce = (finalFuturePosition - obstaclePosition).Normalize() * STRONGFORCE;
			}
		}		
	}
	if (distanceMoreClose == 1000)
	{
		return CVector2D(0, 0);
	}
	return obstacleForce;
}

CVector2D CBoid::ObstacleAvoidance2()
{
	CVector2D perpendicularDirection = CVector2D(-m_CVec2Direction.y, m_CVec2Direction.x).Normalize();
	CVector2D lastMiddlePoint = m_CVec2Position + m_CVec2Direction*m_fVelocity *OFFSETAVOIDANCE;
	CVector2D firstMiddlePoint = m_CVec2Position - (m_CVec2Direction * m_fRadiusSizeBoid);
	CVector2D firstTopPoint = firstMiddlePoint + perpendicularDirection * m_fRadiusSizeBoid;
	CVector2D firstBotPoint = firstMiddlePoint - perpendicularDirection * m_fRadiusSizeBoid;
	CVector2D lastTopPoint = lastMiddlePoint + perpendicularDirection * m_fRadiusSizeBoid;
	CVector2D lastBotPoint = lastMiddlePoint - perpendicularDirection * m_fRadiusSizeBoid;

	CVector2D topRectangle = lastTopPoint - firstTopPoint;
	CVector2D botRectangle = lastBotPoint - firstBotPoint;
	CVector2D leftRectangle = firstTopPoint - firstBotPoint;
	CVector2D rightRectangle = lastBotPoint - lastTopPoint;

	CVector2D obstacleForce;
	float distanceMoreClose = 10000;

	for (auto &obstacle : *m_pObstacleList) {
		CVector2D obstacleDistance = obstacle.GetPosition() - firstTopPoint;
		float dot = obstacleDistance.Dot(topRectangle);
		CVector2D pointColision = topRectangle.Normalize() * (dot / topRectangle.Magnitude());



	}
	if (distanceMoreClose == 1000)
	{
		return CVector2D(0, 0);
	}
	return obstacleForce;
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
