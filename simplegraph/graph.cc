/*	Kendrick Hardy
	z1945923
	CSCI 340-2
	I certify that this is my own work and where appropriate an extension
	of the starter code provided for the assignment.
*/

#include "graph.h"

#include <iostream>
#include <fstream>
#include <list>
#include <vector>

std::vector<int> visited;
std::vector<int> paths;
std::vector<bool> init;

/**
 * Constructs the graph
 *
 * @param filename An input file of the graph given in adjaceny matrix representation
 **********************************************************************************************/
Graph::Graph(const char* filename)
{
	std::ifstream file;
        file.open(filename);
	std::list<int> list;
        char value;

	if(!file){
		std::cerr << "Could not open file" << std::endl;
	}

        file >> size;

	init = std::vector<bool> (size, false);

	for(int i = 0; i < size; i++){
		file >> value;
		labels.push_back(value);
	}

	for(int i = 0; i < size; i++){
		file >> value;

		for(int i = 0; i < size; i++){
			int num;
			file >> num;
			if(num == 1){
				list.push_back(i);
			}
		}

		adj_list.push_back(list);
		list.clear();
	}
} //End of Graph()

/**
 * Destructor
 * ********************************************************/
Graph::~Graph(){} //End of ~Graph()

/**
 * Gets the size of a graph
 * 
 * @returns an integer representing the size of the graph
 * ***************************************************************************/
int Graph::Getsize() const
{
	return size;
}

/**
 * traverses a graph in depth-first traversal/search algorithm
 *
 * @param v a vertex with the index value of v
 * ********************************************************************************************/
void Graph::Depthfirst(int v)
{
	bool isIn = true;
	visited.push_back(v);
	paths.push_back(v);
	for(auto it = adj_list[v].begin(); it != adj_list[v].end(); ++it){
		for(int i = 0; i < (int) visited.size(); i++){
			if(visited[i] == *it){
				isIn = false;
				break;
			}
		}

		if(isIn){
			paths.push_back(*it);
			Depthfirst(*it);
		}

	}
} //End of Depthfirst()

/**
 * traverses a graph
 *
 * @note Uses Depthfirst()
 * ***************************************************************************/
void Graph::Traverse()
{
	bool isIn = true;
	for(int j = 0; j < (int) labels.size(); j++){
		for(int i = 0; i < (int) visited.size(); i++){
			if(visited[i] == j){
				isIn = false;
				break;
			}
		}

		if(isIn){
			Depthfirst(j);
		}
	}
	std::cout << "------- traverse of graph ------";
	std::cout << std::endl;
	for(int i = 0; i < (int) visited.size(); i++){
		std::cout << labels[visited[i]] << " ";
	}

	std::cout << std::endl;
	for(int i = 0; i < (int) paths.size(); i++){
		std::cout << "(" << labels[paths[i]] << ", ";
		i += 1;
		std::cout << labels[paths[i]] << ") ";
	}
	std::cout << std::endl;

	std::cout << "--------- end of traverse -------" << std::endl;
	std::cout << std::endl;
} //End of Traverse()

/**
 * Prints the adjacency list for the graph
 * *****************************************************************************************************/
void Graph::Print() const
{
	std::cout << "Number of vertices in the graph: " << labels.size() << std::endl;
	std::cout << std::endl;

	std::cout << "-------- graph --------" << std::endl;
	for(int i = 0; i < (int) labels.size(); i++)
	{
		std::cout << labels[i] << ": ";
		auto it = adj_list[i].begin();
		while(it != adj_list[i].end())
		{
			std::cout << labels[(*it)] << ", ";
			++it;
		}
		std::cout << std::endl;
	}
	std::cout << "------- end of graph ------" << std::endl;
	std::cout << std::endl;
} //End of Print()
