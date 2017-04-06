#include "CWalker.h"

float euristicQuadratic(CVector2D *vec1, CVector2D *vec2) {
	CVector2D temp = (*vec1 - *vec2);
	return temp.Dot(temp);
};
float euristicLineal(CVector2D *vec1, CVector2D *vec2) {
	return (*vec1 - *vec2).Magnitude();
};
float euristicManhattan(CVector2D *vec1, CVector2D *vec2) {
	return abs(vec1->x - vec2->x) + abs(vec1->y - vec2->y);
};

float Evaluateheuristics(CVector2D *vec1, CVector2D *vec2, HEURISTIC_TYPE::E euristicType) {
	switch (euristicType)
	{
	case HEURISTIC_TYPE::kQUADRATIC:
		return euristicQuadratic(vec1, vec2);
		break;
	case HEURISTIC_TYPE::kLINEAL:
		return euristicLineal(vec1, vec2);
		break;
	case HEURISTIC_TYPE::kMANHATTAN:
		return euristicManhattan(vec1, vec2);
		break;
	default:
		return 0;
		break;
	}
}

std::vector<node*> CWalker::PathFinding(HEURISTIC_TYPE::E euristicType)
{
	ClearWait();
	InsertNodoInWait(m_start.m_reference, NULL);
	nodeInfo* temp;
	bool flagPath = false;
	while (!EmptyListWait())
	{
		temp = NextNodoInWait();
		if (temp->m_reference == m_end.m_reference)
		{
			flagPath = true;
			break;
		}
		InsertChilds(temp);
	}
	//si encotnro el nodo final
	if (flagPath)
	{
		std::vector<node*> path;
		while(temp->m_father != NULL)
		{
			path.push_back(temp->m_reference);
			temp = temp->m_father;
		}
		path.push_back(temp->m_reference);
		return path;
	}

	return std::vector<node*>();
	
}

void CWalker::InsertChilds(nodeInfo* father)
{
	int lol = father->m_reference->m_conections.size();
	for (int i = 0; i < lol; i++)
	{
		InsertNodoInWait(father->m_reference->m_conections[i].m_node, father);
	}
}

void CWalker::SetStart(node * start)
{
	m_start.m_reference = start;
	m_start.m_father = NULL;
}

void CWalker::SetEnd(node * end)
{
	m_end.m_reference = end;
}

