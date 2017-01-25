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
	CVector2D(CVector2D &V);
	CVector2D(float fx, float fy); //Por que mandar constantes y no copias?
	CVector2D();
	~CVector2D();
	
	CVector2D operator* (CVector2D  &A);
	CVector2D operator* (float s);
	CVector2D operator*= (float s);
	CVector2D operator/ (float s);
	CVector2D operator+(CVector2D& A);
	CVector2D operator+=(CVector2D& A);
	CVector2D operator-(CVector2D& A);

	float Dot(CVector2D &A);
	float Truncate(float maxValue);
	float Magnitude(); //La palabra es Magnitude
	CVector2D Normalize();
};