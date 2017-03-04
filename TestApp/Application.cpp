#include "Application.h"

void TestApp::InitVars() {
	DtTimer.Init();
	Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Orientation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scaling		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void TestApp::CreateAssets() {	
	PrimitiveMgr.SetVP(&VP);
	int indexTriangle = PrimitiveMgr.CreateTriangle();
	int indexCube = PrimitiveMgr.CreateCube();
	int indexCuad = PrimitiveMgr.CreateCuad();
	int counterCuads = 0;
	int counterTriangles = 0;
	for (auto &gameObject : m_WorldChemonky.m_pGameObjects) {
		unsigned short type = gameObject->GetClassId();
		switch (type)
		{
		case CLASSBOID:
			Triangles[counterTriangles].CreateInstance(PrimitiveMgr.GetPrimitive(indexTriangle), &VP);
			(*gameObject).m_PrimitiveInstance = &Triangles[counterTriangles];
			counterTriangles++;
			break;
		case CLASSOBSTACLE:
			
			Cuads[counterCuads].CreateInstance(PrimitiveMgr.GetPrimitive(indexCuad), &VP);
			(*gameObject).m_PrimitiveInstance = &Cuads[counterCuads];
			counterCuads++;
			
			/*
			Triangles[counterTriangles].CreateInstance(PrimitiveMgr.GetPrimitive(indexTriangle), &VP);
			(*gameObject).m_PrimitiveInstance = &Triangles[counterTriangles];
			counterTriangles++;
			/*Cubes[counterCubes].CreateInstance(PrimitiveMgr.GetPrimitive(indexCube), &VP);
			(*gameObject).m_PrimitiveInstance = &Cubes[counterCubes];
			counterCubes++;*/
			break;
		default:
			break;
		}
	}

	D3DXMATRIX View;
	D3DXVECTOR3 Pos		= D3DXVECTOR3(0.0f,1.0f,5.0f);
	D3DXVECTOR3 Up		= D3DXVECTOR3(0.0f,1.0f,0.0f);
	D3DXVECTOR3 LookAt	= D3DXVECTOR3(0.0001f, 0.0001f, 0.0001f) - Pos;
	D3DXMatrixLookAtRH(&View,&Pos,&LookAt,&Up);
	D3DXMATRIX Proj;

	D3DXMatrixPerspectiveFovRH(&Proj,D3DXToRadian(45.0f),1280.0f/720.0f,0.1f,1000.0f);
	//	D3DXMatrixOrthoRH(&Proj, 1280.0f / 720.0f, 1.0f , 0.1, 100.0f);
	VP = View*Proj;
}

void TestApp::DestroyAssets() {
	PrimitiveMgr.DestroyPrimitives();
}

void TestApp::OnUpdate() {
	DtTimer.Update();

	OnInput();
	static float time = 0;
	time += DtTimer.GetDTSecs();
	if (time > 4/60.0f)
	{
		m_WorldChemonky.Update(DtTimer.GetDTSecs());
		time = 0;
	}
	/*Cubes[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Cubes[0].RotateXAbsolute(Orientation.x);
	Cubes[0].RotateYAbsolute(Orientation.y);
	Cubes[0].RotateZAbsolute(Orientation.z);
	Cubes[0].ScaleAbsolute(Scaling.x);
	Cubes[0].Update();

	static float freq = DtTimer.GetDTSecs();
	freq += 10.0f*DtTimer.GetDTSecs();

	if (freq > 36.0f)
		freq = 0.0f;

	Cubes[1].TranslateAbsolute(1.5f*exp(0.1f*-freq)*sin(freq), 1.5f*exp(0.1f*-freq)*cos(freq), 0.0f);
	Cubes[1].RotateXRelative(180.0f*DtTimer.GetDTSecs());
	Cubes[1].RotateYRelative(180.0f*DtTimer.GetDTSecs());
	Cubes[1].RotateZRelative(180.0f*DtTimer.GetDTSecs());
	Cubes[1].ScaleAbsolute(0.15f);
	Cubes[1].Update();

	Triangles[0].Update();*/

	OnDraw();
}

void TestApp::OnDraw() {
	pFramework->pVideoDriver->Clear();
	
	m_WorldChemonky.Render();
	pFramework->pVideoDriver->SwapBuffers();
}

void TestApp::OnInput() {
	
	if (IManager.PressedKey(SDLK_UP)) {
		Position.y += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_DOWN)) {
		Position.y -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_LEFT)) {
		Position.x -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_RIGHT)) {
		Position.x += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_z)) {
		Position.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_x)) {
		Position.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_PLUS)) {
		Scaling.x += 1.0f*DtTimer.GetDTSecs();
		Scaling.y += 1.0f*DtTimer.GetDTSecs();
		Scaling.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_MINUS)) {
		Scaling.x -= 1.0f*DtTimer.GetDTSecs();
		Scaling.y -= 1.0f*DtTimer.GetDTSecs();
		Scaling.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP5)) {
		Orientation.x -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP6)) {
		Orientation.x += 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP2)) {
		Orientation.y -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP3)) {
		Orientation.y += 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP0)) {
		Orientation.z -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_PERIOD)) {
		Orientation.z += 60.0f*DtTimer.GetDTSecs();
	}

	
}

void TestApp::OnPause() {

}

void TestApp::OnResume() {

}

void TestApp::OnReset() {

}