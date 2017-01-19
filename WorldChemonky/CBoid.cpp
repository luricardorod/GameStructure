#include "stdafx.h"
#include "CBoid.h"

void CBoid::Init() {
}

void CBoid::Destroy() {
}

void CBoid::Update(float delta) {
	if (Magnity(_mVelocity) > _mMaxSpeed)
	{
		_mVelocity = Normalize(_mVelocity) * _mMaxSpeed;
	}
	_mPosition = _mPosition + _mVelocity * delta;
}
void CBoid::Render() {
}

CVector2D CBoid::Seek(CVector2D position, float forceValue) {
	return Normalize(position - _mPosition) * forceValue;
}

CVector2D CBoid::Flee(CVector2D position, float forceValue, float radiusOfForceAplication) {
	CVector2D direction = _mPosition - position;
	if (Magnity(direction) < radiusOfForceAplication) 
	{
		return Normalize(direction) * forceValue;
	}
	return CVector2D(0, 0);
}

CVector2D CBoid::Arrive(CVector2D position, float forceValue, float radiusOfForceAplication) {
	CVector2D arriveForce = Seek(position, forceValue);
	float distance = Magnity(position - _mPosition);
	if (distance < radiusOfForceAplication)
	{
		arriveForce = arriveForce * (distance / radiusOfForceAplication);
	}
	return arriveForce;
}
