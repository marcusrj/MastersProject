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

float AStar::DistanceXZ(int x1, int z1, int x2, int z2)
{
	float distance = sqrt((pow((x1 - x2), 2) + pow((z1 - z2), 2)));

	return distance;
}

float AStar::Cost(Terrain::HeightMapType p1, Terrain::HeightMapType p2)
{
	int beta = 1;
	float slope = (p1.y - p2.y) / DistanceXZ(p1, p2);
	float cost = DistanceXZ(p1, p2) + DistanceXZ(p1, p2)*(1 - slope)*beta;

	//slope = change in y / change in x
	return cost;
}

float AStar::Cost(int x1,int y1, int z1, int x2, int y2, int z2)
{
	int beta = 1;
	float slope = (y1 - y2) / DistanceXZ(x1,  z1,  x2,  z2);
	float cost = DistanceXZ(x1, z1, x2, z2) + DistanceXZ(x1, z1, x2, z2)*(1 - slope)*beta;

	//slope = change in y / change in x
	return cost;
}


std::list<AStar::RoadNode> AStar::getRoad()
{
	return m_Road;
}

void AStar::firstRoad(Terrain::HeightMapType p1, Terrain::HeightMapType p2)
{
	std::list<AStar::RoadNode> L;
	std::list<AStar::RoadNode> Possibilities;
	std::list<AStar::RoadNode> Road;

	AStar::RoadNode start;
	start.x = p1.x;
	start.y = p1.y;
	start.z = p1.z;
	start.costToParent = 0;
	start.costToGoal = Cost(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);;
	start.parent = NULL;
	start.child = NULL;

	L.push_back(start);
	
	while (L.size() > 0)
	{
		AStar::RoadNode* P = &start;
		for (auto it = L.begin(); it != L.end(); it++)
		{
			if (P->costToGoal > it->costToGoal) {
				P = &*it; //the iterator might get invalidated but best we can do
				//P = it;
				
			}
		}

		RoadNode Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight;

		Up.x = P->x;
		Up.z = P->z + 1;
		Up.y = P->y;

		Down.x = P->x;
		Down.z = P->z - 1;
		Down.y = P->y;

		Left.x = P->x - 1;
		Left.z = P->z;
		Left.y = P->y;

		Right.x = P->x + 1;
		Right.z = P->z;
		Right.y = P->y;

		UpLeft.x = P->x - 1;
		UpLeft.z = P->z + 1;
		UpLeft.y = P->y;

		UpRight.x = P->x + 1;
		UpRight.z = P->z + 1;
		UpRight.y = P->y;

		DownLeft.x = P->x - 1;
		DownLeft.z = P->z - 1;
		DownLeft.y = P->y;

		DownRight.x = P->x + 1;
		DownRight.z = P->z - 1;
		Right.y = P->y;

		Possibilities.push_back(Up);
		Possibilities.push_back(Down);
		Possibilities.push_back(Left);
		Possibilities.push_back(Right);
		Possibilities.push_back(UpLeft);
		Possibilities.push_back(UpRight);
		Possibilities.push_back(DownLeft);
		Possibilities.push_back(DownRight);

		for (auto it = Possibilities.begin(); it != Possibilities.end(); it++)
		{
			it->parent = P;
			it->costToParent = Cost(it->x,it->y,it->z, P->x, P->y, P->z);
			it->costToGoal = Cost(it->x, it->y, it->z, p2.x, p2.y, p2.z);
		}

		for (auto it = Possibilities.begin(); it != Possibilities.end(); it++)
		{
			if (p2.x == it->x && p2.z == it->z)
			{
				AStar::RoadNode current;
				AStar::RoadNode next;

				current.parent = it->parent;
				current.x = it->x;
				current.y = it->y;
				current.z = it->z;
				next = *current.parent;
				do
				{
					Road.push_front(current);
					m_Road.push_front(current);
					current = next;
					if (current.parent != NULL)
					{
						next = *current.parent;
					}
					
				} while ((current.x != p1.x || current.z != p1.z));
			

				return;
			}
			
		}

		//add posibilities to end of l
		L.splice(L.end(), Possibilities);

		Possibilities.clear();

	}

}
