#include "Mesh3D.h"
#include "Cube.h"
#include "d3dUtil.h"
#include <vector>


class WorldSystem{


public:

	WorldSystem(IDirect3DDevice9 &device);

	bool CheckIndex();

	void Render();

	void Cleanup();

	int GetSelected(){ return selected; }

	void SetSelected(unsigned int _selected){ if (_selected <= World.size() && _selected >= 1) selected = _selected - 1; }
	
	void Update(D3DXMATRIX projection, D3DXMATRIX view);

	//Object`s manipulations
	void CreateCube();

	void MoveObject(float x, float y, float z);

	void Rotate(float x, float y, float z);

	void ResizeObject(float x, float y, float z);

	void DeleteObject();

	void SetTexture(char* t);

	void Translate(float x, float y, float z);

	void IncreaseDecrease(float x, float y, float z);

	void Clone();

	void ChangeName(const char* to);

	void CreateFromModel(char* path);

	void ChangeColor(int r, int g, int b);

	///////////

	int EntityNumber();

	float* GetPosition(int index);
private:
	std::vector<Mesh3D*> World;


	int selected = 0;

	IDirect3DDevice9* appDevice3D;
};