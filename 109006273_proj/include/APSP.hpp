#ifndef APSP_HPP_
#define APSP_HPP_

std::vector<std::vector<int>> InitializeDistMatrix (std::vector<std::vector<std::pair<int,int>>>& graph);

std::vector<std::vector<int>> FloydWarshall (std::vector<std::vector<std::pair<int,int>>>& graph);

#endif
