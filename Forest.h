#pragma once
#include <time.h>
#include "Terrain.h"
using namespace DirectX;
class Forest
{
	private:

		//struct HeightMapType
		//{
		//	float x, y, z;
		//	float nx, ny, nz;
		//	float u, v;
		//};

	public:

		Forest();
		Forest(int spacing, int forestX, int forestZ, int terrainWidth, int terrainHeight,int forestWidth, int forestHeight);
		Forest(int spacing, int terrainWidth, int terrainHeight, int forestWidth, int forestHeight);
		Forest(int terrainHeight, int forestWidth);
		~Forest();
		DirectX::SimpleMath::Vector3* getTrees();
		int getNumberTrees();
		void TreePlacement(int spacing, int forestX, int forestY);
		void TreePlacement(Terrain::HeightMapType* heightMap);
		void UpdateHeightmap(Terrain::HeightMapType* heightMap);
		void Initialize(int terrainWidth, int terrainHeight);
		DirectX::SimpleMath::Vector3* m_trees;
	private:


	private:

		int m_forestX, m_forestZ;
		int m_spacing;
		int m_forestWidth, m_forestHeight;
		int m_noOfTrees;
		int m_terrainWidth, m_terrainHeight;
		
		Terrain::HeightMapType* m_heightMap;



};

