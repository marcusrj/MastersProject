#pragma once
#include "Terrain.h"
#include <list>
class AStar
{


	AStar();
	~AStar();

	Terrain::HeightMapType* m_heightMap;
	int m_terrainWidth, m_terrainHeight, m_indexCount;

	std::list<Terrain::HeightMapType> m_Road;
	std::list<Terrain::HeightMapType> m_RoadNetwork;


	void Initialise(Terrain::HeightMapType* heightmap);

	void firstRoad(Terrain::HeightMapType p1, Terrain::HeightMapType p2);

	//p2 replaced with existing network

	void newRoad(Terrain::HeightMapType p1, Terrain::HeightMapType p2);


	float DistanceXZ(Terrain::HeightMapType p1, Terrain::HeightMapType p2);

	float Cost(Terrain::HeightMapType p1, Terrain::HeightMapType p2);


	

};

