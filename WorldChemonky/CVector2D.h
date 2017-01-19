#pragma once

class CVector2D
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
	};
	CVector2D();
	CVector2D(const CVector2D& V);
	CVector2D(const float fx, const  float fy);
	~CVector2D();
};
CVector2D operator* (const CVector2D  &A, const CVector2D &B);
CVector2D operator* (float s, const CVector2D &A);
CVector2D operator* (const CVector2D &A, float s);
CVector2D operator/ (const CVector2D &A, float s);
CVector2D operator+(const CVector2D& A, const CVector2D& B);
CVector2D operator-(const CVector2D& A, const CVector2D& B);

float Dot(const CVector2D &A, const CVector2D &B);

float Magnity(const CVector2D& A);
CVector2D Normalize(const CVector2D& A);

