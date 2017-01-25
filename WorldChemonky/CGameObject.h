#pragma once
#include "CVector2D.h"

class CGameObject
{
public:
	CVector2D _mPosition; //Mismo problema con estandar de variables
	virtual void Init();
	virtual void Destroy();
	virtual void Update(float delta);
	virtual void Render();

  //Falta los constructores
	virtual ~CGameObject(); //TODOS los destructores en clases derivables deben ser virtuales
	CGameObject();
};

