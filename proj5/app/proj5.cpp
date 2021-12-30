#include "proj5.hpp"
#include <limits>
#include <unordered_map>
#include "MyPriorityQueue.hpp"

// As a reminder, for this project, edges have positive cost, g[i][j] = 0 means no edge.
std::vector<Edge> compute_mst(const std::vector< std::vector<unsigned>> & graph)
{
	std::vector<Edge> mst;
	std::vector<int> distance;
	for(unsigned i = 0; i < graph.size(); i++)
	{
		distance.push_back(std::numeric_limits<int>::max()); //sets distance to max possible int
	}
	std::vector<bool> inTree;
	for(unsigned i = 0; i < graph.size(); i++)
	{
		inTree.push_back(false); //sets distance to max possible int
	}
	MyPriorityQueue<Edge> nodes;
	Edge edge = Edge{0,0,0};
	nodes.insert(edge);
	distance[0] = 0;
	inTree[0] = true;
	while(nodes.isEmpty() == false)
	{
		Edge current = nodes.min();
		nodes.extractMin();
		if(inTree[current.pt1] == false)
		{
			inTree[current.pt1] = true;
			mst.push_back(current);
		}
		for(unsigned i = 0; i < graph[current.pt1].size(); i++)
		{
			// edge {current, parent, cost}
			if(inTree[i] == false)
			{
				Edge new_edge = Edge{i, current.pt1, graph[current.pt1][i]};
				if(new_edge.weight < distance[i]) //distance is less than existing distnace
				{
					distance[i] = new_edge.weight;
					nodes.insert(new_edge);

				}
			}

		}

	}

	return mst;
}


// Returns the cost of the edges in the given vector,
// This does not confirm that it is a MST at all.  
unsigned mstCost(const std::vector<Edge> & vE) 
{
	unsigned sum =0;
	for(auto e: vE)
	{
		sum += e.weight;
	}
	return sum;
}
