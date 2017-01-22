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
	CVector2D(const float fx, const  float fy); //Por que mandar constantes y no copias?
	~CVector2D();
};

//Alguna raz�n por la cual no meter todo esto a la misma clase?
//Ahorramos un par�metro y podemos considerar operadores de modificaci�n
//O si solo van a ser datos... entonces Vector deber�a de ser una estructura
//Aqu� hay que considerar que estamos en C++, no en C.

CVector2D operator* (const CVector2D  &A, const CVector2D &B);
CVector2D operator* (float s, const CVector2D &A);
CVector2D operator* (const CVector2D &A, float s);
CVector2D operator/ (const CVector2D &A, float s);
CVector2D operator+(const CVector2D& A, const CVector2D& B);
CVector2D operator-(const CVector2D& A, const CVector2D& B);

float Dot(const CVector2D &A, const CVector2D &B);

float Magnity(const CVector2D& A); //La palabra es Magnitude
CVector2D Normalize(const CVector2D& A);

