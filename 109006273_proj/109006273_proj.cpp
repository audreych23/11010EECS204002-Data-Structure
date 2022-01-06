#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include "include/vector.hpp"
#include "include/input.hpp"
#include "include/rentalhistory.hpp"
#include "include/inventory.hpp"
#include "include/minheap.hpp"
#include "include/graph.hpp"
#include "include/fee.hpp"

void Print (std::vector<std::vector<int>> &v)
{
  for (auto x : v)
  {
    for (auto y : x)
    {
      std::cout << y << " ";
    }
    std::cout << '\n';
  }
}

void Print (std::vector<std::vector<std::string>> &v)
{
  for (auto x : v)
  {
    for (auto y : x)
    {
      std::cout << y << " ";
    }
    std::cout << '\n';
  }
}
int main (int argc, char** argv)
{
  int revenues {};

  std::vector<std::vector<int>> read_input_station = ParseInputStation();
  Print (read_input_station);
  std::vector<std::vector<int>> read_input_map = ParseInputMap();
  Print (read_input_map);
  std::vector<std::vector<std::string>> read_input_fee = ParseInputFee();
  Print (read_input_fee);
  std::vector<std::vector<std::string>> read_input_user = ParseInputUser();
  Print (read_input_user);

  std::vector<Inventory> station;
  Graph map(read_input_station.size(), 0);
  Fee fee;
  RentalHistory rental_history;

  // InitializeInventory(station, ParseInputStation());
  // InitializeGraph(map, ParseInputMap());
  // fee = InitializeFee(ParseInputFee());
  // InitializeRentalHistory(rental_history, ParseInputMap());

  InitializeInventory(station, read_input_station);

  InitializeGraph(map, read_input_map);
  fee = InitializeFee(read_input_fee);
  InitializeRentalHistory(rental_history, read_input_user, fee, map, station, revenues);

  for (int i {}; i < read_input_station.size(); ++i)
  {
    station[i].PrintInventory();
  }

  std::cout << revenues << '\n';
}
