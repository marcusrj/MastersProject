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

	m_spacing = 5 + rand() % 3;
	
	m_forestWidth = 4 + rand() % 4;
	m_forestHeight = 4 + rand() % 4;

	//wont really work without terrain width of 1000
	m_forestX = 300 + rand() % 400;
	m_forestZ = 300 + rand() % 400;

	m_noOfTrees = m_forestWidth * m_forestHeight;

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

/*
	Jittered grid tree placement

	TODO *this should definitely be in its own class*
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

DirectX::SimpleMath::Vector3* Forest::getTrees()
{
	return m_trees;
}

int Forest::getNumberTrees()
{
	return m_noOfTrees;
}

void Forest::UpdateHeightmap(HeightMapType* heightMap)
{
	m_heightMap = heightMap;
	TreePlacement(m_spacing, m_forestX, m_forestZ);
}