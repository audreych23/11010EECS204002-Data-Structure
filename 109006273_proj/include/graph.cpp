#include <limits>

#include "graph.hpp"

/* public members */

std::ostream& operator<< (std::ostream& out, Node const& node)
{
  out << "(" << node.to_ << "," << node.distance_ << ")";
  return out;
}

Graph::Graph (uint64_t size)
{
  graph_ = Vector<Vector<Node>>{size};
  std::ifstream fin {"test_case/map.txt"};
  while (fin)
  {
    uint64_t from {};
    uint64_t to {};
    uint64_t distance {};
    fin >> from >> to >> distance;
    if (from)
    {
      graph_[from - 1].PushBack(Node{to - 1, distance});
      graph_[to - 1].PushBack(Node{from - 1, distance});
    }
  }
  {
    shortest_distances_ = Vector<Vector<uint64_t>>{size};
    Vector<uint64_t> max_distances {Vector<uint64_t>{size}};
    for (uint64_t i {}; i != size; ++i) { max_distances[i] = std::numeric_limits<uint64_t>::max(); }
    for (uint64_t from {}; from != size; ++from) { shortest_distances_[from] = max_distances; }
    for (uint64_t i {}; i != size; ++i) { shortest_distances_[i][i] = 0; }
    for (uint64_t from {}; from != size; ++from)
    {
      for (uint64_t i {}; i != graph_[from].Size(); ++i)
      {
        shortest_distances_[from][graph_[from][i].to_] = graph_[from][i].distance_;
      }
    }
    FloydWarshall();
  }
}

uint64_t Graph::Distance (uint64_t from, uint64_t to) const
{
  return shortest_distances_[from - 1][to - 1];
}

std::ostream& operator<< (std::ostream& out, Graph const& graph)
{
  out << "graph_:\n";
  for (uint64_t from {}; from != graph.graph_.Size(); ++from)
  {
    out << from << ": ";
    if (graph.graph_[from].Size())
    {
      out << graph.graph_[from][0];
      for (uint64_t i {1}; i != graph.graph_[from].Size(); ++i)
      {
        out << " -> " << graph.graph_[from][i];
      }
    }
    out << "\n";
  }
  out << "\nshortest_distances_:\n";
  for (uint64_t from {}; from != graph.shortest_distances_.Size(); ++from)
  {
    if (graph.shortest_distances_.Size())
    {
      out << "(" << from << "," << 0 << "," << graph.shortest_distances_[from][0] << ")";
    }
    for (uint64_t to {1}; to != graph.shortest_distances_.Size(); ++to)
    {
      out << ", " << "(" << from << "," << to << "," << graph.shortest_distances_[from][to] << ")";
    }
    out << "\n";
  }
  return out;
}

/* private members */

void Graph::FloydWarshall ()
{
  for (uint64_t middle {}; middle != graph_.Size(); ++middle)
  {
    for (uint64_t from {}; from != graph_.Size(); ++from)
    {
      for (uint64_t to {}; to != graph_.Size(); ++to)
      {
        if
        (
          shortest_distances_[from][middle] != std::numeric_limits<uint64_t>::max()
          && shortest_distances_[middle][to] != std::numeric_limits<uint64_t>::max()
        )
        {
          uint64_t distance {shortest_distances_[from][middle] + shortest_distances_[middle][to]};
          if (distance < shortest_distances_[from][to]) { shortest_distances_[from][to] = distance; }
        }
      }
    }
  }
  return;
}
