#include "CBoid.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

void CBoid::Init() {
	srand(time(NULL));
	m_CVec2Direction = CVector2D(-1, 1);
	m_CVec2Direction = m_CVec2Direction.Normalize();
	m_CVec2Position = CVector2D(0, 0);
	m_fVelocity = .0f;
	m_fMaxSpeed = .5f;
	m_fRadiusSizeBoid = .01f;

	//crear path
	m_pPath.push_back(CVector2D(-.5f, -.5f));
	m_pPath.push_back(CVector2D(.5f, .5f));
	m_pPath.push_back(CVector2D(.5f, -.5f));
	m_pPath.push_back(CVector2D(-.5f, .5f));

	m_bFlagPatrol2 = false;
	m_usPathIndex = 0;
}

void CBoid::Destroy() {
}

void CBoid::Update(float delta) {
	CVector2D SteeringForce(0, 0);
	if (flag1)
	{
		//SteeringForce += FollowPath2(10.0f, .1f, .05f, 1);
		SteeringForce += FollowPath1(10.0f, .1f, 1);


	}
	if (flag2)
	{
		//SteeringForce += FollowPath2(10.0f, .1f, .05f, 2);
		SteeringForce += FollowPath1(10.0f, .1f, 2);

	}
	//SteeringForce += Wander2(5.0f, .3f, 375, .1);
	SteeringForce += ObstacleAvoidance1();
	SteeringForce += Flocking(10.0f, 10.0f, 10.0f);
	m_fVelocity = SteeringForce.Truncate(m_fMaxSpeed) * delta;
	m_CVec2Direction = (m_CVec2Direction + SteeringForce.Normalize()).Normalize();
	
	

}

void CBoid::Render() {
	m_CVec2Position += m_CVec2Direction * m_fVelocity;

	m_PrimitiveInstance->TranslateAbsolute(m_CVec2Position.x, m_CVec2Position.y, 0);
	m_PrimitiveInstance->Update();
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

CVector2D CBoid::Circle(float radioOrbita, float radioArrive)
{
	static float delta = .01f;
	static CVector2D target(radioOrbita*cosf(delta), radioOrbita * sinf(delta));

	CVector2D seekForce = Seek(target, FORCESEEK);

	float distance = (target - m_CVec2Position).Magnitude();

	if (distance < radioArrive)
	{
		delta += .01;
		target.x = radioOrbita*cosf(delta);
		target.y = radioOrbita*sinf(delta);
	}
	return Seek(target, FORCESEEK);
}

CVector2D CBoid::ObstacleAvoidance1()
{
	CVector2D finalFuturePosition = m_CVec2Position + m_CVec2Direction * m_fVelocity * 1;
	CVector2D halfFuturePosition = finalFuturePosition * 0.5f;

	float distanceMoreClose = 10000;
	CVector2D obstacleForce = CVector2D(0, 0);

	for (auto &obstacle : *m_pGameObjects) {
		if (obstacle->GetClassId() == CLASSOBSTACLE)
		{
			float addRadius = std::dynamic_pointer_cast<CObstacle>(obstacle)->GetRadius() + m_fRadiusSizeBoid;
			CVector2D obstaclePosition = (*obstacle).GetPosition();

			if ((obstaclePosition - m_CVec2Position).Magnitude() < addRadius)
			{
				if (distanceMoreClose > (obstaclePosition - m_CVec2Position).Magnitude())
				{
					obstacleForce = (m_CVec2Position - obstaclePosition).Normalize() * STRONGFORCE;
					distanceMoreClose = (obstaclePosition - m_CVec2Position).Magnitude();
				}
			}
			if ((obstaclePosition - halfFuturePosition).Magnitude() < addRadius)
			{
				if (distanceMoreClose > (obstaclePosition - halfFuturePosition).Magnitude())
				{
					obstacleForce = (halfFuturePosition - obstaclePosition).Normalize() * STRONGFORCE;
					distanceMoreClose = (obstaclePosition - halfFuturePosition).Magnitude();
				}
			}
			if ((obstaclePosition - finalFuturePosition).Magnitude() < addRadius)
			{
				if (distanceMoreClose > (obstaclePosition - finalFuturePosition).Magnitude())
				{
					obstacleForce = (finalFuturePosition - obstaclePosition).Normalize() * STRONGFORCE;
					distanceMoreClose = (obstaclePosition - finalFuturePosition).Magnitude();
				}
			}
		}
	}
	return obstacleForce;
}

CVector2D CBoid::ObstacleAvoidance2()
{
	CVector2D perpendicularDirection = CVector2D(-m_CVec2Direction.y, m_CVec2Direction.x).Normalize();
	CVector2D lastMiddlePoint = m_CVec2Position + m_CVec2Direction*m_fVelocity *80.0f;
	CVector2D firstMiddlePoint = m_CVec2Position - (m_CVec2Direction * m_fRadiusSizeBoid);
	CVector2D firstTopPoint = firstMiddlePoint + perpendicularDirection * m_fRadiusSizeBoid;
	CVector2D firstBotPoint = firstMiddlePoint - perpendicularDirection * m_fRadiusSizeBoid;
	CVector2D lastTopPoint = lastMiddlePoint + perpendicularDirection * m_fRadiusSizeBoid;
	CVector2D lastBotPoint = lastMiddlePoint - perpendicularDirection * m_fRadiusSizeBoid;
	/*printf("radio=%f\n", m_fRadiusSizeBoid);
	printf("Topleftx=%f y=%f \n", m_CVec2Position.x, m_CVec2Position.y);

	printf("Topleftx=%f y=%f \n", firstTopPoint.x, firstTopPoint.y);
	printf("toprightx=%f y=%f \n", lastTopPoint.x, lastTopPoint.y);
	printf("botlrftx=%f y=%f \n", firstBotPoint.x, firstBotPoint.y);
	printf("botrightx=%f y=%f \n", lastBotPoint.x, lastBotPoint.y);*/

	CVector2D topRectangle = lastTopPoint - firstTopPoint;
	CVector2D botRectangle = lastBotPoint - firstBotPoint;
	CVector2D leftRectangle = firstTopPoint - firstBotPoint;
	CVector2D rightRectangle = lastBotPoint - lastTopPoint;

	CVector2D obstacleForce = CVector2D(0, 0);
	float distanceMoreClose = 10000;

	for (auto &obstacle : *m_pGameObjects) {
		if (obstacle->GetClassId() == CLASSOBSTACLE)
		{
			CVector2D obstaclePosition = (*obstacle).GetPosition();
			float obstacleRadius = std::dynamic_pointer_cast<CObstacle>(obstacle)->GetRadius();
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
					distanceMoreClose = (m_CVec2Position - pointColision).Magnitude();
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
					distanceMoreClose = (m_CVec2Position - pointColision).Magnitude();
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
					distanceMoreClose = (m_CVec2Position - pointColision).Magnitude();

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
					distanceMoreClose = (m_CVec2Position - pointColision).Magnitude();
				}
			}
		}
	}

	return obstacleForce;
}

//TypePatrol 1= 0,1,2....n,0,1,2...   2= 0,1,2....n, n-1, n-2, .....2, 1, 0, 1, 2
CVector2D CBoid::FollowPath1(float magnitudeForce, float radioArrive, unsigned short typePatrol)
{

	CVector2D target = m_pPath[m_usPathIndex];

	float distance = (target - m_CVec2Position).Magnitude();

	if (distance < radioArrive)
	{
		if (m_bFlagPatrol2)
		{
			if (m_usPathIndex)
			{
				m_usPathIndex--;
			}
			else
			{
				m_bFlagPatrol2 = false;
			}
		}
		else if (m_usPathIndex < m_pPath.size()-1)
		{
			m_usPathIndex++;
		}
		else if (typePatrol == 1)
		{
			m_usPathIndex = 0;
		}
		else if (typePatrol == 2)
		{
			m_bFlagPatrol2 = true;
			m_usPathIndex--;
		}
	}

	return Seek(target, magnitudeForce);
}

//TypePatrol 1= 0,1,2....n,0,1,2...   2= 0,1,2....n, n-1, n-2, .....2, 1, 0, 1, 2
CVector2D CBoid::FollowPath2(float magnitudeForce, float radioArrive, float distanceMaxPath, unsigned short typePatrol)
{
	CVector2D forceNextPoint = FollowPath1(magnitudeForce, radioArrive, typePatrol);
	if (m_usPathIndex && ((m_pPath.size()-1) != m_usPathIndex))
	{
		CVector2D distanceBetweenPath = m_pPath[m_usPathIndex - 1] - m_pPath[m_usPathIndex];
		CVector2D distanceNextTarget = m_CVec2Position - m_pPath[m_usPathIndex + 1];
		float projection = distanceBetweenPath.Dot(distanceNextTarget) / distanceBetweenPath.Magnitude();
		CVector2D pointColision = m_pPath[m_usPathIndex] + distanceBetweenPath.Normalize() * projection;

			forceNextPoint += (pointColision - m_CVec2Position).Normalize() * magnitudeForce;

	}
	return forceNextPoint;
}

CVector2D CBoid::Direction()
{
	CVector2D averageDirection = CVector2D(0, 0);

	for (auto &boid : *m_pGameObjects) {
		if ((*boid).GetClassId() == CLASSBOID)
		{
			CVector2D boidPosition = (*boid).GetPosition();
			float distance = (m_CVec2Position - boidPosition).Magnitude();
			if (distance < RADIOFLOCKING)
			{
				CVector2D direction = std::dynamic_pointer_cast<CBoid>(boid)->GetDirection();
				averageDirection += direction;
			}
		}
	}
	return averageDirection.Normalize();
}

CVector2D CBoid::Separation(float magnitudeForce)
{
	CVector2D totalForce = CVector2D(0, 0);
	for (auto &boid : *m_pGameObjects) {
		if ((*boid).GetClassId() == CLASSBOID)
		{
			CVector2D boidPosition = (*boid).GetPosition();
			CVector2D direction = m_CVec2Position - boidPosition;
			float distance = direction.Magnitude();
			if (distance < RADIOFLOCKING)
			{
				float force = (1-(distance/RADIOFLOCKING)) *magnitudeForce;
				totalForce += direction.Normalize() * force;
			}
		}
	}
	return totalForce;
}

CVector2D CBoid::Cohesion(float magnitudeForce)
{
	int counter = 0;
	CVector2D centralPoint = CVector2D(0, 0);

	for (auto &boid : *m_pGameObjects) {
		if ((*boid).GetClassId() == CLASSBOID)
		{
			CVector2D boidPosition = (*boid).GetPosition();
			CVector2D direction = m_CVec2Position - boidPosition;
			float distance = direction.Magnitude();
			if (distance < RADIOFLOCKING)
			{
				centralPoint += boidPosition;
				counter++;
			}
		}
	}
	centralPoint /= counter;
	return (centralPoint - m_CVec2Position).Normalize() * magnitudeForce * (centralPoint.Magnitude() / RADIOFLOCKING);
}

CVector2D CBoid::Flocking(float magnitudForce, float magnitudSeparationForce, float magnitudCoheisonForce)
{
	CVector2D flockingForce;
	flockingForce = Separation(magnitudSeparationForce);
	flockingForce += Cohesion(magnitudCoheisonForce);
	flockingForce += Direction()*magnitudForce;

	return flockingForce;
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

void CBoid::SetListObstacle(std::vector<std::shared_ptr<CGameObject>>* gameObjectsList)
{
	m_pGameObjects = gameObjectsList;
}

CVector2D CBoid::GetDirection()
{
	return m_CVec2Direction;
}

CBoid::CBoid()
{
}

CBoid::~CBoid()
{
	Destroy();
}
