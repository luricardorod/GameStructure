#include "CBoid.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

void CBoid::Init() {
	srand(time(NULL));
	m_CVec2Direction = CVector2D(-1, 1);
	m_CVec2Direction = m_CVec2Direction.Normalize();
	m_CVec2Position = CVector2D(0, 0);
	m_fVelocity = .8f;
	m_fMaxSpeed = .1f;
	m_fRadiusSizeBoid = 1;
}

void CBoid::Destroy() {
}

void CBoid::Update(float delta) {
	CVector2D SteeringForce(0, 0);
	CVector2D target(0, 1);

	//SteeringForce += Wander2(2, 5, 1.15, FORCESEEK);
	SteeringForce += Seek(target, FORCESEEK);
	SteeringForce += ObstacleAvoidance1();
	m_fVelocity = SteeringForce.Truncate(m_fMaxSpeed) * delta;
	m_CVec2Direction = (m_CVec2Direction + SteeringForce.Normalize()).Normalize();
	m_CVec2Position += m_CVec2Direction * m_fVelocity;

	//printf("x=%f \n y=%f \n", m_CVec2Position.x, m_CVec2Position.y);
	printf("%f\n", m_CVec2Position.y);

	m_PrimitiveInstance->TranslateAbsolute(m_CVec2Position.x, m_CVec2Position.y, 0);
	m_PrimitiveInstance->Update();

}

void CBoid::Render() {
	m_PrimitiveInstance->Draw();
}

unsigned short CBoid::GetClassId()
{
	return CLASSBOID;
}

CVector2D CBoid::Seek(CVector2D position, float magnitudeForce) {
	CVector2D forceSeek = position - m_CVec2Position;
	return forceSeek.Normalize() * magnitudeForce;
}

CVector2D CBoid::Flee(CVector2D position, float radiusOfForceAplication, float magnitudeForce) {
	CVector2D forceFlee = m_CVec2Position - position;
	if (forceFlee.Magnitude() < radiusOfForceAplication)
	{
		return forceFlee.Normalize() * magnitudeForce;
	}
	return CVector2D(0, 0);
}

CVector2D CBoid::Arrive(CVector2D position, float radiusOfForceAplication, float magnitudeForce) {
	CVector2D arriveForce = Seek(position, magnitudeForce);

	float distance = (position - m_CVec2Position).Magnitude();

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
	CVector2D projectedPoint = m_CVec2Position + (m_CVec2Direction*offset);
	float angleBoid = atanf(m_CVec2Direction.y / m_CVec2Direction.x);

	float angleInVision = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / visionAngle));
	angleInVision = angleInVision - (visionAngle / 2);

	CVector2D pointInAngleVision(cosf(angleBoid + angleInVision)*radiusNextPoint, sin(angleBoid + angleInVision)*radiusNextPoint);

	CVector2D target = projectedPoint + pointInAngleVision;

	return Seek(target, magnitudeForce);
}

CVector2D CBoid::ObstacleAvoidance1()
{
	CVector2D finalFuturePosition = m_CVec2Position + m_CVec2Direction * m_fVelocity * .1f;
	CVector2D halfFuturePosition = finalFuturePosition * 0.5f;

	float distanceMoreClose = 10000;
	CVector2D obstacleForce = CVector2D(0, 0);

	for (auto &obstacle : *m_pObstacleList) {
		float addRadius = (*obstacle).GetRadius() + m_fRadiusSizeBoid;
		CVector2D obstaclePosition = (*obstacle).GetPosition();

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
	if (distanceMoreClose == 10000)
	{
		return obstacleForce;
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

	CVector2D obstacleForce = CVector2D(0, 0);
	float distanceMoreClose = 10000;

	for (auto &obstacle : *m_pObstacleList) {
		CVector2D obstaclePosition = (*obstacle).GetPosition();
		float obstacleRadius = (*obstacle).GetRadius();
		//TopVectorCollision
		CVector2D obstacleDistance = obstaclePosition - firstTopPoint;
		float projection = obstacleDistance.Dot(topRectangle) / topRectangle.Magnitude();
		CVector2D pointColision;
		if (projection < 0)
		{
			pointColision = firstTopPoint;
		}
		else if (pointColision.Magnitude() > topRectangle.Magnitude()) {
			pointColision = lastTopPoint;
		}
		else {
			pointColision = firstTopPoint + topRectangle.Normalize() * projection;
		}
		if ((obstaclePosition - pointColision).Magnitude() < obstacleRadius)
		{
			if (distanceMoreClose > (m_CVec2Position - pointColision).Magnitude())
			{
				obstacleForce = (pointColision - obstaclePosition).Normalize() * STRONGFORCE;
			}
		}
		//BotVectorCollision
		obstacleDistance = obstaclePosition - firstBotPoint;
		projection = obstacleDistance.Dot(botRectangle) / botRectangle.Magnitude();
		if (projection < 0)
		{
			pointColision = firstBotPoint;
		}
		else if (pointColision.Magnitude() > botRectangle.Magnitude()) {
			pointColision = lastBotPoint;
		}
		else {
			pointColision = firstBotPoint + botRectangle.Normalize() * projection;
		}
		if ((obstaclePosition - pointColision).Magnitude() < obstacleRadius)
		{
			if (distanceMoreClose > (m_CVec2Position - pointColision).Magnitude())
			{
				obstacleForce = (pointColision - obstaclePosition).Normalize() * STRONGFORCE;
			}
		}
		//LeftVectorCollision
		//obstacleDistance = obstaclePosition - firstBotPoint;
		projection = obstacleDistance.Dot(leftRectangle) / leftRectangle.Magnitude();
		if (projection < 0)
		{
			pointColision = firstBotPoint;
		}
		else if (pointColision.Magnitude() > leftRectangle.Magnitude()) {
			pointColision = firstTopPoint;
		}
		else {
			pointColision = firstBotPoint + leftRectangle.Normalize() * projection;
		}
		if ((obstaclePosition - pointColision).Magnitude() < obstacleRadius)
		{
			if (distanceMoreClose > (m_CVec2Position - pointColision).Magnitude())
			{
				obstacleForce = (pointColision - obstaclePosition).Normalize() * STRONGFORCE;
			}
		}
		//RightVectorCollision
		obstacleDistance = obstaclePosition - lastTopPoint;
		projection = obstacleDistance.Dot(rightRectangle) / rightRectangle.Magnitude();
		if (projection < 0)
		{
			pointColision = lastTopPoint;
		}
		else if (pointColision.Magnitude() > leftRectangle.Magnitude()) {
			pointColision = lastBotPoint;
		}
		else {
			pointColision = lastTopPoint + rightRectangle.Normalize() * projection;
		}
		if ((obstaclePosition - pointColision).Magnitude() < obstacleRadius)
		{
			if (distanceMoreClose > (m_CVec2Position - pointColision).Magnitude())
			{
				obstacleForce = (pointColision - obstaclePosition).Normalize() * STRONGFORCE;
			}
		}
	}
	if (distanceMoreClose == 10000)
	{
		return obstacleForce;
	}
	return obstacleForce;
}

CVector2D CBoid::Wander1(CVector2D SizeWorld, float radiusArrival, float timeLimitSeek, float delta, float magnitudeForce)
{
	static float x = ((rand() % 201) / 100.0f) - 1.0f;
	static float y = ((rand() % 201) / 100.0f) - 1.0f;
	static float timeSeek = 0;
	static CVector2D randomTarget(x, y);

	float distance = (randomTarget - m_CVec2Position).Magnitude();
	timeSeek += delta;

	if (timeSeek > timeLimitSeek || distance < radiusArrival)
	{
		randomTarget.x = ((rand() % 201) / 100.0f) - 1.0f;
		randomTarget.y = ((rand() % 201) / 100.0f) - 1.0f;
		timeSeek = 0;
	}
	return Seek(randomTarget, magnitudeForce);
}

void CBoid::SetListObstacle(std::vector<std::shared_ptr<CObstacle>>* obstacleList)
{
	m_pObstacleList = obstacleList;
	printf("lu");
}

CBoid::CBoid()
{
	Init();
}

CBoid::~CBoid()
{
	Destroy();
}
