#pragma once
#include "Terrain.h"
#include <list>
class AStar
{
public:
	struct RoadNode{
		float x, y, z;
		float costToParent;
		float costToGoal;
		RoadNode* parent;
		RoadNode* child;
	};

	

	AStar();
	~AStar();

	Terrain::HeightMapType* m_heightMap;
	int m_terrainWidth, m_terrainHeight, m_indexCount;


	std::list<AStar::RoadNode> m_Road;
	//std::list<Terrain::HeightMapType> m_Road;
	std::list<Terrain::HeightMapType> m_RoadNetwork;


	void Initialise(Terrain::HeightMapType* heightmap);

	void firstRoad(Terrain::HeightMapType p1, Terrain::HeightMapType p2);

	//p2 replaced with existing network

	void newRoad(Terrain::HeightMapType p1, Terrain::HeightMapType p2);

	std::list<AStar::RoadNode> AStar::getRoad();


	float DistanceXZ(Terrain::HeightMapType p1, Terrain::HeightMapType p2);

	float Cost(Terrain::HeightMapType p1, Terrain::HeightMapType p2);

	float AStar::Cost(int x1, int y1, int z1, int x2, int y2, int z2);
	float AStar::DistanceXZ(int x1, int z1, int x2, int z2);

};

