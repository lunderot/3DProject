#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <stdexcept>
#include <windows.h>
#include "VertexTypes.h"
#include "Texture.h"

class Terrain
{
private:

	//For our texture-blending to work this has to be set to 1. 
	//If no blending is used then repeating texture works
	const int TEXTURE_REPEAT = 1;

	struct float3
	{
		float x, y, z;
	};

	struct HeightMap
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	int terrainWidth;
	int terrainHeight;
	int vertexCount;
	int indexCount;

	HeightMap* heightMap;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	Texture* texture[4];

	ID3D11ShaderResourceView* textureArray[4];

	void InitializeBuffers(ID3D11Device* device);
	void SetBuffers(ID3D11DeviceContext* deviceContext);

	bool LoadHeightMap(char* filename);
	void NormalizeHeightMap(float factor);
	void CalculateNormals();
	void CalculateTextureCoordinates();

	float GetHeightAt(int x, int z);

public:

	Terrain(ID3D11Device* device, char* heightMapName, float normalizeFactor, std::string blendMapFilename, std::string grassTextureFilename, std::string stoneTextureFilename, std::string sandTextureFilename);
	~Terrain();

	void Render(ID3D11DeviceContext* deviceContext);

	float GetY(float x, float z);
	
	int GetIndexCount();
	ID3D11ShaderResourceView** GetTextures();
};
