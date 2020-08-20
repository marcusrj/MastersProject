#include "pch.h"
#include "Forest.h"


Forest::Forest() 
{

}

Forest::Forest(int terrainHeight, int terrainWidth)
{
	m_terrainHeight = terrainHeight;
	m_terrainWidth = terrainWidth;

	srand((unsigned)time(0));

	//Semi-random spacing
	m_spacing = 5 + rand() % 3;
	
	//Semi-random forest width
	m_forestWidth = 4 + rand() % 4;
	m_forestHeight = 4 + rand() % 4;

	//rough island start postion
	int start = terrainWidth / 2 - terrainWidth / 5;
	//rough island width
	int islandWidth = (terrainWidth / 5) * 2;

	m_forestX = 300 + rand() % 400;
	m_forestZ = 300 + rand() % 400;

	//calulate number of trees
	m_noOfTrees = m_forestWidth * m_forestHeight;

	//tree storage, each tree is a set of coordinates hence vector3
	m_trees = new DirectX::SimpleMath::Vector3[m_noOfTrees];

}

Forest::Forest(int spacing, int forestX, int forestZ, int terrainWidth, int terrainHeight, int forestWidth, int forestHeight)
{
	m_terrainHeight = terrainHeight;
	m_terrainWidth = terrainWidth;

	m_spacing = spacing;

	m_forestHeight = forestHeight;
	m_forestWidth = forestWidth;

	m_forestX = forestX;
	m_forestZ = forestZ;
	
	m_noOfTrees = m_forestWidth * m_forestHeight;

	m_trees = new DirectX::SimpleMath::Vector3[m_noOfTrees];
}

Forest::Forest(int spacing, int terrainWidth, int terrainHeight, int forestWidth, int forestHeight)
{

}


Forest::~Forest()
{

}

void Forest::Initialize(int terrainWidth, int terrainHeight, Terrain::HeightMapType* heightmap,int seed)
{
	m_terrainHeight = terrainHeight;
	m_terrainWidth = terrainWidth;

	srand((unsigned)time(0)+seed);

	//Semi-random spacing
	m_spacing = 5 + rand() % 3;

	//Semi-random forest width
	m_forestWidth = 4 + rand() % 4;
	m_forestHeight = 4 + rand() % 4;

	//rough island start postion
	int start = terrainWidth / 2 - terrainWidth / 5;
	//rough island width
	int islandWidth = (terrainWidth / 5) * 2;


	int index = 0;
	do
	{
		m_forestX = 200 + rand() % 600;
		m_forestZ = 200 + rand() % 600;
		index = (m_forestX * m_terrainHeight) + m_forestZ;
	} while (heightmap[index].y <=3.4f);




	//calulate number of trees
	m_noOfTrees = m_forestWidth * m_forestHeight;

	//tree storage, each tree is a set of coordinates hence vector3
	m_trees = new DirectX::SimpleMath::Vector3[m_noOfTrees];
}

/*
	Jittered grid tree placement

	
*/
void Forest::TreePlacement(int spacing, int forestX, int forestY)
{
	//int treeStartX, treeWidth, treeStartY, treeHeight;

	int treeIndex = 0;

	int heightmapIndex = 0;
	int startX = forestX; //- (m_forestWidth * spacing) / 2;
	int startY = forestY; //- (m_forestHeight * spacing) / 2;

	int endX = startX + (m_forestHeight * spacing);

	//make sure we dont go off the edge of the terrain
	if (endX > m_terrainWidth)
	{
		endX = m_terrainWidth;
	}

	int endY = startY + (m_forestWidth * spacing);
	//make sure we dont go off the edge of the terrain
	if (endY > m_terrainHeight)
	{
		endY = m_terrainHeight;
	}

	//random seed
	srand((unsigned)time(0));

	//loop from start of forest to end of forest incremented by initial tree spacing
	for (int j = startY; j < endY; j += spacing)
	{
		for (int i = startX; i < endX; i += spacing)
		{
			//calculate jitter
			int jitterX = j + (rand() % (spacing + 1) - (spacing - 2) / 2);
			int jitterY = i + (rand() % (spacing + 1) - (spacing - 2) / 2);

			//find point on terrain relative to tree
			heightmapIndex = (jitterX * m_terrainHeight) + jitterY;

			//give tree the same coords as terrain vertex
			m_trees[treeIndex].x = m_heightMap[heightmapIndex].x;
			m_trees[treeIndex].y = m_heightMap[heightmapIndex].y;
			m_trees[treeIndex].z = m_heightMap[heightmapIndex].z;

			treeIndex++;
		}
	}
}

void Forest::TreePlacement(Terrain::HeightMapType* heightmap)
{
	m_heightMap = heightmap;
	int spacing = m_spacing;
	int forestX = m_forestX;
	int forestY = m_forestZ;
	//int treeStartX, treeWidth, treeStartY, treeHeight;

	int treeIndex = 0;

	int heightmapIndex = 0;
	int startX = forestX; //- (m_forestWidth * spacing) / 2;
	int startY = forestY; //- (m_forestHeight * spacing) / 2;

	int endX = startX + (m_forestHeight * spacing);

	//make sure we dont go off the edge of the terrain
	if (endX > m_terrainWidth)
	{
		endX = m_terrainWidth;
	}

	int endY = startY + (m_forestWidth * spacing);
	//make sure we dont go off the edge of the terrain
	if (endY > m_terrainHeight)
	{
		endY = m_terrainHeight;
	}

	//random seed
	srand((unsigned)time(0));

	//loop from start of forest to end of forest incremented by initial tree spacing
	for (int j = startY; j < endY; j += spacing)
	{
		for (int i = startX; i < endX; i += spacing)
		{
			//calculate jitter
			int jitterX = j + (rand() % (spacing + 1) - (spacing - 2) / 2);
			int jitterY = i + (rand() % (spacing + 1) - (spacing - 2) / 2);

			//find point on terrain relative to tree
			heightmapIndex = (jitterX * m_terrainHeight) + jitterY;

			//give tree the same coords as terrain vertex
			m_trees[treeIndex].x = m_heightMap[heightmapIndex].x;
			m_trees[treeIndex].y = m_heightMap[heightmapIndex].y;
			m_trees[treeIndex].z = m_heightMap[heightmapIndex].z;

			treeIndex++;
		}
	}
}

DirectX::SimpleMath::Vector3* Forest::getTrees()
{
	return m_trees;
}

int Forest::getNumberTrees()
{
	return m_noOfTrees;
}

void Forest::UpdateHeightmap(Terrain::HeightMapType* heightMap)
{
	m_heightMap = heightMap;
	TreePlacement(m_spacing, m_forestX, m_forestZ);
}