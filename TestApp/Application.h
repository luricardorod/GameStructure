#include <Core.h>
#include <PrimitiveManager.h>
#include <PrimitiveInstance.h>

#include <d3dx9math.h>
#include <Timer.h>

#include "CWorld.h"

class TestApp : public AppBase {
public:
	TestApp() : AppBase() {}
	void InitVars();
	void CreateAssets();
	void DestroyAssets();

	void OnUpdate();
	void OnDraw();
	void OnInput();

	void OnPause();
	void OnResume();

	void OnReset();

	PrimitiveManager PrimitiveMgr;
	PrimitiveInst	Cubes[10];
	PrimitiveInst	Triangles[30];

	D3DXVECTOR3		Position;
	D3DXVECTOR3		Orientation;
	D3DXVECTOR3		Scaling;

	D3DXMATRIX		View;
	D3DXMATRIX		Projection;
	D3DXMATRIX		VP;

	Timer			DtTimer;

	CWorld			m_WorldChemonky;
};