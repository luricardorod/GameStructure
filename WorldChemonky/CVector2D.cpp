#include "stdafx.h"
#include "CVector2D.h"
#include <cmath>
CVector2D::CVector2D()
{
}

CVector2D::CVector2D(const CVector2D& V)
{
	x = V.x;
	y = V.y;
}
CVector2D::CVector2D(const float fx, const float fy)
{
	x = fx;
	y = fy;
}

CVector2D::~CVector2D()
{
}
CVector2D operator* (const CVector2D  &A, const CVector2D &B)
{
	return CVector2D(A.x*B.x, A.y*B.y);
}
CVector2D operator* (float s, const CVector2D &A)
{
	return CVector2D(A.x*s, A.y*s);
}
CVector2D operator* (const CVector2D &A, float s)
{
	return s*A;
}
CVector2D operator/ (const CVector2D &A, float s)
{
	return A*(1 / s);
}
CVector2D operator+(const CVector2D& A, const CVector2D& B)
{
	return CVector2D(A.x + B.x, A.y + B.y);
}
CVector2D operator-(const CVector2D& A, const CVector2D& B)
{
	return CVector2D(A.x - B.x, A.y - B.y);

}
float Dot(const CVector2D &A, const CVector2D &B)
{
	return A.x*B.x + A.y*B.y;
}

float Magnity(const CVector2D& A)
{//Que pasa si la magnitud es 0?
	return std::sqrt(Dot(A, A));
}
CVector2D Normalize(const CVector2D& A)
{//Que pasa si la magnitud es 0?
	return A / Magnity(A);
}
