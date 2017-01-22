#pragma once

#include "CGameObject.h"
#include <list>

//Esto no es aceptable, para que incluir todo el namespace cuando solo usa un objeto?
//Cambiar por "using std::list", es más facil de saber que es lo que se está utilizando
using namespace std;  

class CWorld
{
public:
	list<CGameObject *> gameObjects;  //Tambien es un miembro de la clase "m_"
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	CWorld();
	~CWorld();
};

//No le tema a espaciar y a organizar su código