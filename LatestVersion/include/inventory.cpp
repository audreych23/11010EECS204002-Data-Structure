#include <iostream>
#include <vector>
#include "inventory.hpp"
#include "minheap.hpp"
/* public members*/

Inventory::Inventory (int station_id, int size_electric, int size_lady, int size_road) : bike_inventory_(3)
{
  station_id_ = station_id;
  size_bike_[0] = size_electric;
  size_bike_[1] = size_lady;
  size_bike_[2] = size_road;
  for (int i {}; i < size_electric; ++i){ bike_inventory_[0].Insert((station_id*100) + i); }
  for (int i {}; i < size_lady; ++i){ bike_inventory_[1].Insert((station_id*100) + i); }
  for (int i {}; i < size_road; ++i){ bike_inventory_[2].Insert((station_id*100) + i); }
}

int Inventory::Size (int bike_type) { return size_bike_[bike_type]; }

void Inventory::SetBike (int bike_type, int bike_id)
{
  bike_inventory_[bike_type].Insert(bike_id);
  size_bike_[bike_type] += 1;
}

int Inventory::GetBike (int bike_type)
{
  if(size_bike_[bike_type] <= 0) { return -1; } // -1 if it has no bike?
  size_bike_[bike_type] -= 1;
  int least_bike_id = bike_inventory_[bike_type].ExtractMin();
  return least_bike_id;
} // take the minimum ascending sorted

void Inventory::PrintInventory ()
{
  std::cout << station_id_ << ":" <<'\n';

  std::cout << "electric: ";
  for (int i {}; i != size_bike_[0]; ++i)
  {
    std::cout << bike_inventory_[0].ExtractMin() << ' ';
  }
  std::cout << '\n';

  std::cout << "lady: ";
  for (int i {}; i != size_bike_[1]; ++i)
  {
    std::cout << bike_inventory_[1].ExtractMin() << ' ';
  }
  std::cout << '\n';

  std::cout << "road: ";
  for (int i {}; i != size_bike_[2]; ++i)
  {
    std::cout << bike_inventory_[2].ExtractMin() << ' ';
  }
  std::cout << '\n';
}
