#include <iostream>
#include <vector>
#include <climits>
#include "APSP.hpp"

std::vector<std::vector<int>> InitializeDistMatrix (std::vector<std::vector<std::pair<int,int>>>& graph)
{
  // index is the src, first element contains the key (dest) and second element contains contain the weight from src to dest
  std::vector<std::vector<int>> distance_matrix;

  // initialize the 2d adjacency matrix
  for (int i {}; i < graph.size(); ++i)
  {
    std::vector<int> temp(graph.size(), INT_MAX);
    distance_matrix.push_back(temp);
    distance_matrix[i][i] = 0; // diagonal as 0
  }

  // copy graph to the all_path_shortest_path (2d matrix), and initialize as infinity for the weight
  for (int i {}; i < graph.size(); ++i)
  {
    auto g {graph[i]};
    std::vector<std::pair<int, int>>::iterator it {g.begin()};
    for (it; it != g.end(); ++it)
    {
      distance_matrix[i][it->first] = it->second;
    }
  }
  return distance_matrix;
}

std::vector<std::vector<int>> FloydWarshall (std::vector<std::vector<std::pair<int,int>>>& graph)
{
  std::vector<std::vector<int>> all_path_shortest_path = InitializeDistMatrix(graph);

  for (int k {}; k < graph.size(); ++k)
  {
    for (int i {}; i < graph.size(); ++i)
    {
      for (int j {}; j < graph.size(); ++j)
      {
        if(all_path_shortest_path[i][j] > (all_path_shortest_path[i][k] + all_path_shortest_path[k][j]) &&
        (all_path_shortest_path[i][k] != INT_MAX && all_path_shortest_path[k][j] != INT_MAX))
        {
          all_path_shortest_path[i][j] = all_path_shortest_path[i][k] + all_path_shortest_path[k][j];
        }
      }
    }
  }

  return all_path_shortest_path;
}
