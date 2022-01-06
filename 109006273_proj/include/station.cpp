#include <iostream>
#include <vector>
#include "station.hpp"
#include "inventory.hpp"
//size electric of each station
Station::Station (int total_station, int size_electric[], int size_lady[], int size_road[]) : inventory_(total_station)
{
  for (int i {1}; i <= total_station; ++i)
  {
    Inventory temp(i, size_electric[i - 1], size_lady[i - 1], size_road[i - 1]);
    inventory_[i-1] = temp;
  }
}

int Station::GetFromInventory (int station_id, int bike_type) { return inventory_[station_id - 1].GetBike(bike_type); }

void Station::UpdateInventory (int station_id_return, int bike_type, int bike_id) { inventory_[station_id_return - 1].SetBike(bike_type, bike_id); }
