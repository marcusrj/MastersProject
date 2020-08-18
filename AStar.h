#pragma once
#include "Terrain.h"
#include <list>
#include <time.h>
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


	//std::list<AStar::RoadNode> createRoad(Terrain::HeightMapType* heightmap);
	void generateRoad(Terrain::HeightMapType p1, Terrain::HeightMapType p2, Terrain::HeightMapType* heightmap);
	void generateRoad(Terrain::HeightMapType* heightmap);

	//p2 replaced with existing network

	void newRoad(Terrain::HeightMapType p1, Terrain::HeightMapType p2);

	std::list<AStar::RoadNode> AStar::getRoad();


	float DistanceXZ(Terrain::HeightMapType p1, Terrain::HeightMapType p2);

	float Cost(Terrain::HeightMapType p1, Terrain::HeightMapType p2);

	float AStar::Cost(float x1, float y1, float z1, float x2, float y2, float z2);
	float AStar::Cost(int x1, int y1, int z1, int x2, int y2, int z2);
	float AStar::DistanceXZ(int x1, int z1, int x2, int z2);

};

