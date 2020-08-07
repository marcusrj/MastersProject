#include "pch.h"
#include "AStar.h"





AStar::AStar() 
{

}

AStar::~AStar() 
{

}

void AStar::Initialise(Terrain::HeightMapType* heightmap) 
{
	m_heightMap = heightmap;
}
float AStar::DistanceXZ(Terrain::HeightMapType p1, Terrain::HeightMapType p2)
{
	float distance = sqrt((pow((p1.x - p2.x),2) + pow((p1.z - p2.z), 2)));

	return distance;
}

float AStar::Cost(Terrain::HeightMapType p1, Terrain::HeightMapType p2)
{
	//DistXY(S, T) + DistXY(S, T)*(1-slope)*beta



	float slope = (p1.y - p2.y) / DistanceXZ(p1, p2);

	//slope = change in y / change in x
	
}

void AStar::firstRoad(Terrain::HeightMapType p1, Terrain::HeightMapType p2)
{
	std::list<Terrain::HeightMapType> L;
	std::list<Terrain::HeightMapType> Possibilities;

	L.push_back(p1);


	while (L.size() > 0)
	{

	}

}
