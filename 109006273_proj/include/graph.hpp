#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <vector>
#include "pair.hpp"
// TODO include the node e.g pair of dest and weight in diff file
class Graph
{
public:
  //TODO floydwarshall?
  Graph() = default;
  Graph(int, int);

  void Insert (int, int, int);
  void InitializeDistance ();
  int GetDistance (int, int); // only when initialize distance is done
  void Print ();
  void PrintDistance ();

private:

  void InitializeDistanceMatrix ();
  void FloydWarshall ();

  int vertices;
  int edges;
  std::vector<std::vector<Pair>> graph_;
  std::vector<std::vector<int>> shortest_path_;

};


#endif

// TODO one more data structure, either min heap or idk actually, i think min heap is good (to change with set)
// TOOD fee class store the fee for the bike
