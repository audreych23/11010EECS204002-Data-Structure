#include <iostream>
#include <vector>
#include <climits>
#include "graph.hpp"
/* public members */

Graph::Graph (int v, int e) : graph_(v)
{
  vertices = v;
  edges = e;
}

void Graph::Insert (int from, int to, int length)
{
  Pair pair(to-1, length); // off by 1 error
  Pair pair_temp(from-1, length);
  graph_[from-1].push_back(pair);
  graph_[to-1].push_back(pair_temp);
}

void Graph::InitializeDistance ()
{
  // only call once
  FloydWarshall();
}

int Graph::GetDistance (int from, int to)
{
  return shortest_path_[from-1][to-1]; // only call after Initialize distance
}

void Graph::Print ()
{
  for (int i {}; i < graph_.size(); ++i)
  {
    auto g {graph_[i]};
    std::cout << i << '\n';
    for (int j {}; j < g.size(); ++j)
    {
      std::cout << "   " << g[j].destination << " " << g[j].length << " " << '\n';
    }
  }
}

void Graph::PrintDistance ()
{
  for (auto x : shortest_path_)
  {
    for (auto y : x)
    {
      std::cout << y << ' ';
    }
    std::cout << '\n';
  }
}

/* private members */

void Graph::InitializeDistanceMatrix ()
{
  // index is the src, first element contains the key (dest) and second element contains contain the weight from src to dest

  // initialize the 2d adjacency matrix
  for (int i {}; i < graph_.size(); ++i)
  {
    std::vector<int> temp(graph_.size());
    for (int j {}; j < graph_.size(); ++j)
    {
      temp[j] = INT_MAX;
    }
    shortest_path_.push_back(temp);
    shortest_path_[i][i] = 0; // diagonal as 0
  }

  // copy graph to the all_path_shortest_path (2d matrix), and initialize as infinity for the weight
  for (int i {}; i < graph_.size(); ++i)
  {
    auto g {graph_[i]};
    //std::vector<std::pair<int, int>>::iterator it {g.begin()};
    for (int j {}; j < g.size(); ++j)
    {
      shortest_path_[i][g[j].destination] = g[j].length;
    }
  }
}

void Graph::FloydWarshall ()
{
  InitializeDistanceMatrix();

  for (int k {}; k < graph_.size(); ++k)
  {
    for (int i {}; i < graph_.size(); ++i)
    {
      for (int j {}; j < graph_.size(); ++j)
      {
        if(shortest_path_[i][j] > (shortest_path_[i][k] + shortest_path_[k][j]) &&
        (shortest_path_[i][k] != INT_MAX && shortest_path_[k][j] != INT_MAX))
        {
          shortest_path_[i][j] = shortest_path_[i][k] + shortest_path_[k][j];
        }
      }
    }
  }
}
