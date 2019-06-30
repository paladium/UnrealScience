#include "d3dUtil.h"

using namespace d3dUtil;

///Vertex Position Color
VertexPositionColor::VertexPositionColor(float _x, float _y, float _z, D3DCOLOR c)
{
	x = _x;
	y = _y;
	z = _z;
	color = c;
}

VertexPositionColor::VertexPositionColor()
{

}

/////////////////////////

VertexPositionTexture::VertexPositionTexture(float _x, float _y, float _z, float _u, float _v)
{
	x = _x;
	y = _y;
	z = _z;

	u = _u;
	v = _v;
}

VertexPositionTexture::VertexPositionTexture()
{
	u = 0;
	v = 0;
}
///////////////


VertexPositionNormalTexture::VertexPositionNormalTexture(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u, float _v)
{
	x = _x;
	y = _y;
	z = _z;

	nx = _nx;
	ny = _ny;
	nz = _nz;

	u = _u;
	v = _v;
}

VertexPositionNormalTexture::VertexPositionNormalTexture()
{

}
///////////////////////////////////////