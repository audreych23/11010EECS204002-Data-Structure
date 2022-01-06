#ifndef STATION_HPP_
#define STATION_HPP_

#include "inventory.hpp"
// store vector<vector<station>>
// station stores all station inventory
class Station
{
public:

  Station () = default;
  Station (int, int*, int*, int*);
  //~Station ();
  // void InitializeStation (int, int*, int*, int*);

  int GetFromInventory (int, int);
  void UpdateInventory (int, int, int);
  void PrintInventory();

private:

  std::vector<Inventory> inventory_; //index indicates which station id // station_id - 1

};

#endif
