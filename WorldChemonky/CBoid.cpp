#include "stdafx.h"
#include "CBoid.h"

void CBoid::Init() {
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
CVector2D CBoid::Seek(CVector2D position, float forceValue) {
	return Normalize(position - _mPosition) * forceValue;
}

//Si forceValue y el radio pueden ser considerados constantes, pueden tener defaults? en que orden irían?
CVector2D CBoid::Flee(CVector2D position, float forceValue, float radiusOfForceAplication) {
	CVector2D direction = _mPosition - position;
	if (Magnity(direction) < radiusOfForceAplication) 
	{
		return Normalize(direction) * forceValue;
	}
	return CVector2D(0, 0);
}

//Si forceValue y el radio pueden ser considerados constantes, pueden tener defaults? en que orden irían?
CVector2D CBoid::Arrive(CVector2D position, float forceValue, float radiusOfForceAplication) {
	//Los radios pueden ser 0?, que pasa si la fuerza es 0?
  
  CVector2D arriveForce = Seek(position, forceValue);
	float distance = Magnity(position - _mPosition);
	if (distance < radiusOfForceAplication)
	{
    //Justo por esto debería tener operador *=
		arriveForce = arriveForce * (distance / radiusOfForceAplication);
	}

	return arriveForce;
}
