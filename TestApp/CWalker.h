#pragma once
#include "CVector2D.h"
#include <vector>
enum TYPEEURISTICS
{
	QUADRATIC,
	LINEAL,
	MANHATTAN
};
struct nodo;
struct Conection
{
	float m_fvalue;
	nodo* m_nodo;
	Conection(float val, nodo* nodo) {
		m_fvalue = val;
		m_nodo = nodo;
	}
};
struct nodo
{
	CVector2D m_position;
	std::vector<Conection> m_conections;
	nodo* m_father;
	int m_id;
	float m_value;
	nodo* m_reference;
	nodo operator=(nodo *temp) {
		m_position = temp->m_position;
		m_conections = temp->m_conections;
		m_father = NULL;
		m_id = temp->m_id;
		m_value = temp->m_value;
		m_reference = temp;
		return *this;
	}
	float euristicQuadratic(CVector2D *nodo) {
		CVector2D temp = (m_position - (*nodo));
		return temp.Dot(temp);
	};
	float euristicLineal(CVector2D *nodo) {
		return (m_position - (*nodo)).Magnitude();
	};
	float euristicManhattan(CVector2D *nodo) {
		return abs(m_position.x - (*nodo).x) + abs(m_position.y - (*nodo).y);
	};

	float Evaluateheuristics(CVector2D *nodo, int type) {
		switch (type)
		{
		case QUADRATIC:
			return euristicQuadratic(nodo);
			break;
		case LINEAL:
			return euristicLineal(nodo);
			break;
		case MANHATTAN:
			return euristicManhattan(nodo);
			break;
		default:
			break;
		}
		return 0;
	}
};

class CWalker
{
public:
	std::vector<nodo*> m_reviewed;
	virtual void PathFinding(nodo *start, nodo*end, std::vector<nodo*> *path, int euristicType) = 0;
	virtual ~CWalker() {}
};

