#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <fstream>

#include "vector.hpp"

class Node
{
public:

  Node () = default;
  Node (uint64_t to, uint64_t distance): to_ {to}, distance_ {distance} {}

  friend class Graph;
  friend std::ostream& operator<< (std::ostream& out, Node const& node);

private:

  uint64_t to_;
  uint64_t distance_;

};

class Graph
{
public:

  Graph () = default;
  Graph (uint64_t size);

  uint64_t Distance (uint64_t from, uint64_t to) const;

  friend std::ostream& operator<< (std::ostream& out, Graph const& graph);

private:

  void FloydWarshall ();

  Vector<Vector<Node>> graph_;
  Vector<Vector<uint64_t>> shortest_distances_;

};

#endif
