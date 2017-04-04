#pragma once
#include "CVector2D.h"
#include <vector>

namespace HEURISTIC_TYPE
{
	enum E
	{
		kNONE,
		kQUADRATIC,
		kLINEAL,
		kMANHATTAN,
		kNUM_MAX
	};
}

struct node;
struct Conection
{
	float m_fvalue;
	node* m_node;
	Conection(float val, node* node) {
		m_fvalue = val;
		m_node = node;
	}
};

struct node
{
	int m_iid;
	CVector2D m_position;
	std::vector<Conection> m_conections;
};


struct nodeInfo 
{
	nodeInfo* m_father;
	float m_fvalue;
	node* m_reference;
};


class CWalker
{
private:
	nodeInfo m_start;
	nodeInfo m_end;
public:
	std::vector<nodeInfo> m_reviewed;
	void SetStart(node* start);
	void SetEnd(node* end);
	std::vector<node*> PathFinding(HEURISTIC_TYPE::E euristicType=HEURISTIC_TYPE::kNONE);
	
	virtual void InsertNodoInWait(node *newNodo, nodeInfo *father) = 0;
	void InsertChilds(nodeInfo father);
	virtual void ClearWait() = 0;
	virtual bool EmptyListWait() = 0;
	virtual nodeInfo NextNodoInWait() = 0;
	virtual ~CWalker() {}
};

