#pragma once
#include "CVector2D.h"

class CGameObject
{
protected:
	CVector2D m_CVec2Position; //Mismo problema con estandar de variables
public:
	virtual void Init() = 0;
	virtual void Destroy() = 0;
	virtual void Update(float delta) = 0;
	virtual void Render() = 0;

  //Falta los constructores
	virtual ~CGameObject(); //TODOS los destructores en clases derivables deben ser virtuales
	CGameObject();
	CVector2D GetPosition();
	void SetPosition(CVector2D position);
};

