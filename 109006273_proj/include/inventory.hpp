#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_
#include <vector>
#include <set>
//#include "vector.hpp"
// stores the inventory of one station, and bike_invenotry stores the id of bike in each corresponding senction
// size_bike[0] stores the size of electric etcetc
class Inventory
{
public:

  Inventory () = default;
  //~Inventory () = default;
  Inventory (int, int, int, int);
  //~Inventory ();
  int Size (int); //biketype as parameter
  void SetBike (int, int); // setBike?
  int GetBike (int); // also updates inventory? reduces the amount of bike
  void PrintInventory ();

private:

  int station_id_;
  int size_bike_[3];
  std::vector<std::set<int>> bike_inventory_; // temporary use set, but maybe we can apply with min heap?

};

#endif
