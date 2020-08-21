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

float AStar::Cost(float x1,float y1, float z1, float x2, float y2, float z2)
{
	float beta = 20 ;
	float slope = ((y1 - y2) / DistanceXZ(x1,  z1,  x2,  z2));
	slope = pow(slope,2);
	slope = sqrt(slope);
	float cost = DistanceXZ(x1, z1, x2, z2) + DistanceXZ(x1, z1, x2, z2);


	//slope = change in y / change in x
	return cost;
}


std::list<AStar::RoadNode> AStar::getRoad()
{
	return m_Road;
}
/*
void AStar::generateRoad(Terrain::HeightMapType p1, Terrain::HeightMapType p2)
{
	std::list<AStar::RoadNode> L;
	std::list<AStar::RoadNode> Possibilities;
	std::list<AStar::RoadNode> Road;

	AStar::RoadNode start;
	start.x = p1.x;
	start.y = p1.y;
	start.z = p1.z;
	start.costToParent = 0;
	start.costToGoal = AStar::Cost(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);;
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
*/
void AStar::generateRoad(Terrain::HeightMapType p1, Terrain::HeightMapType p2, Terrain::HeightMapType* heightmap)
{
	

	std::list<AStar::RoadNode> L;
	std::list<AStar::RoadNode> Possibilities;
	std::list<AStar::RoadNode> Road;

	AStar::RoadNode start;
	start.x = p1.x;
	start.y = p1.y;
	start.z = p1.z;
	start.costToParent = 0;
	start.costToGoal = AStar::Cost(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);;
	start.parent = NULL;
	start.child = NULL;

	L.push_back(start);
	AStar::RoadNode* P = &start;
	while (L.size() > 0)
	{
		
		for (auto it = L.begin(); it != L.end(); it++)
		{
			if (P->costToGoal > it->costToGoal) {
				P = &*it; //the iterator might get invalidated but best we can do
				//P = it;

			}
		}

//		RoadNode Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight;
		RoadNode neighbours[8];
		int py;
		neighbours[0].x = P->x;
		neighbours[0].z = P->z + 1;
		py = 1000 * neighbours[0].z + neighbours[0].x;
		neighbours[0].y = heightmap[py].y;

		neighbours[1].x = P->x;
		neighbours[1].z = P->z - 1;
		py = 1000 * neighbours[1].z + neighbours[1].x;
		neighbours[1].y = heightmap[py].y;

		neighbours[2].x = P->x - 1;
		neighbours[2].z = P->z;
		py = 1000 * neighbours[2].z + neighbours[2].x;
		neighbours[2].y = heightmap[py].y;

		neighbours[3].x = P->x + 1;
		neighbours[3].z = P->z;
		py = 1000 * neighbours[3].z + neighbours[3].x;
		neighbours[3].y = heightmap[py].y;
		//upleft
		neighbours[4].x = P->x - 1;
		neighbours[4].z = P->z + 1;
		py = 1000 * neighbours[4].z + neighbours[4].x;
		neighbours[4].y = heightmap[py].y;
		//upright
		neighbours[5].x = P->x + 1;
		neighbours[5].z = P->z + 1;
		py = 1000 * neighbours[5].z + neighbours[5].x;
		neighbours[5].y = heightmap[py].y;
		//downleft
		neighbours[6].x = P->x - 1;
		neighbours[6].z = P->z - 1;
		py = 1000 * neighbours[6].z + neighbours[6].x;
		neighbours[6].y = heightmap[py].y;
		//downright
		neighbours[7].x = P->x + 1;
		neighbours[7].z = P->z - 1;
		py = 1000 * neighbours[7].z + neighbours[7].x;
		neighbours[7].y = heightmap[py].y;

		for (size_t i = 0; i < 8; i++)
		{	
			
				//if (neighbours[i].y > 3.4f && neighbours[i].y < 28.5f)
				//{
					Possibilities.push_back(neighbours[i]);
				//}
			

				
		}
		
		for (auto it = Possibilities.begin(); it != Possibilities.end(); it++)
		{
			it->parent = P;
			it->costToParent = Cost(it->x, it->y, it->z, P->x, P->y, P->z);
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
				} 
				while ((current.x != p1.x || current.z != p1.z));

				return;
			}
		}

		for (auto it1 = Possibilities.begin(); it1 != Possibilities.end(); it1++)
		{
			//bool contains = false;
			//for (auto it2 = L.begin(); it2 != L.end(); it2++)
			//{
				//if (it1->x == it2->x && it1->z == it2->z) {
					//contains = true;
					//if (it1->costToGoal < it2->costToGoal) 
					//{
						//L.push_back(*it1);
					//}
				//}
			//}
				//if (contains == false)
				//{
					L.push_back(*it1);
				//}
		}
		//add posibilities to end of l
		//L.splice(L.end(), Possibilities);
		Possibilities.clear();
	}

}